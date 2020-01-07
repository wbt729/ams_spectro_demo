#ifndef SENSORHANDLER_H
#define SENSORHANDLER_H

#include <QObject>
#include <QDebug>
#include <QSerialPort>
#include <QStateMachine>

#include "command.h"
#include "spectraldataparser.h"

class SensorHandler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString received READ getReceived NOTIFY receivedChanged)
    Q_PROPERTY(QString state READ getState WRITE setState NOTIFY stateChanged)

public:
    explicit SensorHandler(QObject *parent = nullptr);
    Q_INVOKABLE QString getReceived() { return received; }
    Q_INVOKABLE void requestData();
    Q_INVOKABLE void requestSWVersion() { serialPort->write("ATVERSW\n"); }
    Q_INVOKABLE void sendCalibrationData() { serialPort->write("ATSCL0=10\n");}
    Q_INVOKABLE void setGain(int gainFactor) { serialPort->write(QString("ATGAIN=%1\n").arg(gainFactor).toLatin1());}
    Q_INVOKABLE void setIntegrationTime(int timeFactor) { serialPort->write(QString("ATINTTIME=%1\n").arg(timeFactor).toLatin1());}
    Q_INVOKABLE void openSerialPort(QString portName);
    Q_INVOKABLE bool isConnected() { return !stateMachine.configuration().contains(stateNotConnected); }
    Q_INVOKABLE QString getState() { return state; }
    void setState(QString state) { this->state = state; emit stateChanged(); }
    Q_INVOKABLE void toggleMeasurement();

signals:
    void receivedChanged();
    void spectralDataReceived(QList<int> data);
    void connected();
    void disconnected();
    void measuringStarted();
    void measuringStopped();
    void stateChanged();

private slots:
    void onReadyRead();
    void onSpectralDataReceived(QString response);
    void onStateNotConnectedEntered();
    void onStateIdleEntered();
    void onStateMeasuringEntered();

private:
    QSerialPort* serialPort{nullptr};
    const int baudRate{115200};
    QString received;
    void sendCommand(Command* command);
    Command* currentCommand{nullptr};
    void clearCurrentCommand();

    QStateMachine stateMachine;
    QState* stateNotConnected{nullptr};
    QState* stateIdle{nullptr};
    QState* stateMeasuring{nullptr};
    QString state = "undefined";

    void initStateMachine();
    void startMeasuring();
    void stopMeasuring();
};

#endif // SENSORHANDLER_H
