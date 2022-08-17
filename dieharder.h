#ifndef DIEHARDER_H
#define DIEHARDER_H

#include <QObject>

class Dieharder : public QObject
{
    Q_OBJECT

    const QString command = "dieharder -g 201 -f ";

public:
//    explicit Dieharder(QObject *parent = nullptr);

    void startTest();

    QString getResult() const;
    void setPath(QString path);

signals:
    void finished(QString res);

private:
    QString res, path;
};

#endif // DIEHARDER_H
