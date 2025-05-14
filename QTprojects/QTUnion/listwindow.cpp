#include "listwindow.h"
#include "ui_listwindow.h"
#include <QStringList>
#include <QString>
#include <QTableWidget>
#include <QList>

ListWindow::ListWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ListWindow)
{
    ui->setupUi(this);
    rows = 0;
    ui->table->setColumnCount(3);
    ui->table->setColumnWidth(0, 300);
    ui->table->setColumnWidth(1, 40);
    ui->table->setColumnWidth(2, 40);
}

ListWindow::~ListWindow()
{
    delete ui;
}
void ListWindow::addStud(QString &stud, QString &grade, QString &mark){
    ++rows;
    ui->table->setRowCount(rows);
    QTableWidgetItem *studItem = new QTableWidgetItem(stud);
    QTableWidgetItem *gradeItem = new QTableWidgetItem(grade);
    QTableWidgetItem *markItem = new QTableWidgetItem(mark);
    ui->table->setItem(rows - 1, 0, studItem);
    ui->table->setItem(rows - 1, 1, gradeItem);
    ui->table->setItem(rows - 1, 2, markItem);
}

void ListWindow::setTable(const MyUnion<QStudent>& x, int groupNumber) {
    currentGroup = groupNumber;
    rows = x.getLenth();
    ui->table->setRowCount(rows);
    QStudent* M = x.getArray();

    for (int var = 0; var < rows; ++var) {
        QTableWidgetItem *studItem = new QTableWidgetItem(M[var].getName());
        QTableWidgetItem *gradeItem = new QTableWidgetItem(M[var].getGrade());
        QTableWidgetItem *markItem = new QTableWidgetItem(M[var].getMark());

        ui->table->setItem(var, 0, studItem);
        ui->table->setItem(var, 1, gradeItem);
        ui->table->setItem(var, 2, markItem);
    }
}

void ListWindow::on_pushButton_clicked()
{
    QList<QTableWidgetItem*> items = ui->table->selectedItems();
    QList<int> rowsToRemove;
    QList<QStudent> studentsToRemove;

    for (QTableWidgetItem* item : items) {
        int row = item->row();
        if (!rowsToRemove.contains(row)) {
            rowsToRemove.append(row);

            QString name = ui->table->item(row, 0)->text();
            QString grade = ui->table->item(row, 1)->text();
            QString mark = ui->table->item(row, 2)->text();
            studentsToRemove.append(QStudent(name, grade, mark));
        }
    }
    std::sort(rowsToRemove.begin(), rowsToRemove.end(), std::greater<int>());
    int bufRow = -1;
    for(const int &row : rowsToRemove) {
        if(row == bufRow) continue;
        --rows;
        ui->table->removeRow(row);
        bufRow = row;
    }
    studentsRemoved(studentsToRemove, currentGroup);
}
