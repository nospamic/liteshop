#ifndef INI_H
#define INI_H

#include <QString>
#include <QDebug>
#include <fstream>
#include <vector>
#include <iostream>
#include "textbutor.h"

class Ini
{
public:
    Ini();
    void save();

    int getStickerVertCorrect();
    QString getCheckPrinterName();
    QString getStickerPrinterName();
    QString getReservPath();
    QString getNationalCurrency();
    QString getAlternativeCurrency();
    QString getStoreName();
    QString getStoreAddress();
    QString getCheckText();

    void setStickerVertCorrect(int value);
    void setCheckPrinterName(QString value);
    void setStickerPrinterName(QString value);
    void setReservPath(QString value);
    void setNationalCurrency(QString value);
    void setAlternativeCurrency(QString value);
    void setStoreName(QString value);
    void setStoreAddress(QString value);
    void setCheckText(QString value);
private:

    int stickerVertCorrect;
    std::string checkPrinterName;
    std::string stickerPrinterName;
    std::string reservPath;
    std::string nationalCurrency;
    std::string alternativeCurrency;
    std::string storeName;
    std::string storeAddress;
    std::string checkText;

    const char * path;

    void load();
    std::string inFilter(QString value);
    QString outFilter (std::string value);
};

#endif // INI_H
