#ifndef CSSTEST4_H
#define CSSTEST4_H

#include <QObject>

class CssTest4 : public QObject
{
    Q_OBJECT

public:
    CssTest4(){}

    void cssTest4StartTest();

    void setPath(QString str);
    void setCRandom(int cRandom);
    void setBitFlip(int bitFlip);
    static int BIT_FLIP;

    QString getResult() const;

signals:
    void finished(QString res);
    void verboseData(QString data);

private:
    QString path, res;
    int cRandom;
};

#endif // CSSTEST4_H
