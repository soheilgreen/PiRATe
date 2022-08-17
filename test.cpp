#include "test.h"
#include <cstdio>
#include <QApplication>
#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QThread>
#include <QFile>
#include <QTextStream>

#include "boreltest.h"
#include "csstest.h"
#include "csstest4.h"
#include "csstest12.h"
#include "enttest.h"
#include "nist_sp800_90btest.h"
#include "dieharder.h"
#include "nist_sp800_22.h"

Test::Test(QObject *parent)
    : QObject{parent}
{

}


//void Test::testStart()
//{
//    //Just Get Emmited
//}




Q_INVOKABLE QString Test::entTest(const QString path)
{
    if(path.isEmpty())
        return "Path is Empty!";

    QString res;
    QString command = ((QDir::currentPath() + "/" + ENT_TEST_PATH + path));

//    Q_ASSERT(QMetaObject::invokeMethod(this, "entTestProgram", Qt::QueuedConnection, Q_ARG(QString, command), Q_ARG(QString&, res)));
//    QThread *thread = QThread::create([&]{entTestProgram(command, res);});
//    thread->setObjectName("EntTest");

    EntTest* test = new EntTest();
    test->setCommand(command);

    QThread* thread = new QThread(this);
    test->moveToThread(thread);

    connect(test, &EntTest::finished, thread, &QThread::quit);
    connect(thread, &QThread::started, test, &EntTest::entTestProgram);
    connect(test, &EntTest::finished, this, &Test::testFinished);
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);
    connect(test, &EntTest::finished, thread, &EntTest::deleteLater);

    //Emit Signal
    emit testStart();
    QApplication::processEvents();

    thread->start();
//    thread->wait();


    return res;

}

Q_INVOKABLE QString Test::getResult() const
{ return this->result; }


void Test::testFinished(QString res)
{
    result = res;
    emit finished(res);
}

Q_INVOKABLE QString Test::borelTest(const QString path, int verbose)
{
    if(path.isEmpty())
        return "Path is Empty!";

    QString res;

//    Q_ASSERT(QMetaObject::invokeMethod(this, "entTestProgram", Qt::QueuedConnection));
    BorelTest* test = new BorelTest;
    QThread* thread = new QThread;

    test->moveToThread(thread);
    test->setPath(path);
    test->setVerbose(verbose);

    thread->setObjectName("Borel Test");

    connect(thread, &QThread::started, test, &BorelTest::StartTest);
    connect(test, &BorelTest::finished, thread, &QThread::quit);

//    connect(test, &BorelTest::finished, this, [&](QString result){res=result;});
    connect( test, &BorelTest::finished, thread, &BorelTest::deleteLater);
    connect( thread, &QThread::finished, thread, &QThread::deleteLater);
    connect (test, &BorelTest::finished, this, &Test::testFinished);

    emit testStart();
    QApplication::processEvents();

    thread->start();

//    thread->wait();
//    delete test;
//    delete thread;

    return res;

}

Q_INVOKABLE QString Test::ssTest3(const QString path, const QString cmPath, int bitFlip, int verbose, int charmichaelNumbers)
{
    if(path.isEmpty())
        return "Path is Empty!";

    if(cmPath.isEmpty())
        return "Cm Path is Empty";


    QString res;

    CssTest3* test = new CssTest3;
    QThread* thread = new QThread;
    test->moveToThread(thread);

    test->setCarmichealNumber(charmichaelNumbers);
    test->setBitflip(bitFlip);
    test->setCmPath(cmPath);
    test->setPath(path);
    test->setVerbose(verbose);


    thread->setObjectName("CSS 3 Test");

    connect(test, &CssTest3::finished, this, &Test::testFinished);
    connect(thread, &QThread::started, test, &CssTest3::cssTest3Start);
    connect(test, &CssTest3::finished, thread, &QThread::quit);
    connect(test, &CssTest3::verboseData, this, &Test::verboseDataSlot);


    connect(test, &CssTest3::finished, thread, &CssTest3::deleteLater);
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);
//    Q_ASSERT(QMetaObject::invokeMethod(this, "entTestProgram", Qt::QueuedConnection));
//    QThread *thread = QThread::create([&]{CssTest3::cssTest3Start(path, cmPath, res, charmichaelNumbers);});
//    thread->setObjectName("Css Test 3");

    emit testStart();
    QApplication::processEvents();

    thread->start();
//    thread->wait();


    return res;
}


Q_INVOKABLE QString Test::ssTest4(const QString path, const QString carmicaelFilePath, int bitFlip, int random)
{
    if(path.isEmpty())
        return "Path is Empty!";

    if(carmicaelFilePath.isEmpty())
        return "carmicael File Path is Empty!";

    QString res;

//    Q_ASSERT(QMetaObject::invokeMethod(this, "entTestProgram", Qt::QueuedConnection));
//    QThread *thread = QThread::create([&]{CssTest4::cssTest4StartTest(path, carmicaelFilePath, res, random);});
//    thread->setObjectName("Css Test 4");
    CssTest4* test = new CssTest4();
    test->setPath(path);
    test->setCRandom(random);
    test->setBitFlip(bitFlip);

    QThread* thread = new QThread(this);
    test->moveToThread(thread);
    thread->setObjectName("CSS 4 Test");

    connect(thread, &QThread::started, test, &CssTest4::cssTest4StartTest);
    connect(test, &CssTest4::finished, thread, &QThread::quit);

    connect(test, &CssTest4::finished, this, &Test::testFinished);
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);
    connect(test, &CssTest4::finished, thread, &CssTest4::deleteLater);

    emit testStart();
    QApplication::processEvents();

    thread->start();
//    thread->wait();


    return res;
}


