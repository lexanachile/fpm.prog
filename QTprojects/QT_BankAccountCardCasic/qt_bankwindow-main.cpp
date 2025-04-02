#include "qt_bankwindow.h"

#include <QApplication>
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
     QApplication app(argc, argv);

     QTBankWindow window;
     window.setWindowTitle("Bank app");
     window.show();{


     }
    return app.exec();
}
