#ifndef BORELTEST_H
#define BORELTEST_H

#include <QObject>


class BorelTest : public QObject
{

    Q_OBJECT

public:
    BorelTest(): VERBOSE(1) {}
    void StartTest();
    void setPath(QString path);
    void setVerbose(int verboes);

signals:
    void finished(QString res);
    void error(QString err);

private:
    QString path;
    int VERBOSE; // MS: set to 1 for expanded status output

};

#endif // BORELTEST_H
