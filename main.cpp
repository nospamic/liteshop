#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Unit.h"
#include "human.h"

typedef unsigned int un;



std::ostream& operator<<(std::ostream& os, const Unit& un)
{
    os<<

    un.id<<" "<<
    un.code<<" "<<
    un.name<<" "<<
    un.price<<" "<<
    un.quantity<<" "<<
    un.echarge<<" "<<
    un.description<<" "<<
    un.section<<" "<<
    un.group<<" "<<
    un.barcode<<" "<<
    un.minimum<<" "<<
    un.hidden<<"\n";
    return os;
}

std::istream& operator>>(std::istream& is,  Unit& un)
{
    is>>

    un.id>>
    un.code>>
    un.name>>
    un.price>>
    un.quantity>>
    un.echarge>>
    un.description>>
    un.section>>
    un.group>>
    un.barcode>>
    un.minimum>>
    un.hidden;
    return is;
}

std::ostream& operator<<(std::ostream& os, const Human& hu)
{
    os<<
    hu.code<<" "<<
    hu.name<<" "<<
    hu.tel<<" "<<
    hu.description<<" "<<
    hu.summ<<" "<<
    hu.debt<<" "<<
    hu.discount<<"\n";
    return os;
}

std::istream& operator>>(std::istream& is,  Human& hu)
{
    is>>
    hu.code>>
    hu.name>>
    hu.tel>>
    hu.description>>
    hu.summ>>
    hu.debt>>
    hu.discount;
    return is;
}

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
