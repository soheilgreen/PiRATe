#ifndef NIST_SP800_90BTEST_H
#define NIST_SP800_90BTEST_H

#include <QObject>

class NIST_SP800_90BTest : public QObject
{
    Q_OBJECT

    const QString commandIID = "Tests/NIST_SP800_90B/ea_iid ";
    const QString commandNONIID = "Tests/NIST_SP800_90B/ea_non_iid ";

public:
    explicit NIST_SP800_90BTest(QObject *parent = nullptr): QObject(parent), testType(TestType::noniid)
    {}

    enum TestType{noniid, iid};


    void startTest();

    void noniidTest();
    void iidTest();

    void setTestType(TestType type);
    void setPath(QString path);
    QString getResult() const;

signals:
    void finished(QString res);
    void verboseData(QString data);

private:
    QString path, res;
    TestType testType;
};

#endif // NIST_SP800_90BTEST_H
