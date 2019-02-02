#ifndef UNIT_LOADER_H
#define UNIT_LOADER_H

#include <QObject>
#include <QDir>
#include <QString>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <ctime>
#include <io.h>
#include <QDebug>
#include "ini.h"
#include "textbutor.h"

#include "Unit.h"

typedef unsigned int un;

class Unit_loader
{
public:
    Unit_loader();
    std::vector<Unit>base;

    unsigned getFileSize();
    void load();
    void save();
    void newFile();
    void add(Unit unit);
    void del(un code);
    void edit(Unit unit);
    void editSome(std::vector<Unit>invoice);
    Unit getUnit(un code);
    Unit getUnit(std::string barcode);
    un getPosition(un code);
    std::string nameByBarcode(std::string barcode);
    bool unitExists(un code);
    bool unitExists(std::string barcode);
    un getLastCode();
    void addToLog(std::string msg);
    float getBalance();
    void makeReservCopy();
    int round(float a);
    float daySummFromLog(QString file);
    QStringList getFiles(QString dir);
    bool fileExists();
    std::string getDate();

private:
    Ini ini;
    const char * path;
    std::string reservPath;
    std::string logPath;
    std::string date;




};

#endif // UNIT_LOADER_H
