#include "human.h"

Human::Human()
{
    code = 100000;
    name = "noname";
    tel = "no_fone";
    description = "no_descr";
    summ = 0.0;
    debt = 0.0;
    discount = 0;
}

void Human::setCode(int code) {this->code = code;}

void Human::setName(std::string name) {this->name = inFilter(name);}

void Human::setTel(std::string tel) {this->tel = inFilter(tel);}

void Human::setDescription(std::string description) {this->description = inFilter(description);}

void Human::setSumm(float summ) {this->summ = summ;}

void Human::setDebt(float debt) {this->debt = debt;}

void Human::setDiscount(int discount) {this->discount = discount;}


int Human::getCode() {return code;}

std::string Human::getName() {return outFilter(name);}

std::string Human::getTel() {return outFilter(tel);}

std::string Human::getDescription() {return outFilter(description);}

float Human::getSumm() {return summ;}

float Human::getDebt() {return debt;}

int Human::getDiscount() {return discount;}


std::string Human::inFilter(std::string str)
{
    str = Textbutor::removeSpaces(str);
    str =Textbutor::endlRemove(str);
    return str;
}

std::string Human::outFilter(std::string str)
{
    str = Textbutor::endlAdd(str);
    str = Textbutor::spaceAdd(str);
    return str;
}




