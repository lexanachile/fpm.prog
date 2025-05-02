#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>
#include <string>
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui {
class Calculator;
}
QT_END_NAMESPACE

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    void calculate();
    ~Calculator();

private slots:
    void on_calcButton_clicked();

    void on_dial_sliderMoved(int position);
    void rotateDone();

    void addSymbol(char chr);
    void on_clearButton_clicked();
    void on_deleteButton_clicked();
    void buttonClicked();

    void on_pb0_clicked();
    void on_pb1_clicked();
    void on_pb2_clicked();
    void on_pb3_clicked();
    void on_pb4_clicked();
    void on_pb5_clicked();
    void on_pb6_clicked();
    void on_pb7_clicked();
    void on_pb8_clicked();
    void on_pb9_clicked();
    void on_divButton_clicked();
    void on_mulButton_clicked();
    void on_minusButton_clicked();
    void on_plusButton_clicked();
    void on_pbOpenBracket_clicked();
    void on_pbCloseBracket_clicked();

    void on_up_clicked();
    void on_mid_clicked();
    void on_bottom_clicked();

private:
    short countOfRotates = 0;
    short indexUp = 0;
    short indexMid = 0;
    short indexBottom = 0;
    bool up, mid, bottom = false;
    std::vector<QString> colors = {"red", "yellow", "green", "blue", "magenta", "cyan", "purple"};
    bool isRotating = false;
    bool isResult = false;
    short lastPos = 0;
    std::string input = "";
    Ui::Calculator *ui;
};
#endif // CALCULATOR_H
