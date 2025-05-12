#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "listwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void addStud(QString name, int grade, double mark);
private slots:
    void on_addStudButton_clicked();
    void on_newWindowButton_clicked();

private:
    Ui::MainWindow *ui;
    ListWindow *win;
};
#endif // MAINWINDOW_H
