#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>
#include <string>

QT_BEGIN_NAMESPACE
namespace Ui { class Calculator; }
QT_END_NAMESPACE

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Calculator *ui;
    std::string input;
};
#endif // CALCULATOR_H
