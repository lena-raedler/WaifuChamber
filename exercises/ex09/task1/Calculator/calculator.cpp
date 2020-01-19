#include "calculator.h"
#include "ui_calculator.h"

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
    , input("")
{
    ui->setupUi(this);
}

Calculator::~Calculator()
{
    delete ui;
}


void Calculator::on_pushButton_clicked()
{
    input += "0";
    updateInput();
}

void Calculator::on_pushButton_2_clicked()
{
    input += "1";
    updateInput();
}

void Calculator::on_pushButton_3_clicked()
{
    input += "2";
    updateInput();
}

void Calculator::updateInput()
{
     ui->label->setText(input);
}
