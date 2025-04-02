#include "qt_bankwindow.h"
#include "./ui_qtbankwindow.h"
#include <iostream>
#include "bankaccountcard.h"

QTBankWindow::QTBankWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::QTBankWindow)
{
    ui->setupUi(this);
    std::cout << "start" << std::endl;

    Bank Alpha("AlphaBank");
    int acc1num = Alpha.openAccount("Lexa");
    int acc2num = Alpha.openAccount("Grisha");
    Alpha.addCard(acc1num);
    Alpha.addCard(acc2num);
    Alpha.deposit(1000);
    Alpha.getBalance();
}

QTBankWindow::~QTBankWindow()
{
    delete ui;
    std::cout << std::endl << "end" << std::endl;
}


