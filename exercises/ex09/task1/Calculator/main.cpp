#include "calculator.hpp"
//#include <locale>
//#include <clocale>

#include <QApplication>

int main(int argc, char *argv[])
{
    //std::locale::global(std::locale("En_US"));
    //std::setlocale(LC_ALL, "en_US.UTF-8");
    QApplication a(argc, argv);
    Calculator w;
    w.show();
    return a.exec();
}
