#ifndef LISTWINDOW_H
#define LISTWINDOW_H

#include <QDialog>
#include <QListWidget>

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

private slots:
    void on_pushButton_clicked();

private:
    Ui::ListWindow *ui;
    int rows;
};

#endif // LISTWINDOW_H
