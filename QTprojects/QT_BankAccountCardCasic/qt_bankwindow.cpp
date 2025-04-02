#include "qt_bankwindow.h"
#include "./ui_qtbankwindow.h"
#include <iostream>
#include "bankaccountcard.h"
#include <QFile>

QTBankWindow::QTBankWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::QTBankWindow)
{
    ui->setupUi(this);
    std::cout << "start" << std::endl;
    QString filePath = "C:\\Users\\yaras\\OneDrive\\Dokumente\\GitHub\\fpm.prog\\QTprojects\\QT_BankAccountCardCasic\\bank.txt";
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Ошибка открытия файла:" << file.errorString();
        return;
    }
    QTextStream in(&file);
    int a = 2;
    in >> a;
    std::cout << a << ". Thats was a" << std::endl;

    try{
    Bank Alpha("AlphaBank");
    int acc1num = Alpha.openAccount("Lexa");
    int acc2num = Alpha.openAccount("Grisha");
    int card1 = Alpha.addCard(acc1num);
    int card2 = Alpha.addCard(acc2num);
    Alpha.OpenSession(card1, 1111);
    Alpha.deposit(1000);
    std::cout << Alpha.getBalance() << std::endl;
    Alpha.cashout(200);
     std::cout << Alpha.getBalance() << std::endl;
    Alpha.transfer(400, card2);
    std::cout << Alpha.getBalance() << std::endl;
    Alpha.closeSession();
    Alpha.OpenSession(card2, 1111);
    std::cout << Alpha.getBalance() << std::endl;
    Alpha.closeSession();
    }
    catch(const char* msg){
        std::cout<< msg << std::endl;
    }
}

QTBankWindow::~QTBankWindow()
{
    delete ui;
    std::cout << std::endl << "end" << std::endl;
}


