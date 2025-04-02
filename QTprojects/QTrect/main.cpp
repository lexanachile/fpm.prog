#include <QCoreApplication>
#include <iostream>
#include <math.h>
#include <QFile>
#include <QTextStream>
#include <QDataStream>

using namespace std;

class MyRect
{
protected:
    int x1,x2,y1,y2;
public:
    MyRect(int _x1, int _x2, int _y1, int _y2): x1(_x1), x2(_x2), y1(_y1), y2(_y2) {}
    virtual double square()
    {
        return abs((x1-x2)*(y1-y2));
    }
    virtual double perimeter()
    {
        return 2*(abs(x1-x2)+abs(y1-y2));
    }
    friend QTextStream &operator>>(QTextStream &in, MyRect &r);
    friend QTextStream &operator<<(QTextStream &out, MyRect &r);
};
class MyTriangle: public MyRect
{
public:
    MyTriangle(int _x1, int _x2, int _y1, int _y2) : MyRect(_x1, _x2, _y1, _y2) {}
    double square()
    {
        return MyRect::square()*0.5;
    }
    double perimeter()
    {
        return abs(x1-x2)+2*(sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)/4));
    }
};

class MyRhomb: public MyRect
{
public:
    MyRhomb(int _x1, int _x2, int _y1, int _y2) : MyRect(_x1, _x2, _y1, _y2) {}
    double square()
    {
        return MyRect::square()*0.5;
    }
    double perimeter()
    {
        return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)*2)*2;
    }
};

QTextStream &operator>>(QTextStream &in, MyRect &r){
    in >> r.x1 >> r.y1 >> r.x2 >> r.y2;
    return in;
};
QTextStream &operator<<(QTextStream &out, MyRect &r){
    out << r.x1 << " " << r.y1 << " " << r.x2 << " " << r.y2 << Qt::endl;
    return out;
};


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString path = "C:\\Users\\yaras\\OneDrive\\Dokumente\\GitHub\\fpm.prog\\QTprojects\\QTrect\\build\\rect.txt";
    QFile file(path);
    file.open(QIODevice::WriteOnly);
    QTextStream ft(&file);
    MyRect b(1, 1, 2, 2);
    ft << b;
    ft << b;
    return a.exec();
}

