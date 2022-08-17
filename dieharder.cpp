#include "dieharder.h"

//Dieharder::Dieharder(QObject *parent)
//    : QObject{parent}
//{

//}

void Dieharder::startTest()
{
    char result[1024];    *result = '\0';
    res = "";

    QString c = command + path + " -a";

    FILE* cmd = popen(c.toStdString().c_str(), "r");
    if (cmd)
    {
        while (!feof(cmd))
            if (fgets(result, 1024, cmd) != NULL) res.append(result);
        if(pclose(cmd) == -1) res = "Process Terminated!";
    }

    emit finished(res);
}


QString Dieharder::getResult() const
{
    return res;
}
void Dieharder::setPath(QString path)
{
    this->path = path;
}
