#include <QCoreApplication>
#include <QRegularExpression>
#include <QString>
#include <QDebug>
#include <QFile>
#include <QTextStream>

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "russian");
    QCoreApplication a(argc, argv);

    QString path = "data.txt";
    QFile file(path);

    QTextStream out(stdout);

    if(!file.open(QIODevice::ReadWrite)){
        out << "11";
    }
    QTextStream ff(&file);

    QString dataString = ff.readAll(); //"29.02.2025";
    dataString.resize(10);

    ff.seek(0);
    ff << dataString;
    out << "Before writing: " << dataString << Qt::endl;

    QRegularExpression reg("((0[1-9]|1[0-9]|2[0-8])\\.02\\.2025)");

    ff << Qt::endl;
    if (reg.match(dataString).hasMatch())
    {
        out << dataString << " is a date of February 2025." << Qt::endl;
        ff << dataString << " is a date of February 2025." << Qt::endl;
    }
    else
    {
        out << dataString << " is NOT a date of February 2025." << Qt::endl;
        ff << dataString << " is NOT a date of February 2025." << Qt::endl;
    }
    file.close();
    return a.exec();
}
