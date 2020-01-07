#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>
#include <QDebug>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>
#include <QApplication>
#include <QSerialPortInfo>

#include "sensorhandler.h"
#include "spectraprovider.h"

class Application : public QApplication
{
    Q_OBJECT
    Q_PROPERTY(QStringList serialPorts READ getSerialPorts CONSTANT)


public:
    explicit Application(int &argc, char **argv);
    Q_INVOKABLE QStringList getSerialPorts() { return portLocations; }

signals:

private:
    QQmlApplicationEngine* engine{nullptr};
    SensorHandler* sensorHandler{nullptr};
    SpectraProvider* spectraProvider{nullptr};

    void init();

    QStringList portLocations;
};

#endif // APPLICATION_H
