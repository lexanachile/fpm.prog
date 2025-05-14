#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    numOfGroups = 0;
    loadGroupsFromFile();
}

MainWindow::~MainWindow()
{
    saveGroupsToFile();
    delete ui;
}
void MainWindow::on_addStudButton_clicked()
{
    ui->errLabel->setText("");
    bool ok1, ok2;
    QString name = ui->fst->text();
    QString grade = ui->snd->text();
    int gradeInt = grade.toUInt(&ok1);
    QString mark = ui->thd->text();
    double markDouble = mark.toDouble(&ok2);
    if(markDouble < 0) ok2 = false;
    int currGroup = ui->groupSelect->value();

    if(ok1 && ok2 && (gradeInt >= 0 && gradeInt <= 12) && (markDouble >= 0 && markDouble <= 12)) {
        //win->addStud(name, grade, mark);
        MyUnion<QStudent>& unionSet = groups[currGroup];
        QStudent x(name, grade, mark);
        unionSet = unionSet + MyUnion<QStudent>(x);
        ui->errLabel->setText("Accept");
    }
    else ui->errLabel->setText("Error");

}
void MainWindow::on_newWindowButton_clicked()
{
    win = new ListWindow;
    win->setAttribute(Qt::WA_DeleteOnClose);

    int currGroup = ui->groupCheck->value();
    if(groups.contains(currGroup)) {
        MyUnion<QStudent>& unionSet = groups[currGroup];
        win->setTable(unionSet, currGroup);

        connect(win, &ListWindow::studentsRemoved,
                this, &MainWindow::studentsRemoved);

        win->show();
    }
    else
        return;
}

void MainWindow::studentsRemoved(const QList<QStudent>& students, int groupNumber)
{
    if (!groups.contains(groupNumber)) return;

    MyUnion<QStudent>& currentGroup = groups[groupNumber];
    MyUnion<QStudent> newGroup;

    QStudent* array = currentGroup.getArray();
    for (int i = 0; i < currentGroup.getLength(); ++i) {
        bool shouldKeep = true;
        for (const QStudent& student : students) {
            if (array[i] == student) {
                shouldKeep = false;
                break;
            }
        }
        if (shouldKeep) {
            newGroup = newGroup + MyUnion<QStudent>(array[i]);
        }
    }

    groups[groupNumber] = newGroup;
}

int MainWindow::checkGroup(int arg1){
    QList<int> keysList = groups.keys();
    if (keysList.isEmpty()) {
        return 0;
    }
    if (groups.contains(arg1)) {
        return arg1;
    }

    std::sort(keysList.begin(), keysList.end());
    int closest = keysList[0];
    for (int key : keysList) {
        if (key >= arg1) {
            closest = key;
            break;
        }
    }
    return closest;
}

void MainWindow::on_groupCheck_valueChanged(int arg1)
{
    ui->groupCheck->setValue(checkGroup(arg1));
}
void MainWindow::on_group2_valueChanged(int arg1)
{
    ui->group2->setValue(checkGroup(arg1));
}
void MainWindow::on_group1_valueChanged(int arg1)
{
    ui->group1->setValue(checkGroup(arg1));
}



void MainWindow::on_plusButton_clicked()
{
    buttonPressed('+');
}
void MainWindow::on_minusButton_clicked()
{
    buttonPressed('-');
}
void MainWindow::on_xorButton_clicked()
{
    buttonPressed('*');
}
void MainWindow::on_intersectionButton_clicked()
{
    buttonPressed('/');
}

void MainWindow::buttonPressed(char a){
    int x = ui->group1->value();
    int y = ui->group2->value();
    int z = ui->groupResult->value();
    MyUnion<QStudent>& X = groups[x];
    MyUnion<QStudent>& Y = groups[y];
    MyUnion<QStudent> Z;
    switch (a) {
    case '+':{
        Z = X + Y;
        break;
    }
    case '-':{
        Z = X - Y;
        break;
    }
    case '/':{
        Z = X / Y;
        break;
    }
    case '*':{
        Z = X * Y;
        break;
    }
    default:
        break;
    }
    groups[z] = Z;
}
void MainWindow::saveGroupsToFile() {
    QFile file(FILE_NAME);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Cannot open file for writing:" << FILE_NAME;
        return;
    }

    QTextStream out(&file);
    out << groups.size() << "\n";
    
    for (auto it = groups.begin(); it != groups.end(); ++it) {
        out << it.key() << "\n";
        out << it.value();
    }

    file.close();
}

void MainWindow::loadGroupsFromFile() {
    QFile file(FILE_NAME);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Cannot open file for reading:" << FILE_NAME;
        return;
    }

    QTextStream in(&file);
    groups.clear();

    QString line = in.readLine();
    int groupCount = line.toInt();

    for (int i = 0; i < groupCount; ++i) {
        line = in.readLine();
        int groupNumber = line.toInt();

        MyUnion<QStudent> group;
        in >> group;
        
        if (!group.getLength()) continue;
        groups[groupNumber] = group;
    }

    file.close();
}
