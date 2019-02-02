#include "unit.h"

Unit::Unit(void)
{


    name = "Noname";
    id = 0;
    code = 100000;
    price = 0.0;
    quantity = 0;
    echarge = 0.0;
    description="No_description";
    section="No_section";
    group="No_group";
    minimum = 1;
    barcode="0000000000000";
    hidden = "no_hidden";
}


Unit::~Unit(void)
{
}


void Unit::setId(un id){this->id=id;}
void Unit::setCode(long code){this->code=code;}
void Unit::setBarcode(std::string barcode){this->barcode=inFilter(barcode);}
void Unit::setQuantity(int quantity){this->quantity=quantity;}
void Unit::setPrice(float price){this->price=price;}
void Unit::setEcharge(float echarge){this->echarge=echarge;}
void Unit::setName(std::string name){this->name=inFilter(name);}
void Unit::setSection(std::string section){this->section=inFilter(section);}
void Unit::setGroup(std::string group){this->group=inFilter(group);}
void Unit::setDescription(std::string description){this->description=inFilter(description);}
void Unit::setMinimum(un minimum){this->minimum = minimum;}
void Unit::setHidden(std::string hidden){this->hidden=inFilter(hidden);}



bool Unit::isUah()
{
    if (getHidden().substr(0,1)=="+" || getHidden().substr(0,1)=="#")
    {
        return true;
    }
    else
    {
        return false;
    }
}


void Unit::setUah(bool isUah)
{
    if (isUah)
    {
        if(hidden.substr(0,1)!="#" && hidden.substr(0,1)!="+") hidden = "#" + hidden;
    }
    else
    {
        if(hidden.substr(0,1)=="#" || hidden.substr(0,1)=="+") hidden = "$" + hidden.substr(1 ,hidden.length()-1);
    }
}


void Unit::addSales(int sales)
{
    std::string salesStr = intToString(sales);


    if (hidden.find("?[") > hidden.size())
    {
        hidden = hidden + "_?[" + salesStr + "]";
    }
    else
    {
        sales += getSales();
        un startPos = hidden.find("?[");
        un endPos = hidden.find("]",startPos + 2);
        hidden.erase(startPos, endPos - startPos + 1);
        salesStr = intToString(sales);
        hidden = hidden + "?[" + salesStr + "]";

    }
}


un Unit::getId(){return id;}
un Unit::getCode(){return code;}
std::string Unit::getBarcode(){return outFilter(barcode);}
int Unit::getQuantity(){return quantity;}
float Unit::getPrice(){return price;}
float Unit::getEcharge(){return echarge;}
std::string  Unit::getName(){return outFilter(name);}
std::string Unit::getSection(){return outFilter(section);}
std::string Unit::getGroup(){return outFilter(group);}
std::string Unit::getDescription(){return outFilter(description);}
std::string Unit::getHidden(){return outFilter(hidden);}
un Unit::getMinimum(){return minimum;}

un Unit::getSales()
{
    un result = 0;
    if (hidden.find("?[") < hidden.size())
    {
        un startPos = hidden.find("?[");
        un endPos = hidden.find("]",startPos + 2);
        std::string value = hidden.substr(startPos + 2, endPos - startPos - 2);
        result = stringToInt(value);
    }
    return result;
}


std::string Unit::inFilter(std::string str)
{
    str = Textbutor::removeSpaces(str);
    str = Textbutor::endlRemove(str);
    return str;
}

std::string Unit::outFilter(std::string str)
{
    str = Textbutor::endlAdd(str);
    str = Textbutor::spaceAdd(str);
    return str;
}


std::string Unit::intToString(int value)
{
    std::string str;
    std::ostringstream ss;
    ss<<value;
    str=ss.str();
    return str;
}


int Unit::stringToInt(std::string str)
{
    int d=0;
    std::stringstream ss(str);
    ss>>d;
    return d;
}
