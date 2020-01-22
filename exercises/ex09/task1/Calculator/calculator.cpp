#include "calculator.hpp"
#include "ui_calculator.h"
#include <iostream>

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
    , input("")
    , inputNumbersCount(0)
    , inputOperationsCount(1)   // The first operation is always a '+' to make processing easier (add first number)
    , inputNumbers(256)
    , inputNumbersDouble(256)
    , inputOperations(256)
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
    updateInput();
}

void Calculator::on_pushButton_1_clicked()
{
    input += "1";
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

void Calculator::on_pushButton_times_clicked()
{
    input += "*";
    updateInput();
}

void Calculator::on_pushButton_divide_clicked()
{
    input += "/";
    updateInput();
}

void Calculator::on_pushButton_minus_clicked()
{
    input += "-";
    updateInput();
}

void Calculator::on_pushButton_plus_clicked()
{
    input += "+";
    updateInput();
}

void Calculator::on_pushButton_dot_clicked()
{
    input += ",";
    updateInput();
}

void Calculator::on_pushButton_clear_clicked()
{
    input = "";
    clearCalculator();
    updateInput();
    ui->label_result->setText("");
}


void Calculator::updateInput()
{
     ui->label_input->setText(input);
}


void Calculator::on_pushButton_equals_clicked()
{
    clearCalculator();
    preprocessInput();
    if (inputNumbersCount <= 0)
        return;

    printCalculator();
    timesAndDivide();
    double result = plusAndMinus();

    ui->label_result->setText(std::to_string(result).c_str());
}

void Calculator::preprocessInput()
{
    inputOperations[0] = "+";
    for (QChar c : input)
    {
        if (c.isDigit() || c == ',')    // Former: if (c.isDigit() || c == '.')
            inputNumbers[inputNumbersCount] += c;
        else if (isOperation(c))
        {
            inputOperations[inputOperationsCount++] += c;
            inputNumbersCount++;
        }
    }

    for (int i = 0; i <= inputNumbersCount; i++)
        inputNumbersDouble[i] = stof(inputNumbers[i].toStdString());
}

bool Calculator::isOperation(const QChar c)
{
    if (c == '+' || c == '-' || c == '*' || c == '/')
        return true;
    return false;
}

double Calculator::calculateResult(const double a, const double b, const QString& operation)
{
    if (operation.compare("-") == 0){
        std::cout << "- operation called" << std::endl;
        return a-b;
    }
    else if (operation.compare("+") == 0)
    {
        std::cout << "+ operation called" << std::endl;
        return a+b;
    }
    else if (operation.compare("*") == 0)
    {
        std::cout << "* operation called" << std::endl;
        return a*b;
    }
    else if (operation.compare("/") == 0)
    {
        std::cout << "/ operation called" << std::endl;
        return a/b;
    }
    else
    {
        std::cout << "Unable to resolve operation" << std::endl;
        return -1;
    }
}

// Resolve negatives
void Calculator::resolveNegatives()
{
    // TODO
}

// Resolve point operations
void Calculator::timesAndDivide()
{
    QString op;

    for (int i = 1; i <= inputOperationsCount; i++)    // Start at 1 directly because 0 is a +
    {
        op = inputOperations[i];
        if (op.compare("*") == 0 || op.compare("/") == 0)
        {
            inputNumbersDouble[i-1] = calculateResult(inputNumbersDouble[i-1], inputNumbersDouble[i], op);
            shiftNumbers(i);
        }
    }
}

void Calculator::shiftNumbers(const int offset)
{
    for (int i = offset; i < inputNumbersCount; i++)
        inputNumbersDouble[i] = inputNumbersDouble[i+1];
    inputNumbersCount--;    // There is no need to delete inputNumbersDouble[i] because we iterate with inputNumbersCount

    for (int i = offset; i < inputOperationsCount; i++)
        inputOperations[i] = inputOperations[i+1];
    inputOperationsCount--;
}

double Calculator::plusAndMinus()
{
    double result = 0;
    for (int i = 0; i <= inputNumbersCount; i++)
        result = calculateResult(result, inputNumbersDouble[i], inputOperations[i]);

    std::cout << std::endl;
    return result;
}


void Calculator::clearCalculator()
{
    inputNumbersCount = 0;
    for (int i = 0; i < inputNumbers.size(); i++)
        inputNumbers[i] = "";

    inputOperationsCount = 1;
    for (int i = 0; i < inputOperations.size(); i++)
        inputOperations[i] = "";
}

void Calculator::printCalculator()
{
    std::cout << "Input Numbers: ";
    for (int i = 0; i <= inputNumbersCount; i++) {
        std::cout << inputNumbers[i].toStdString() << ", ";
    }
    std::cout << std::endl;

    std::cout << "Input doubles: ";
    for (int i = 0; i <= inputNumbersCount; i++) {
        std::cout << inputNumbersDouble[i] << ", ";
    }
    std::cout << std::endl;

    std::cout << "Input Operations: ";
    for (int i = 0; i < inputOperationsCount; i++) {
        std::cout << inputOperations[i].toStdString() << ", ";
    }
    std::cout << std::endl;
}
