#include "nist_sp800_22.h"
#include <QDebug>

//NIST_SP800_22::NIST_SP800_22(QObject *parent)
//    : QObject{parent}
//{

//}


void NIST_SP800_22::startTest()
{
    char result[1024];    *result = '\0';
    res = "";

    //Go to path
#ifdef _Win32

#else
    QString c = "ln -s " + filePath;
#endif
    FILE* cmd = popen(c.toStdString().c_str(), "r");
    if(!cmd)
    {
        res += "Faild to open file: " + filePath;
        emit finished(res);
        return;
    }
    pclose(cmd);

#ifdef _Win32

#else
    c = "ln -s " + configFilpath;
#endif

    cmd = popen(c.toStdString().c_str(), "r");
    if(!cmd)
    {
        res += "Faild to open file: " + filePath;
        emit finished(res);
        return;
    }
    pclose(cmd);


     c = command + path;
    cmd = popen(c.toStdString().c_str(), "r");
    if (cmd)
    {
        while (!feof(cmd))
            if (fgets(result, 1024, cmd) != NULL) res.append(result);
        if(pclose(cmd) == -1) res = "Process Terminated!";
    }

    emit finished(res);
}

void NIST_SP800_22::setPath(QString path)
{ this->path = path; }
QString NIST_SP800_22::getResult() const
{ return res; }
