#include "calculator.h"
#include "./ui_calculator.h"
#include "polska.h"
#include <string>
#include <QPixmap>
#include <QLabel>
#include <QString>
#include <QFile>

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);
    ui->dial->setRange(0, 99);
    ui->dial->setWrapping(true);
    ui->dial->setNotchesVisible(true);
    ui->rotatesCount->setText(QString::number(3 - Calculator::countOfRotates));
    ui->calcButton->hide();
    ui->noseButton->setFixedSize(20, 20);  // Устанавливаем квадратный размер
    ui->noseButton->setStyleSheet(
        "QPushButton {"
        "    background-color: transparent;"   // прозрачный фон кнопки
        "    border: none;"             // без границ
        "    border-radius: 10px;"       // радиус равен половине ширины/высоты
        "}"
        );

    //ui->clown->setStyleSheet("QLabel { background-image: qrc:/clown.jpg; }");
    //ui->clown->setStyleSheet("background-image: url(C:/Users/yaras/OneDrive/Dokumente/GitHub/fpm.prog/QTprojects/QTPolCalculator/clown1.png);");
    //ui->clown->setStyleSheet("background-image: url(qrc:/new/prefix1/clown1.png);");
    //ui->graphicsView->setStyleSheet("background-image: url(qrc:/new/prefix1/clown1.png);");
    // QPixmap pixmap(":/images/clown1.png");
    // if (pixmap.isNull()){
    //     qDebug() << "Не удалось загрузить изображение из ресурсов!";
    // } else {
    //     qDebug() << "Изображение успешно загружено.";
    // }




    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    Calculator::indexUp = rand() % Calculator::colors.size();
    ui->up->setStyleSheet(QString("background-color: %1;").arg(Calculator::colors[Calculator::indexUp]));
    Calculator::indexMid = rand() % Calculator::colors.size();
    ui->mid->setStyleSheet(QString("background-color: %1;").arg(Calculator::colors[Calculator::indexMid]));
    Calculator::indexBottom = rand() % Calculator::colors.size();
    ui->bottom->setStyleSheet(QString("background-color: %1;").arg(Calculator::colors[Calculator::indexBottom]));




}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::on_calcButton_clicked() {
    Calculator::calculate();
}

void Calculator::calculate(){
    if(Calculator::isResult) return;
    Calculator::input = ui->inpLine->text().toStdString();
    std::string &input = Calculator::input;
    if(input == "" || input == "0") {
        input = "";
        ui->inpLine->setText(QString::number(0));
        return;
    }
    else try{
        //vector<pair<string, int>> v = {{"+", 1},{"-", 1}, {"*", 2}, {"/", 2}, {"^", 3}};
        PolCalc calc;
        QString output = QString::fromStdString(Calculator::input + " = " + std::to_string(calc.calculate(input)));
        ui->inpLine->setText(output);
        Calculator::isResult = true;
    }
    catch(PolCalcException err){
        ui->outpLine->setText(QString::fromStdString(err.what()));;
    }
}

void Calculator::rotateDone(){
    ++Calculator::countOfRotates;
    ui->rotatesCount->setText(QString::number(3 - Calculator::countOfRotates));
    if(Calculator::countOfRotates == 3){
        Calculator::calculate();
        Calculator::countOfRotates = 0;
        ui->rotatesCount->setText(QString::number(3 - Calculator::countOfRotates));
    }
}
void Calculator::on_dial_sliderMoved(int position)
{
    if(Calculator::isRotating){
        if(position < lastPos) {
            Calculator::isRotating = false;
            return;
        }
        if(position >= 95) {
            Calculator::rotateDone();
            Calculator::isRotating = false;
        }
    }
    else if(position <= 5) Calculator::isRotating = true;
}


void Calculator::on_clearButton_clicked()
{
    Calculator::input = "";
    ui->inpLine->setText(QString::number(0));
    Calculator::buttonClicked();
}
void Calculator::buttonClicked()
{
    Calculator::countOfRotates = 0;
    ui->rotatesCount->setText(QString::number(3 - Calculator::countOfRotates));
    Calculator::isResult = false;
}
void Calculator::on_deleteButton_clicked()
{
    if(Calculator::isResult){
        Calculator::buttonClicked();
        ui->inpLine->setText(QString::fromStdString(Calculator::input));
        return;
    }
    if(Calculator::input.size() > 0){
        Calculator::buttonClicked();
        Calculator::input.pop_back();
    ui->inpLine->setText(QString::fromStdString(Calculator::input));
    }
}

void Calculator::addSymbol(char chr){
    Calculator::input.push_back(chr);
    ui->inpLine->setText(QString::fromStdString(Calculator::input));
    Calculator::buttonClicked();
}

void Calculator::on_pb0_clicked()
{
    Calculator::addSymbol('0');
}
void Calculator::on_pb1_clicked()
{
   Calculator::addSymbol('1');
}
void Calculator::on_pb2_clicked()
{
    Calculator::addSymbol('2');
}
void Calculator::on_pb3_clicked()
{
    Calculator::addSymbol('3');
}
void Calculator::on_pb4_clicked()
{
    Calculator::addSymbol('4');
}
void Calculator::on_pb5_clicked()
{
    Calculator::addSymbol('5');
}
void Calculator::on_pb6_clicked()
{
    Calculator::addSymbol('6');
}
void Calculator::on_pb7_clicked()
{
    Calculator::addSymbol('7');
}
void Calculator::on_pb8_clicked()
{
    Calculator::addSymbol('8');
}
void Calculator::on_pb9_clicked()
{
    Calculator::addSymbol('9');
}
void Calculator::on_divButton_clicked()
{
        Calculator::addSymbol('/');
}
void Calculator::on_mulButton_clicked()
{
    Calculator::addSymbol('*');
}
void Calculator::on_minusButton_clicked()
{
    Calculator::addSymbol('-');
}
void Calculator::on_plusButton_clicked()
{
    Calculator::addSymbol('+');
}
void Calculator::on_pbOpenBracket_clicked()
{
    Calculator::addSymbol('(');
}
void Calculator::on_pbCloseBracket_clicked()
{
    Calculator::addSymbol(')');
}


void Calculator::on_up_clicked()
{
    ++Calculator::indexUp;
    Calculator::indexUp %= colors.size() ;
    ui->up->setStyleSheet(QString("background-color: %1;").arg(Calculator::colors[Calculator::indexUp]));
    if(Calculator::colors[Calculator::indexUp] == "red") {
        Calculator::up = true;
        if(Calculator::mid && Calculator::bottom) ui->calcButton->show();
    }
    else up = false;
}


void Calculator::on_mid_clicked()
{
    ++Calculator::indexMid;
    indexMid %= colors.size();
    ui->mid->setStyleSheet(QString("background-color: %1;").arg(Calculator::colors[Calculator::indexMid]));
    if(Calculator::colors[Calculator::indexMid] == "yellow") {
        Calculator::mid = true;
        if(Calculator::up && Calculator::bottom) ui->calcButton->show();
    }
    else mid = false;
}


void Calculator::on_bottom_clicked()
{
    ++Calculator::indexBottom;
    indexBottom %= colors.size();
    ui->bottom->setStyleSheet(QString("background-color: %1;").arg(Calculator::colors[Calculator::indexBottom]));
    if(Calculator::colors[Calculator::indexBottom] == "green") {
        Calculator::bottom = true;
        if(up && mid) ui->calcButton->show();
    }
    else bottom = false;
}
