#include "spectraprovider.h"

SpectraProvider::SpectraProvider(QObject *parent) : QObject(parent)
{

}

void SpectraProvider::updateSeries(QAbstractSeries *series)
{
    qDebug() << Q_FUNC_INFO;
    if(series)
    {
        QXYSeries* xySeries = static_cast<QXYSeries*>(series);
        QList<QPointF> points;
        points.reserve(spectralData.size());
        yMax = 0;
        for(int i = 0; i < spectralData.size(); i++)
        {
            points.append(QPointF(xOffset + xStep * i, spectralData.at(i)));
            if(spectralData.at(i) > yMax)
                yMax = spectralData.at(i);
        }
        xySeries->replace(points);
        emit yMaxChanged();
    }
}

void SpectraProvider::setSpectralData(QList<int> spectralData)
{
    qDebug() << Q_FUNC_INFO << spectralData;
    if(spectralData.size() == valuesInFrame)
    {
        this->spectralData = spectralData;
        emit dataChanged();
    }
}
