#ifndef TEXTBUTOR_H
#define TEXTBUTOR_H

#include <QString>
#include <QDebug>
#include <vector>
#include <iostream>
#include <ctime>
#include <string>
#include <QMessageBox>
#include <sstream>
#include <cstdlib>


class Textbutor
{
private:

public:
    Textbutor();

    static QString cutter(QString str, int size);
    static QString makeBarcode(unsigned code);
    static QString barcodeToEvan(QString barcode);
    QString makeLable(QString name, float price, bool isUah);
    QString makePrice(float price, bool isUah);
    static QString getDate();
    static QString checkSummGen(QString barcode);
    static QString testBarcode13(QString barcode);

    static std::string removeSpaces(std::string str);
    static std::string spaceAdd(std::string str);
    static std::string endlRemove(std::string str);
    static std::string endlAdd(std::string str);


    static QString toDot (QString str);
    static int spaceFirstPos(QString str);
    static bool isBarcode(QString str);
    static std::vector<QString> stringToVector(QString word);
    static QString latinToKiril(QString str);
    static QString stdToQ(std::string str);
    static int stdToInt(std::string str);
    static std::string intToString(int a);
    static std::string qToStd(QString str);
    static int dayInDate(std::string date);
    static int round(float a);
    static std::string encrypt(std::string);
    static std::string decrypt(std::string);


};

#endif // TEXTBUTOR_H
