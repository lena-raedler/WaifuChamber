#include "calculator.hpp"
#include "ui_calculator.h"

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
    , input("")
    , inputNumbersCount(0)
    , inputOperationsCount(1)   // The first operation is always a '+' to make processing easier (add first number)
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
    input += "0";
    //inputNumbers[inputNumbersCount].push_back('0');
    updateInput();
}

void Calculator::on_pushButton_1_clicked()
{
    input += "1";
    //inputNumbers[inputNumbersCount].push_back('1');
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
    input += "+";
    //inputNumbers.push_back("+");
    //inputOperations.push_back("+");
    //inputOperationsCount++;
    updateInput();
}

void Calculator::updateInput()
{
     //ui->label_input->setText(input);
     /*QString inputS = "";
     //int max = (inputNumbersCount >= inputOperationsCount) ? inputNumbersCount : inputOperationsCount;
     for (int i = 0; i <= inputNumbersCount; i++) {
         inputS += inputNumbers[i];
         inputS += inputOperations[i];
     }
     */
     //ui->label_input->setText(inputS);
     ui->label_input->setText(input);
}


void Calculator::on_pushButton_equals_clicked()
{
    preprocessInput();
    double result = 0;
    for (int i = 0; i < inputNumbers.size(); i++)
    {
        result = calculateResult(result, std::stoi(inputNumbers[0].toStdString()), inputOperations[0]);
    }
    ui->label_result->setText(std::to_string(result).c_str());
}

// Preprocess input
void Calculator::preprocessInput()
{
    for (QChar c : input)
    {
        if (c.isDigit())
            inputNumbers[inputNumbersCount] += c;
        else if (isOperation(c))
        {
            inputOperations[inputOperationsCount++] = c;
            inputNumbersCount++;
        }
    }
}

bool Calculator::isOperation(QChar c)
{
    if (c == '+' || c == '-' || c == '*' || c == '/')
        return true;
    return false;
}

double Calculator::calculateResult(double a, double b, QChar operation)
{
    if (operation == '-')
        return a-b;
    else if (operation == '+')
        return a+b;
    else
        return -1;
}

// Resolve negatives


// Resolve point operations

void Calculator::plusAndMinus()
{

}
