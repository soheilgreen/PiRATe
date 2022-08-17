#include "enttest.h"

//EntTest::EntTest(QObject *parent)
//    : QObject{parent}
//{

//}


void EntTest::entTestProgram()
{
    char result[1024];    *result = '\0';
    res = "";

    FILE* cmd = popen(command.toStdString().c_str(), "r");
    if (cmd)
    {
        while (!feof(cmd))
            if (fgets(result, 1024, cmd) != NULL) res.append(result);
        if(pclose(cmd) == -1) res = "Process Terminated!";
    }

    emit finished(res);
}

void EntTest::setCommand(QString cmd)
{ this->command = cmd;}

QString EntTest::getResult() const
{ return res; }
