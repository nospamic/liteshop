#ifndef HUMAN_H
#define HUMAN_H

#include <string>
#include "textbutor.h"

class Human
{
public:
    Human();
    void setCode(int code);
    void setName(std::string name);
    void setTel(std::string tel);
    void setDescription(std::string description);
    void setSumm(float summ);
    void setDebt(float debt);
    void setDiscount(int discount);
    int getCode();
    std::string getName();
    std::string getTel();
    std::string getDescription();
    float getSumm();
    float getDebt();
    int getDiscount();


private:
    int code;
    std::string name;
    std::string tel;
    std::string description;
    float summ;
    float debt;
    int discount;

    std::string inFilter(std::string str);
    std::string outFilter(std::string str);


    friend std::ostream& operator<<(std::ostream& os, const Human& );
    friend std::istream& operator>>(std::istream& is,  Human& );
};



#endif // HUMAN_H
