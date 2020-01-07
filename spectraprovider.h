#ifndef SPECTRAPROVIDER_H
#define SPECTRAPROVIDER_H

#include <QObject>
#include <QDebug>
#include <QXYSeries>

QT_CHARTS_USE_NAMESPACE

class SpectraProvider : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qreal yMax READ getYMax NOTIFY yMaxChanged)
public:
    explicit SpectraProvider(QObject *parent = nullptr);
    Q_INVOKABLE void updateSeries(QAbstractSeries *series);
    Q_INVOKABLE int getYMax() { return yMax; }

public slots:
    void setSpectralData(QList<int> spectralData);

signals:
    void dataChanged();
    void yMaxChanged();

private:
    QList<int> spectralData;
    int yMax{1};
    const int valuesInFrame{18};
    const int xOffset{410};
    const int xStep{35};
};

#endif // SPECTRAPROVIDER_H
