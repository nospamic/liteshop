#include "unit_loader.h"

Unit_loader::Unit_loader()
{
    path="data.txt";

    struct tm *date;
    time_t t = time(nullptr);
    date = gmtime(&t);
    reservPath = Textbutor::qToStd(ini.getReservPath());
    reservPath +=Textbutor::intToString(date->tm_wday);
    reservPath += "res_data.txt";
    logPath = "LOG\\day_"+ getDate() + ".log";

    load();
}

unsigned Unit_loader::getFileSize()
{
    std::fstream fs;
    fs.open(path, std::fstream::in | std::fstream::out | std::fstream::app);
    //!fs.is_open()?exit(0):true;
    unsigned length=0;
    while(true)
    {
        Unit h;
        fs>>h;
        if(fs.eof()){break;}else{++length;}
        //std::cout << h <<"  length="<<length<<"\n";
    }
    fs.close();
    //std::cout <<"\n"<<length<<"\n";
    return length;
}


void Unit_loader::load()
{
    base.clear();

    std::fstream fs;
    fs.open(path, std::fstream::in | std::fstream::out | std::fstream::app);
     !fs.is_open()?qDebug()<<"\nError open "<<path<<"\n":qDebug()<<"\nLoad - "<<path<<"\n";

    while(true)
    {
        Unit h;
        fs>>h;
        if(fs.eof()){break;}else{base.push_back(h);}
    }
    //qDebug()<<base.size();
    fs.close();
}


void Unit_loader::save()
{
    std::fstream fs;
    fs.open(path, std::fstream::in | std::fstream::out | std::fstream::trunc);
    !fs.is_open()?qDebug()<<"\nError open "<<path<<"\n":qDebug()<<"\nSave - "<<path<<"\n";

    std::vector<Unit>::iterator it;
    for(it = base.begin(); it != base.end(); it++)
    {
        Unit unit;
        unit = *it;
        fs<<unit;
    }
    fs.close();
}


void Unit_loader::newFile()
{

    base.clear();
    Unit unit;

    unit.setCode(100000);
    QString str = "Курс валюты:";

    unit.setName(str.toLocal8Bit().constData());
    unit.setPrice(26.0);
    base.push_back(unit);
    save();
}


void Unit_loader::add(Unit unit)
{
    load();

    un id = base[base.size()-1].getId()+1;
    un code = base[base.size()-1].getCode()+1;

    unit.setId(id);
    unit.setCode(code);

    base.push_back(unit);
    save();
}

void Unit_loader::del(un code)
{
    load();
    if (unitExists(code))
    {

        for(un n=0; n<base.size(); n++)
        {
            if (base[n].getCode() == code)
            {
                base.erase(base.begin() + n);
            }
        }
        save();
    }
}


void Unit_loader::edit(Unit unit)
{
    un code = unit.getCode();
    un position = this->getPosition(code);

    base[position].setBarcode(unit.getBarcode());
    base[position].setQuantity(unit.getQuantity());
    base[position].setPrice(unit.getPrice());
    base[position].setEcharge(unit.getEcharge());
    base[position].setName(unit.getName());
    base[position].setSection(unit.getSection());
    base[position].setGroup(unit.getGroup());
    base[position].setDescription(unit.getDescription());
    base[position].setMinimum(unit.getMinimum());
    base[position].setHidden(unit.getHidden());

    save();
}

void Unit_loader::editSome(std::vector<Unit> invoice)
{
    for(un n=0; n<invoice.size(); n++)
    {
        un code = invoice[n].getCode();
        un position = this->getPosition(code);

        base[position].setBarcode(invoice[n].getBarcode());
        base[position].setQuantity(invoice[n].getQuantity());
        base[position].setPrice(invoice[n].getPrice());
        base[position].setEcharge(invoice[n].getEcharge());
        base[position].setName(invoice[n].getName());
        base[position].setSection(invoice[n].getSection());
        base[position].setGroup(invoice[n].getGroup());
        base[position].setDescription(invoice[n].getDescription());
        base[position].setMinimum(invoice[n].getMinimum());
        base[position].setHidden(invoice[n].getHidden());
    }
    save();
}


Unit Unit_loader::getUnit(un code)
{
    int position = -1;
    for (un n=0; n<base.size(); n++)
    {
        if(base[n].getCode() == code)
        {
            position = n;
            break;
        }
    }
    Unit result = base[position];
    return result;
}


