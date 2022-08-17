#ifndef TEST_H
#define TEST_H

#include <QObject>
#include <QFileDialog>

class Test : public QObject
{
    Q_OBJECT

#ifdef _WIN32
    const QString ENT_TEST_PATH = "Tests/ENT/ent.exe -b ";
#else
    const QString ENT_TEST_PATH = "Tests/ENT/ent -b ";
#endif

public:
    explicit Test(QObject *parent = nullptr);

    Q_INVOKABLE QString entTest(const QString Path);
    Q_INVOKABLE QString borelTest(const QString Path, int verbose = 1);
    Q_INVOKABLE QString ssTest3(const QString path, const QString cmPath, int bitFlip = 1, int verbose = 1, int charmichaelNumbers = -1);
    Q_INVOKABLE QString ssTest4(const QString path, const QString carmicaelFilePath, int bitFlip = 0, int random = 0);
    Q_INVOKABLE QString ssTest12(const QString path, const QString carmicaelFilePath, int bitFlip = 1, int verbose = 0, int gOffset = 0);
    Q_INVOKABLE QString nist_Test(const QString path, const int testMode = 0);
    Q_INVOKABLE QString dieharderTest(const QString path);
    Q_INVOKABLE QString nist_sp800_22Test(const QString path);
    Q_INVOKABLE void saveResult(const QString path, const QStringList result);

    Q_INVOKABLE QString openFileDialog(bool save = false);

    //getter
    Q_INVOKABLE QString getResult() const;


protected slots:
    void started();
    void testFinished(QString rse);
    void verboseDataSlot(QString data);

signals:
    void testStart();
    void finished(QString res);
    void verboseData(QString text);


private:
    QString result;
};

#endif // TEST_H
