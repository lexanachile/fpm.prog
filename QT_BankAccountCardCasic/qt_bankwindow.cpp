#include "qt_bankwindow.h"
#include "./ui_qtbankwindow.h"

QTBankWindow::QTBankWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::QTBankWindow)
{
    ui->setupUi(this);
}

QTBankWindow::~QTBankWindow()
{
    delete ui;
}
