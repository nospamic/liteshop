#include "textbutor.h"

Textbutor::Textbutor()
{

}

QString Textbutor::cutter(QString str, int size)
{
    if(str.size()>size)
    {
        return str.left(size);
    }
    else
    {
        int add = size - str.size();
        for (int n=0; n<add; n++)
        {
            str = str + " ";
        }
    }
    return str;
}

QString Textbutor::makeBarcode(unsigned code)
{
    QString barcode = "482000" + QString::number(code);
    return checkSummGen(barcode);
}

QString Textbutor::barcodeToEvan(QString barcode)
{

    QString result = "";
    if (barcode.size()<13) return "Small bar size!";
    QString codingWays = "#$%&'()*+,";

    QString L = "0123456789";
    QString G = "ABCDEFGHIJ";
    QString R = "abcdefghij";

    std::vector<QString>wayCodLeft;
    wayCodLeft.push_back("LLLLLL");
    wayCodLeft.push_back("LLGLGG");
    wayCodLeft.push_back("LLGGLG");
    wayCodLeft.push_back("LLGGGL");
    wayCodLeft.push_back("LGLLGG");
    wayCodLeft.push_back("LGGLLG");
    wayCodLeft.push_back("LGGGLL");
    wayCodLeft.push_back("LGLGLG");
    wayCodLeft.push_back("LGLGGL");
    wayCodLeft.push_back("LGGLGL");

    unsigned codingWayNum = barcode.left(1).toInt();
    result += codingWays.mid(codingWayNum, 1);
    result +="!";
    for (unsigned n=1; n<8; n++)
    {
        int originalNum = barcode.mid(n, 1).toInt();
        int codLeftPos = n-1;
        if (wayCodLeft[codingWayNum][codLeftPos]=='L') result += L.mid(originalNum, 1);
        if (wayCodLeft[codingWayNum][codLeftPos]=='G') result += G.mid(originalNum, 1);

    }
    result +="-";
    for (unsigned n=7; n<13; n++)
    {
        int originalNum = barcode.mid(n, 1).toInt();
        result += R.mid(originalNum, 1);
    }
    result +="!";
    //std::cout <<result.toLocal8Bit().constData()<<"\n";
    return result;
}

QString Textbutor::makeLable(QString name, float price, bool isUah)
{
    QString result = "";
    QString qPrice;
    if(isUah) {qPrice = " " + QString::number(price) + " грн.";}
    else {qPrice = " 000" + QString::number(price);}
    result = "" + cutter(name,17) + qPrice + "\n";
    return result;
}

QString Textbutor::makePrice(float price, bool isUah)
{
    QString qPrice;
    if(isUah) {qPrice = " " + QString::number(price) + " грн.";}
    else {qPrice = " 00" + QString::number(price);}
    return qPrice;
}

QString Textbutor::getDate()
{
        struct tm *date;
        time_t t = time(NULL);
        date = gmtime(&t);
        int day =date->tm_mday;
        int month = date->tm_mon + 1;
        int year = date->tm_year + 1900;
        std::stringstream ss;
        ss<<day<<"."<<month<<"."<<year;
        //std::cout<<date->tm_hour<<':'<<date->tm_min<<':'<<date->tm_sec;
        std::string date1 = ss.str();//std::string(itoa(day)) + "." + std::to_string(month) + "." + std::to_string(year);

        return QString::fromLocal8Bit(date1.c_str());
}


QString Textbutor::checkSummGen(QString barcode)
{
    float checkSumm=0;
    int number=0;
    for (int n=0; n<12; n+=2)
    {
        number=0;
        number = barcode.mid(n, 1).toInt();
        checkSumm += number;
        //qDebug() <<number<<"+";
        number = 0;
        number = barcode.mid(n+1, 1).toInt();
        number = number*3;
        checkSumm += number;
        //qDebug() << number << "+";
    }
    float res = (checkSumm/10.0f) - (int(checkSumm/10.0f));
    //qDebug()<<"res="<<res;
    if(res != 0.0f) {
        res = (res *10.0f);
        //qDebug()<<"res="<<res;
        //res = res*100;
        res = round (res);
        //res=res/100;
        //qDebug()<<"res="<<res;
        res = round(10.0f-res);
    }

    QString result = QString::number(int(res)).left(1);
    //qDebug() << "=" << checkSumm<<" -> "<<res<<"\n";

    return barcode + result;
}


QString Textbutor::testBarcode13(QString barcode)
{
    QString barcodeBase = barcode.left(12);
    QString barcodeCorrect = checkSummGen(barcodeBase);
    if (barcode != barcodeCorrect)
    {

//        barcode = barcodeCorrect;
//        QMessageBox msg;
//        msg.setText("Неправильный штрих-код. Исправлен.");
//        msg.exec();
    }
    return barcodeCorrect;
}

