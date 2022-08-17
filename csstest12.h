#ifndef CSSTEST12_H
#define CSSTEST12_H

#include <QObject>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cassert>
#include <sys/stat.h>

#include <gmpxx.h>


class CssTest12: public QObject
{

    Q_OBJECT

public:
    CssTest12(): VERBOSES(0) {}

    void StartTest();

    void setPath(QString str);
    void setCarmichaelPath(QString str);
    bool solovaytest(mpz_class &n);
    void setGlobalOffset(unsigned long long offset);
    static void setBitFlip(int bitFlip);
    void setVerbose(int verbose);
    static int BIT_FLIP; // MS: if set to 1, flip every input bit (i.e., test the complemented sequence)

    QString getResult() const;

signals:
    void finished(QString res);
    void verboseData(QString data);

private:
    QString path, carmichaelPath, res;
    unsigned long gOffset;
    int VERBOSES; // MS: set to 1 for status output

};

#endif // CSSTEST12_H
