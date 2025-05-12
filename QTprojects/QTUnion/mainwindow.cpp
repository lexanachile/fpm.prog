#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    win = new ListWindow;
    //win->setAttribute(Qt::WA_DeleteOnClose);
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::addStud(QString name, int grade, double mark){

    ui->errLabel->setText("Accept");
}
void MainWindow::on_addStudButton_clicked()
{
    ui->errLabel->setText("");
    bool ok1, ok2;
    QString name = ui->fst->text();
    // int grade = ui->snd->text().toInt(&ok1);
    // double mark = ui->thd->text().toDouble(&ok2);
    // if(ok1 && ok2) addStud(name, grade, mark);
    // else ui->errLabel->setText("Error");
    QString grade = ui->snd->text();
    int gradeInt = grade.toInt(&ok1);
    QString mark = ui->thd->text();
    double markDouble = mark.toDouble(&ok2);
    if(ok1 && ok2 && (gradeInt >= 0 && gradeInt <= 12) && (markDouble >= 0 && markDouble <= 12)) win->addStud(name, grade, mark);
    else ui->errLabel->setText("Error");

}
void MainWindow::on_newWindowButton_clicked()
{
    win->show();
}