std::string Textbutor::removeSpaces(std::string str)
{
    std::string result="";
    for(unsigned a=0; a<str.size();a++)
    {
        if (str[a]==' ' || str[a]=='\t') {result.push_back('_');}else {result.push_back(str[a]);}
    }
    return result;
}

std::string Textbutor::spaceAdd(std::string str)
{
    std::string result="";
    for(unsigned a=0; a<str.size();a++)
    {
        if (str[a]=='_') {result.push_back(' ');} else {result.push_back(str[a]);}
    }
    return result;
}


std::string Textbutor::endlRemove(std::string str)
{
    std::string result="";
    for(unsigned a=0; a<str.size();a++)
    {
        if (str[a]=='\n')
        {
            result.push_back('~');
            result.push_back('n');
        }
        else result.push_back(str[a]);
    }
    return result;
}


std::string Textbutor::endlAdd(std::string str)
{
    std::string result="";
    for(unsigned a=0; a<str.size();a++)
    {
        if (a != (str.size()-1) && str[a] == '~' && str[a+1] == 'n')
        {
            result.push_back('\n');
            a++;
        }
        else result.push_back(str[a]);
    }
    return result;
}


QString Textbutor::toDot(QString str)
{
    QString result="";
    for(int a=0; a<str.size();a++)
    {
        if (str[a]==',') {result.push_back('.');}else {result.push_back(str[a]);}
    }
    return result;
}

int Textbutor::spaceFirstPos(QString str)
{
    for(int a=0; a<str.size();a++)
    {
        if (str[a]==' ' || str[a]=='_') {return a;}
    }
    return str.size();
}

bool Textbutor::isBarcode(QString str)
{
//    QString digits = "0123456789";
//    if(str.size() < 8)return false;
//    for(int a=0; a<str.size();a++)
//    {
//        if (!digits.contains(str.mid(a,1), Qt::CaseInsensitive)) {return false;}
//    }
//    return true;
    return str.contains(QRegExp("[0-9]{7,14}"));
}

std::vector<QString> Textbutor::stringToVector(QString word)
{
    std::vector<QString>result;
    QString add = "";
    for(int n=0; n<word.size(); n++)
    {
        if(word.mid(n,1)!=" " && word.mid(n,1)!="_"){add+=word.mid(n,1);}
        else
            if(add.size()>0)
            {
               result.push_back(add);
                add = "";
            }
    }
    if(add.size()>0) result.push_back(add);
    return result;
}

QString Textbutor::latinToKiril(QString str)
{

    QString latinChar = "qwertyuiop[]asdfghjkl;'zxcvbnm,.QWERTYUIOP{}ASDFGHJKL:\"ZXCVBNM<>";
    QString kirilChar = "йцукенгшщзхъфывапролджэячсмитьбюЙЦУКЕНГШЩЗХЪФЫВАПРОЛДЖЭЯЧСМИТЬБЮ";

    for(int n=0; n<str.size();n++)
    {
        if(latinChar.contains(str[n]))
        {
            int posit = latinChar.indexOf(str[n]);
            str[n] = kirilChar[posit];
        }
    }
    return str;

}



QString Textbutor::stdToQ(std::string str)
{
    return QString::fromLocal8Bit((str).c_str());
}



int Textbutor::stdToInt(std::string str)
{
    return stdToQ(str).toInt();
}

std::string Textbutor::intToString(int a)
{
    std::stringstream ss;
    ss<<a;
    return ss.str();
}


std::string Textbutor::qToStd(QString str)
{
    return str.toLocal8Bit().constData();
}

int Textbutor::dayInDate(std::string date)
{
    int result=0;
    std::string day = "";
    std::string month = "";
    std::string year = "";
    unsigned parsPos = 0;

    for (unsigned n = parsPos;n < date.length();n++)
    {
        if(date[n]=='.') {parsPos = n+1; break;}
        day = day + date[n];
    }
    for (unsigned n = parsPos;n < date.length();n++)
    {
        if(date[n]=='.') {parsPos = n+1; break;}
        month = month + date[n];
    }
    for (unsigned n = parsPos;n < date.length();n++)
    {
        if(date[n]=='.') {break;}
        year = year + date[n];
    }

    result = Textbutor::stdToInt(day) + Textbutor::stdToInt(month)*30 + Textbutor::stdToInt(year) * 365;
    return result;
}

int Textbutor::round(float a)
{
        //qDebug()<<"Round - "<<a;
        a=a*100;
        if(a>=0) a-int(a)>=0.5F ? a=int(a+1) : a=int(a);
        if(a<0) a-int(a)<=-0.5F ? a=int(a-1) : a=int(a);
        //qDebug()<<"Round result - "<<int(a);
        return int(a/100);
}
