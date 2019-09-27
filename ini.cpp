#include "ini.h"

Ini * Ini::instance = nullptr;

Ini::Ini()
{

    path = "parametrs.ini";
    setStickerVertCorrect (0);
    setCheckPrinterName ("check");
    setStickerPrinterName ("sticker");
    setReservPath ("\\");
    setNationalCurrency ("грн.");
    setAlternativeCurrency ("usd.");
    setStoreName ("Магазин");
    setStoreAddress ("Адрес");
    setCheckText ("Спасибо_за_покупку!");

    load();
}


void Ini::save()
{
    std::fstream fs;
    fs.open(path, std::fstream::in | std::fstream::out | std::fstream::trunc);
    if(fs.is_open())
    {
        fs << "stickerVertCorrect = " << stickerVertCorrect << "\n";
        fs << "checkPrinterName = " << checkPrinterName << "\n";
        fs << "stickerPrinterName = " << stickerPrinterName << "\n";
        fs << "reservPath = " << reservPath << "\n";
        fs << "nationalCurrency = " << nationalCurrency << "\n";
        fs << "alternativeCurrency = " << alternativeCurrency << "\n";
        fs << "storeName = " << storeName << "\n";
        fs << "storeAddress = " << storeAddress << "\n";
        fs << "checkText = " << checkText;
        fs.close();
    }

}


Ini *Ini::getInstance()
{
    if(instance==nullptr){
        instance = new Ini;
    }
    return instance;
}


int Ini::getStickerVertCorrect(){return stickerVertCorrect;}

QString Ini::getCheckPrinterName(){return outFilter(checkPrinterName);}

QString Ini::getStickerPrinterName(){return outFilter(stickerPrinterName);}

QString Ini::getReservPath(){return outFilter(reservPath);}

QString Ini::getNationalCurrency(){return outFilter(nationalCurrency);}

QString Ini::getAlternativeCurrency(){return outFilter(alternativeCurrency);}

QString Ini::getStoreName(){return outFilter(storeName);}

QString Ini::getStoreAddress(){return outFilter(storeAddress);}

QString Ini::getCheckText(){return outFilter(checkText);}



void Ini::setStickerVertCorrect(int value) {this->stickerVertCorrect = value;}

void Ini::setCheckPrinterName(QString value) {this->checkPrinterName = inFilter(value);}

void Ini::setStickerPrinterName(QString value) {this->stickerPrinterName = inFilter(value);}

void Ini::setReservPath(QString value) {this->reservPath = inFilter(value);}

void Ini::setNationalCurrency(QString value) {this->nationalCurrency = inFilter(value);}

void Ini::setAlternativeCurrency(QString value) {this->alternativeCurrency = inFilter(value);}

void Ini::setStoreName(QString value) {this->storeName = inFilter(value);}

void Ini::setStoreAddress(QString value) {this->storeAddress = inFilter(value);}

void Ini::setCheckText(QString value) {this->checkText = inFilter(value);}



void Ini::load()
{
    std::string paths = "parametrs.ini";
    std::fstream fs;
    fs.open(paths, std::fstream::in);
    if(fs.is_open())
    {
        while(!fs.eof())
        {
            std::string str = "";
            fs>>str;
            if (str == "stickerVertCorrect"){fs>>str; fs>>stickerVertCorrect;}
            if (str == "checkPrinterName"){fs>>str; fs>>checkPrinterName;}
            if (str == "stickerPrinterName"){fs>>str; fs>>stickerPrinterName;}
            if (str == "reservPath"){fs>>str; fs>>reservPath;}
            if (str == "nationalCurrency"){fs>>str; fs>>nationalCurrency;}
            if (str == "alternativeCurrency"){fs>>str; fs>>alternativeCurrency;}
            if (str == "storeName"){fs>>str; fs>>storeName;}
            if (str == "storeAddress"){fs>>str; fs>>storeAddress;}
            if (str == "checkText"){fs>>str; fs>>checkText;}
        }
        fs.close();
    }
    else save();

}


std::string Ini::inFilter(QString value)
{
    std::string result = Textbutor::qToStd(value);
    result = Textbutor::removeSpaces(result);
    result = Textbutor::endlRemove(result);
    return result;
}

QString Ini::outFilter(std::string value)
{
    value = Textbutor::spaceAdd(value);
    value = Textbutor::endlAdd(value);
    QString result = Textbutor::stdToQ(value);
    return result;
}
