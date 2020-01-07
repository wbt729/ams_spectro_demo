#ifndef COMMAND_H
#define COMMAND_H

#include <QObject>
#include <QDebug>
#include <QVariant>

class Command : public QObject
{
    Q_OBJECT
public:
    explicit Command(QObject *parent = nullptr);
    void setAtCode(QString code);
    void setPayload(QVariant payload);
    QString getCommandString();
    void setResponse(QString response);

signals:
    void responseReceived(QString response);

private:
    QString ATCode;
    QString payload;
    QString response;
};

#endif // COMMAND_H