Unit Unit_loader::getUnit(std::string barcode)
{
    Unit result;
    int position = -1;
    for (un n=0; n<base.size(); n++)
    {
        if(base[n].getBarcode() == barcode)
        {
            position = n;
            break;
        }
    }
    if(position != -1)
    {
        result = base[position];
    }
    else
    {
        result.setName("nullUnit");
    }
    return result;
}


un Unit_loader::getPosition(un code)
{
    for(un n=0; n<base.size(); n++)
    {
        if (base[n].getCode()==code) return n;
    }
    return 100000;
}


std::string Unit_loader::nameByBarcode(std::string barcode)
{
    std::string result = "";
    for(auto &unit : base)
    {
        if (unit.getBarcode()==barcode)
        {
            result =  unit.getName();
            return result;
        }
    }
    return result;
}


bool Unit_loader::unitExists(un code)
{
    for(auto &unit : base)
    {
        if (unit.getCode()==code) return true;
    }
    return false;
}


bool Unit_loader::unitExists(std::string barcode)
{
    for(auto &unit : base)
    {
        if (unit.getBarcode() == barcode) return true;
    }
    return false;
}


un Unit_loader::getLastCode()
{
    load();
    return base[base.size()-1].getCode();
}


void Unit_loader::addToLog(std::string msg)
{
    this->logPath = "LOG\\day_"+ getDate() + ".log";
    if(!QDir("LOG").exists())
        QDir().mkdir("LOG");
    std::fstream log;
    log.open(logPath, std::fstream::in | std::fstream::out | std::fstream::app);
    log<<msg;
    log.close();
}


float Unit_loader::getBalance()
{
    float balance = 0;

    for(un n=1; n < base.size(); n++)
    {
       if(base[n].getHidden().substr(0,1)=="#")
       {
           balance += round(base[n].getPrice() * base[n].getQuantity());
       }
       else
       {
           balance += round(base[n].getPrice() * base[n].getQuantity() * base[0].getPrice());
       }
    }
    return balance;
}


void Unit_loader::makeReservCopy()
{
    std::fstream fs;
    fs.open(reservPath, std::fstream::in | std::fstream::out | std::fstream::trunc);
    !fs.is_open()?std::cout<<"\nError save "<<reservPath<<"\n":std::cout<<"\nSave - "<<reservPath<<"\n";
    for(unsigned a=0; a<base.size(); a++) fs<<base[a];
    fs.close();
}


int Unit_loader::round(float a)
{
    (a>=0) ? (a-int(a)>=0.5) ? a=int(a+1) : a=int(a) : true;
    (a<0)  ? (a-int(a)<=-0.5) ?  a=int(a-1) : a=int(a) :  true;
    return int(a);
}


float Unit_loader::daySummFromLog(QString file)
{
    std::vector<std::string> day;
    float daySumm=0;

    //this->logPath = "LOG\\day_"+ getDate() + ".log";
    std::string stdFile = file.toLocal8Bit().constData();
    stdFile = "LOG\\" + stdFile;
    if(!QDir("LOG").exists())
        QDir().mkdir("LOG");

    std::fstream log;
    log.open(stdFile, std::fstream::in | std::fstream::out | std::fstream::app);
    while(true)
    {
        if(log.eof()){break;}
        std::string line = "";
        log>>line;
        day.push_back(line);
        //std::cout <<line<<"\n";
    }
    log.close();

    for(un n=0; n<day.size(); n++)
    {
        for(un i=0; i<day[n].size(); i++)
        {
            if(day[n].substr(i,1)=="=")
            {
                //std::cout << "= " << day[n+1]<<"\n";
                QString number = QString::fromLocal8Bit((day[n+1]).c_str());
                daySumm+=number.toFloat();
                //break;
            }
        }
    }

    return daySumm;
}


QStringList Unit_loader::getFiles(QString dir)
{
    QDir myDir(dir);
    myDir.setSorting(QDir::Time);

    QStringList files = myDir.entryList();

    return files;
}


bool Unit_loader::fileExists()
{
    return base.size() != 0;
}



std::string Unit_loader::getDate()
{
    struct tm *date;
    time_t t = time(nullptr);
    date = gmtime(&t);
    int day =date->tm_mday;
    int month = date->tm_mon+1;
    int year = date->tm_year+1900;

    //std::cout<<date->tm_hour<<':'<<date->tm_min<<':'<<date->tm_sec;
    std::string date1 = std::to_string(day) + "_" + std::to_string(month) + "_" + std::to_string(year);
    return date1;
}


