#ifndef HUMANLOADER_H
#define HUMANLOADER_H

#include "human.h"
#include <QDir>
#include <QDebug>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <ctime>
#include <io.h>
#include "ini.h"


class HumanLoader
{
public:
    HumanLoader();
    ~HumanLoader();
    unsigned size;
    Human *base;
    void delHuman(int code);
    bool existsHuman(int code);
    void addHuman(std::string name, std::string tel, std::string description, int discount);
    void editHuman(int code, std::string name, std::string tel, std::string description, int discount, float debt,  float summ);
    void edit(Human man);
    Human getHuman(int code);
    void loadBase();
    int getLastCode();
    void debtAdd(Human man, float newDebt);
    void saveReserv();


private:

    const char * path;
    std::string reservPath;
    void saveBase();

    unsigned getSize();


};

#endif // HUMANLOADER_H
