#ifndef LISTWINDOW_H
#define LISTWINDOW_H

#include <QDialog>
#include <QListWidget>
#include "union.h"

namespace Ui {
class ListWindow;
}

class ListWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ListWindow(QWidget *parent = nullptr);
    ~ListWindow();
    void addStud(QString &stud, QString &grade, QString &mark);
    void setTable(const MyUnion<QStudent>& x, int groupNumber);

signals:
    void studentsRemoved(const QList<QStudent>& students, int groupNumber);

private slots:
    void on_pushButton_clicked();

private:
    Ui::ListWindow *ui;
    int rows;
    int currentGroup;
};

#endif // LISTWINDOW_H