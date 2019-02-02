#include "ini.h"

Ini::Ini()
{
    path = "options.ini";


    load();
//    for(auto i : parametr)
//    {
//        qDebug() << stdToQ(i.type) << " " << stdToQ(i.key) << " = " << stdToQ(i.value) << "\n";
//    }
}

Ini::~Ini()
{

}


void Ini::load()
{
    bool isOpen = false;
    std::fstream ifs;
    ifs.open(path, std::fstream::in);


    if(ifs.is_open())
    {
        isOpen = true;
        qDebug()<<"\nOpen - "<<path<<"\n";
        int column = Type;
        Node tempParametr;
        while(!ifs.eof())
        {

            std::string tempStr;
            ifs>>tempStr;
            //qDebug()<< column <<" "<< stdToQ(tempStr);

            if(column == Type){tempParametr.type = tempStr;}
            if(column == Key){tempParametr.key = tempStr;}
            if(column == Value)
            {
                tempParametr.value = tempStr;
                parametr.push_back(tempParametr);
            }
            column++;
            if (column > Value)column = Type;
        }

    }
    ifs.close();
    if(!isOpen)
    {
        create();
        load();
    }
}


void Ini::save()
{
    std::fstream ifs;
    ifs.open(path, std::fstream::in | std::fstream::out | std::fstream::trunc);
    if(ifs.is_open())
    {
        std::string tempStr;
        for(auto& i : parametr)
        {
            tempStr = i.type; ifs << tempStr << " ";
            tempStr = i.key; ifs << tempStr << " = ";
            tempStr = i.value; ifs << tempStr;
            if(&i != &parametr.back()) ifs << "\n";
        }
    }
    ifs.close();
}



std::string Ini::value(std::string key)
{
    std::string result = "error";

    for(auto i : parametr)
        {
            if (i.key == key) result = i.value;
        }
    return result;
}


int Ini::intValue(std::string key)
{
    int result = 0;

    for(auto i : parametr)
        {
            if (i.key == key) result = Textbutor::stdToInt(i.value);
        }
    return result;
}


void Ini::setValue(std::string key, std::string value)
{
    for(unsigned n = 0; n < parametr.size(); n++)
        {
            if (parametr[n].key == key) {parametr[n].value = removeSpaces(value);}
        }
    //print();
}


