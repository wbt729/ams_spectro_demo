#ifndef SPECTRALDATAPARSER_H
#define SPECTRALDATAPARSER_H

#include <QtCore>
#include <QDebug>

class SpectralDataParser
{
public:
    SpectralDataParser();
    static QList<int> parseUncalibratedData(QString response);

private:
    enum positionsReceived{
        A = 12,
        B = 13,
        C = 14,
        D = 15,
        E = 16,
        F = 17,
        G = 6,
        H = 7,
        I = 8,
        J = 9,
        K = 10,
        L = 11,
        R = 0,
        S = 1,
        T = 2,
        U = 3,
        V = 4,
        W = 5
    };
    static const int valuesPerFrame = 18;
};

#endif // SPECTRALDATAPARSER_H
