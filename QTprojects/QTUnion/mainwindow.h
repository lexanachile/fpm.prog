#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "listwindow.h"
#include "union.h"
#include <QMap>

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
    int  checkGroup(int arg1);
    void on_groupCheck_valueChanged(int arg1);
    void on_group2_valueChanged(int arg1);
    void on_group1_valueChanged(int arg1);

    void on_plusButton_clicked();
    void on_minusButton_clicked();
    void on_xorButton_clicked();
    void on_intersectionButton_clicked();
    void buttonPressed(char a);
    void handleStudentsRemoved(const QList<QStudent>& students, int groupNumber);

private:
    Ui::MainWindow *ui;
    ListWindow *win;
    QMap<int, MyUnion<QStudent>> groups;
    int numOfGroups;
};
#endif // MAINWINDOW_H