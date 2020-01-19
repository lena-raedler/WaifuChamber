#include "calculator.h"
#include "ui_calculator.h"

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
    , input("")
    , inputNumbersCount(0)
    , inputOperationsCount(0)
    , inputNumbers(16)
    , inputOperations(16)

{
    ui->setupUi(this);
}

Calculator::~Calculator()
{
    delete ui;
}


void Calculator::on_pushButton_0_clicked()
{
    //input += "0";
    inputNumbers[inputNumbersCount].push_back('0');
    updateInput();
}

void Calculator::on_pushButton_1_clicked()
{
    //input += "1";
    inputNumbers[inputNumbersCount].push_back('1');
    updateInput();
}

void Calculator::on_pushButton_2_clicked()
{
    input += "2";
    updateInput();
}

void Calculator::on_pushButton_3_clicked()
{
    input += "3";
    updateInput();
}

void Calculator::on_pushButton_4_clicked()
{
    input += "4";
    updateInput();
}

void Calculator::on_pushButton_5_clicked()
{
    input += "5";
    updateInput();
}

void Calculator::on_pushButton_6_clicked()
{
    input += "6";
    updateInput();
}

void Calculator::on_pushButton_7_clicked()
{
    input += "7";
    updateInput();
}

void Calculator::on_pushButton_8_clicked()
{
    input += "8";
    updateInput();
}

void Calculator::on_pushButton_9_clicked()
{
    input += "9";
    updateInput();
}

void Calculator::on_pushButton_plus_clicked()
{
    //input += "+";
    //inputNumbers.push_back("+");
    inputOperations.push_back("+");
    inputOperationsCount++;
    updateInput();
}

void Calculator::updateInput()
{
     //ui->label_input->setText(input);
     QString inputS = "";
     //int max = (inputNumbersCount >= inputOperationsCount) ? inputNumbersCount : inputOperationsCount;
     for (int i = 0; i <= inputNumbersCount; i++) {
         inputS += inputNumbers[i];
         inputS += inputOperations[i];
     }
     ui->label_input->setText(inputS);
}


void Calculator::on_pushButton_equals_clicked()
{
    //int max = if (inputArr)


}
