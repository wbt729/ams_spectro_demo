#include "sensorhandler.h"

SensorHandler::SensorHandler(QObject *parent) : QObject(parent)
{
    initStateMachine();
}

void SensorHandler::requestData()
{
    qDebug() << Q_FUNC_INFO;
    Command* command = new Command(this);
    command->setAtCode("ATDATA");
    connect(command, &Command::responseReceived, this, &SensorHandler::onSpectralDataReceived);
    sendCommand(command);
}

void SensorHandler::startMeasuring()
{
    qDebug() << Q_FUNC_INFO;
    Command* command = new Command(this);
    command->setAtCode("ATBURST");
    command->setPayload("255,0");
    connect(command, &Command::responseReceived, this, &SensorHandler::onSpectralDataReceived);
    sendCommand(command);
    emit measuringStarted();
}

void SensorHandler::stopMeasuring()
{
    qDebug() << Q_FUNC_INFO;
    Command* command = new Command(this);
    command->setAtCode("ATBURST");
    command->setPayload("0,0");
    connect(command, &Command::responseReceived, this, &SensorHandler::onSpectralDataReceived);
    sendCommand(command);
    emit measuringStopped();
}

void SensorHandler::openSerialPort(QString portName)
{
    qDebug() << Q_FUNC_INFO << portName;
    if(serialPort)
    {
        serialPort->deleteLater();
    }
    serialPort = new QSerialPort(portName);
    serialPort->setBaudRate(baudRate);
    connect(serialPort, &QSerialPort::readyRead, this, &SensorHandler::onReadyRead);
    serialPort->open(QIODevice::ReadWrite);
    if(serialPort->isWritable())
    {
        serialPort->write("ATSRST\n");
        emit connected();
    }
    else
        qCritical() << "can not open serial port" << portName;
}

void SensorHandler::toggleMeasurement()
{
    qDebug() << Q_FUNC_INFO;
    if(stateMachine.configuration().contains(stateIdle))
        startMeasuring();
    else
        stopMeasuring();
}

void SensorHandler::onReadyRead()
{
    qDebug() << Q_FUNC_INFO;
    if(serialPort->canReadLine()) {
        received = serialPort->readLine();
        if(currentCommand)
            currentCommand->setResponse(received);
        qDebug() << "received" << received;
        emit receivedChanged();
    }
}

void SensorHandler::onSpectralDataReceived(QString response)
{
    qDebug() << Q_FUNC_INFO << response;
    QList<int> spectralData = SpectralDataParser::parseUncalibratedData(response);
    emit spectralDataReceived(spectralData);
}

void SensorHandler::onStateNotConnectedEntered()
{
    qDebug() << Q_FUNC_INFO;
}

void SensorHandler::onStateIdleEntered()
{
    qDebug() << Q_FUNC_INFO;
}

void SensorHandler::onStateMeasuringEntered()
{
    qDebug() << Q_FUNC_INFO;
}

void SensorHandler::sendCommand(Command *command)
{
    qDebug() << Q_FUNC_INFO << command->getCommandString();
    clearCurrentCommand();
    currentCommand = command;

    if(serialPort->isWritable())
        serialPort->write(command->getCommandString().toLatin1());
    else
        qCritical() << "serial port not writable";
}

void SensorHandler::clearCurrentCommand()
{
    qDebug() << Q_FUNC_INFO;
    if(currentCommand)
    {
        currentCommand->disconnect();
        currentCommand->deleteLater();
    }
}

void SensorHandler::initStateMachine()
{
    qDebug() << Q_FUNC_INFO;

    stateNotConnected = new QState();
    stateMachine.addState(stateNotConnected);
    stateNotConnected->assignProperty(this, "state", "notConnected");
    connect(stateNotConnected, &QState::entered, this, &SensorHandler::onStateNotConnectedEntered);

    stateIdle = new QState();
    stateMachine.addState(stateIdle);
    stateIdle->assignProperty(this, "state", "idle");
    connect(stateIdle, &QState::entered, this, &SensorHandler::onStateIdleEntered);

    stateMeasuring = new QState();
    stateMachine.addState(stateMeasuring);
    stateMeasuring->assignProperty(this, "state", "measuring");
    connect(stateMeasuring, &QState::entered, this, &SensorHandler::onStateMeasuringEntered);

    stateNotConnected->addTransition(this, &SensorHandler::connected, stateIdle);
    stateIdle->addTransition(this, &SensorHandler::measuringStarted, stateMeasuring);
    stateIdle->addTransition(this, &SensorHandler::disconnected, stateIdle);
    stateMeasuring->addTransition(this, &SensorHandler::measuringStopped, stateIdle);
    stateMeasuring->addTransition(this, &SensorHandler::disconnected, stateIdle);

    stateMachine.setInitialState(stateNotConnected);
    stateMachine.start();
}
