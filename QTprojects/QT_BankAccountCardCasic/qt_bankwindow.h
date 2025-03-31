#ifndef QT_BANKWINDOW_H
#define QT_BANKWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class QTBankWindow;
}
QT_END_NAMESPACE

class QTBankWindow : public QMainWindow
{
    Q_OBJECT

public:
    QTBankWindow(QWidget *parent = nullptr);
    ~QTBankWindow();

private:
    Ui::QTBankWindow *ui;
};
#endif // QT_BANKWINDOW_H
