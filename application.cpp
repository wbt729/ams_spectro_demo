#include "application.h"

Application::Application(int &argc, char **argv) : QApplication(argc, argv)
{
    QQuickStyle::setStyle("Material");

    sensorHandler = new SensorHandler(this);
    spectraProvider = new SpectraProvider(this);

    QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
    for(auto port: ports)
    {
        portLocations.append(port.systemLocation());
    }

    connect(sensorHandler, &SensorHandler::spectralDataReceived, spectraProvider, &SpectraProvider::setSpectralData);

    init();
}

void Application::init()
{
    qDebug() << Q_FUNC_INFO;
    engine = new QQmlApplicationEngine(this);
    engine->rootContext()->setContextProperty("application", this);
    engine->rootContext()->setContextProperty("sensorHandler", sensorHandler);
    engine->rootContext()->setContextProperty("spectraProvider", spectraProvider);

    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    QObject::connect(engine, &QQmlApplicationEngine::objectCreated,
                     this, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine->load(url);
}
