#include "calculator.hpp"
//#include <locale>
//#include <clocale>

#include <QApplication>

int main(int argc, char *argv[])
{
    //std::locale::global(std::locale("En_US"));
    //std::setlocale(LC_ALL, "en_US.UTF-8");
    QApplication application(argc, argv);
    Calculator calculator;
    calculator.show();
    return application.exec();
}
