#include "calculator.hpp"
#include "ui_calculator.h"
#include <iostream>

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

void Calculator::on_pushButton_clear_clicked()
{
    input = "";
    clearCalculator();
    updateInput();
    ui->label_result->setText("");
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
    clearCalculator();
    preprocessInput();
    std::cout << "Input Numbers: ";
    for (QString s : inputNumbers) {
        std::cout << s.toStdString() << ", ";
    }
    std::cout << std::endl;

    std::cout << "Input Operations: ";
    for (QString s : inputOperations) {
        std::cout << s.toStdString() << ", ";
    }
    std::cout << std::endl;

    double result = 0;
    for (int i = 0; i <= inputNumbersCount; i++)
    {
        double converted = std::stoi(inputNumbers[i].toStdString());
        std::cout << "converted: " << converted << ", ";
        result = calculateResult(result, converted, inputOperations[i]);
    }
    std::cout << std::endl;
    ui->label_result->setText(std::to_string(result).c_str());
}

// Preprocess input
void Calculator::preprocessInput()
{
    inputOperations[0] = "+";
    for (QChar c : input)
    {
        if (c.isDigit())
            inputNumbers[inputNumbersCount] += c;
        else if (isOperation(c))
        {
            inputOperations[inputOperationsCount++] += c;
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

double Calculator::calculateResult(double a, double b, QString operation)
{
    if (operation.compare("-") == 0){
        return a-b;
    }
    else if (operation.compare("+") == 0) {
        std::cout << "+ operation called" << std::endl;
        return a+b;
    }
    else
        return -1;
}

// Resolve negatives


// Resolve point operations

void Calculator::plusAndMinus()
{

}


void Calculator::clearCalculator()
{
    //input.clear();
    inputNumbersCount = 0;
    //inputNumbers.clear();
    for (int i = 0; i < inputNumbers.size(); i++)
        inputNumbers[i] = "";

    inputOperationsCount = 1;
    //inputOperations.clear();
    for (int i = 0; i < inputOperations.size(); i++)
        inputOperations[i] = "";
}
