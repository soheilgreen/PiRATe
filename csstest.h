#ifndef CssTest3_H
#define CssTest3_H

#include <QObject>


class CssTest3 : public QObject
{
    Q_OBJECT

    const QString command = "Tests/CSSS3/SS_Test3_Carm ";
    const QString commandBitFlip = "Tests/CSSS3/SS_Test3_Carm_BitFlip ";
    const QString commandVerbose = "Tests/CSSS3/SS_Test3_Carm_Verbose ";
    const QString commandVerboseBitFlip = "Tests/CSSS3/SS_Test3_Carm_Verbose_BitFlip ";


public:
    CssTest3(){}

    void cssTest3Start();
    void setPath(const QString path);
    void setCarmichealNumber(int number);
    void setCmPath(QString cmPath);
    static void setBitflip(int bitflip);
    static void setVerbose(int verbose);

    static int BIT_FLIP; // MS: if set to 1, flip every input bit (i.e., test the complemented sequence)
    static int VERBOSE; // MS: set to 1 for expanded status output


    QString getResult() const;

signals:
    void finished(QString res);
    void verboseData(QString data);

private:
    int carmichaelNumber;
    QString path, res, cmPath;

};

#endif // CssTest3_H