Q_INVOKABLE QString Test::ssTest12(const QString path, const QString carmicaelFilePath, int bitFlip, int verbose, int gOffset)
{
    if(path.isEmpty())
        return "Path is Empty!";

    if(carmicaelFilePath.isEmpty())
        return "carmicael File Path is Empty!";

    QString res;

//    Q_ASSERT(QMetaObject::invokeMethod(this, "entTestProgram", Qt::QueuedConnection));
//    QThread *thread = QThread::create([&]{CssTest12::StartTest(path, carmicaelFilePath, res, gOffset);});
//    thread->setObjectName("Css Test 1,2");

    CssTest12* test = new CssTest12();
    test->setCarmichaelPath(carmicaelFilePath);
    test->setPath(path);
    test->setGlobalOffset(gOffset);
    test->setBitFlip(bitFlip);
    test->setVerbose(verbose);

    QThread* thread = new QThread(this);
    test->moveToThread(thread);
    thread->setObjectName("CSS 12 Test");

    connect(thread, &QThread::started, test, &CssTest12::StartTest);
    connect(test, &CssTest12::finished, thread, &QThread::quit);
    connect(test, &CssTest12::verboseData, this, &Test::verboseDataSlot);

    connect(test, &CssTest12::finished, this, &Test::testFinished);
    connect(thread, &QThread::finished, test, &QThread::deleteLater);
    connect(test, &CssTest12::finished, thread, &CssTest12::deleteLater);

    emit testStart();
    QApplication::processEvents();

    thread->start();
//    thread->wait();


    return res;

}

Q_INVOKABLE QString Test::nist_Test(const QString path, const int testMode)
{
    if(path.isEmpty())
        return "Path is Empty!";

    QString res = "";

    NIST_SP800_90BTest* test = new NIST_SP800_90BTest();
    test->setPath(path);
    test->setTestType((testMode == 0 ? NIST_SP800_90BTest::TestType::noniid : NIST_SP800_90BTest::TestType::iid));

    QThread* thread = new QThread(this);
    test->moveToThread(thread);
    thread->setObjectName("CSS NIST_SP800_90BTest Test");

    connect(thread, &QThread::started, test, &NIST_SP800_90BTest::startTest);
    connect(test, &NIST_SP800_90BTest::finished, this, &Test::testFinished);
    connect(test, &NIST_SP800_90BTest::verboseData, this, &Test::verboseDataSlot);
    connect(test, &NIST_SP800_90BTest::finished, thread, &QThread::quit);
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);
    connect(test, &NIST_SP800_90BTest::finished, thread, &NIST_SP800_90BTest::deleteLater);

    emit testStart();

    thread->start();

    return res;
}

Q_INVOKABLE QString Test::dieharderTest(const QString path)
{
    if(path.isEmpty())
        return "Path is Empty!";

    QString res;
//    Q_ASSERT(QMetaObject::invokeMethod(this, "entTestProgram", Qt::QueuedConnection, Q_ARG(QString, command), Q_ARG(QString&, res)));
//    QThread *thread = QThread::create([&]{entTestProgram(command, res);});
//    thread->setObjectName("EntTest");

    Dieharder* test = new Dieharder();
    test->setPath(path);
    QThread* thread = new QThread(this);
    test->moveToThread(thread);
    thread->setObjectName("Dieharder Test");

    connect(test, &Dieharder::finished, thread, &QThread::quit);
    connect(thread, &QThread::started, test, &Dieharder::startTest);
    connect(test, &Dieharder::finished, this, &Test::testFinished);
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);
    connect(test, &Dieharder::finished, thread, &Dieharder::deleteLater);

    //Emit Signal
    emit testStart();
    QApplication::processEvents();

    thread->start();
//    thread->wait();


    return res;

}

Q_INVOKABLE QString Test::nist_sp800_22Test(const QString path)
{
    if(path.isEmpty())
        return "Path is Empty!";

    QString res;
//    Q_ASSERT(QMetaObject::invokeMethod(this, "entTestProgram", Qt::QueuedConnection, Q_ARG(QString, command), Q_ARG(QString&, res)));
//    QThread *thread = QThread::create([&]{entTestProgram(command, res);});
//    thread->setObjectName("EntTest");

    NIST_SP800_22* test = new NIST_SP800_22();
    test->setPath(path);
    QThread* thread = new QThread(this);
    test->moveToThread(thread);
    thread->setObjectName("NIST_SP800_22 Test");

    connect(test, &NIST_SP800_22::finished, thread, &QThread::quit);
    connect(thread, &QThread::started, test, &NIST_SP800_22::startTest);
    connect(test, &NIST_SP800_22::finished, this, &Test::testFinished);
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);
    connect(test, &NIST_SP800_22::finished, thread, &NIST_SP800_22::deleteLater);

    //Emit Signal
    emit testStart();
    QApplication::processEvents();

    thread->start();
//    thread->wait();


    return res;
}



void Test::started()
{
    emit testStart();
}

void Test::verboseDataSlot(QString data)
{
    emit verboseData(data);
//    QCoreApplication::processEvents();
}

Q_INVOKABLE QString Test::openFileDialog(bool save)
{
    QString path;
    if(!save)
        path = QFileDialog::getOpenFileName(nullptr, "Choose a File pls");
    else
        path = QFileDialog::getSaveFileName(nullptr, "Choose Path to save");

    return path;
}

Q_INVOKABLE void Test::saveResult(const QString path, const QStringList result)
{
    QString res = "";

   QFile file(path);
   if(!file.open(QIODevice::Append | QIODevice::WriteOnly))
   {
        res += "Faild to open file " + path;
        emit finished(res);
   }

   QTextStream stream(&file);

   for(auto &t : result)
       stream << t << "\n\n";

   file.close();

   res += "Done";

   emit finished(res);

}

