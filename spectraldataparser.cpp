#include "spectraldataparser.h"

SpectralDataParser::SpectralDataParser()
{

}

QList<int> SpectralDataParser::parseUncalibratedData(QString response)
{
    qDebug() << Q_FUNC_INFO;
    QList<int> spectralData;
    response.replace("OK", "");
    qDebug() << response;
    QStringList subStrings = response.split(",");
    if(subStrings.length() < valuesPerFrame)
        qCritical() << "spectral data bad format";
    else
    {
        QList<int> rawOrder;
        for(int i = 0; i < valuesPerFrame; ++i)
        {
            rawOrder.append(subStrings.at(i).toInt());
        }

        spectralData.append(rawOrder.at(positionsReceived::A));
        spectralData.append(rawOrder.at(positionsReceived::B));
        spectralData.append(rawOrder.at(positionsReceived::C));
        spectralData.append(rawOrder.at(positionsReceived::D));
        spectralData.append(rawOrder.at(positionsReceived::E));
        spectralData.append(rawOrder.at(positionsReceived::F));
        spectralData.append(rawOrder.at(positionsReceived::G));
        spectralData.append(rawOrder.at(positionsReceived::H));
        spectralData.append(rawOrder.at(positionsReceived::R));
        spectralData.append(rawOrder.at(positionsReceived::I));
        spectralData.append(rawOrder.at(positionsReceived::S));
        spectralData.append(rawOrder.at(positionsReceived::J));
        spectralData.append(rawOrder.at(positionsReceived::T));
        spectralData.append(rawOrder.at(positionsReceived::U));
        spectralData.append(rawOrder.at(positionsReceived::V));
        spectralData.append(rawOrder.at(positionsReceived::W));
        spectralData.append(rawOrder.at(positionsReceived::K));
        spectralData.append(rawOrder.at(positionsReceived::L));
    }
    return spectralData;
}
