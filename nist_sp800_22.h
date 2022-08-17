#ifndef NIST_SP800_22_H
#define NIST_SP800_22_H

#include <QObject>

class NIST_SP800_22 : public QObject
{
    Q_OBJECT

#ifdef _Win32
    const QString filePath = "Tests/NIST_SP800_22/rnd_test.exe";
    const QString command = "rnd_test.exe ";
#else
    const QString filePath = "Tests/NIST_SP800_22/rnd_test";
    const QString configFilpath = "Tests/NIST_SP800_22/config.json";
    const QString command = "./rnd_test ";

#endif
public:
//    explicit NIST_SP800_22(QObject *parent = nullptr);

    void startTest();

    void setPath(QString path);
    QString getResult() const;
signals:
    void finished(QString res);


private:
    QString path, res;

};

#endif // NIST_SP800_22_H
