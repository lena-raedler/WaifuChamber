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
    void on_pushButton_0_clicked();
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_9_clicked();

    void on_pushButton_plus_clicked();

    void on_pushButton_equals_clicked();

    void on_pushButton_clear_clicked();

private:
    Ui::Calculator *ui;
    QString input;
    int inputNumbersCount;
    int inputOperationsCount;
    QVector<QString> inputNumbers;
    QVector<QString> inputOperations;
    void updateInput();
    void preprocessInput();
    bool isOperation(QChar c);
    void plusAndMinus();
    double calculateResult(double a, double b, QString operation);
    void clearCalculator();
};
#endif // CALCULATOR_H
