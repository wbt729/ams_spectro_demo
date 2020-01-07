#include "command.h"

Command::Command(QObject *parent) : QObject(parent)
{

}

void Command::setAtCode(QString code)
{
    qDebug() << Q_FUNC_INFO << code;
    this->ATCode = code;
}

void Command::setPayload(QVariant payload)
{
    qDebug() << Q_FUNC_INFO << payload;
    this->payload = payload.toString();
}

QString Command::getCommandString()
{
    qDebug() << Q_FUNC_INFO;
    QString commandString;
    if(ATCode.isEmpty())
    {
        qCritical() << "no command defined";
    }
    else
    {
        commandString += ATCode;
    }
    if(!payload.isEmpty())
    {
        commandString +=  QString("=%1").arg(payload).toLatin1();
    }
    commandString += "\n";
    return commandString;
}

void Command::setResponse(QString response)
{
    qDebug() << Q_FUNC_INFO;
    this->response = response;
    emit responseReceived(response);
}
