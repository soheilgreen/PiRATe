#ifndef ENTTEST_H
#define ENTTEST_H

#include <QObject>

class EntTest : public QObject
{
    Q_OBJECT

public:
//    explicit EntTest(QObject *parent = nullptr);

    void entTestProgram();

    void setCommand(QString cmd);

    QString getResult() const;

signals:
    void finished(QString res);

private:
    QString command, res;

};

#endif // ENTTEST_H
