#ifndef HUMANEDIT_H
#define HUMANEDIT_H

#include <QValidator>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QSpinBox>
#include <QLabel>
#include <QTextEdit>
#include <QMessageBox>
#include <QPrinter>
#include <QPrintDialog>
#include <QPrinterInfo>
#include <QPainter>
#include <QFontDatabase>
#include "textbutor.h"
#include "humanloader.h"
#include "human.h"
#include "ini.h"

class HumanEdit : public QDialog
{
    Q_OBJECT

public:
    HumanEdit(unsigned code, bool activateCard = 0, QWidget *parent = 0);
    ~HumanEdit();

private:
    Human man;
    int code;
    Ini ini;
    std::string name;
    std::string tel;
    std::string description;
    float debt;
    float summ;
    int discount;

    bool activateCard;



    QLineEdit * lineName;
    QLineEdit * lineTel;
    QSpinBox * spinDiscount;
    QLineEdit * lineDebt;
    QLineEdit * lineSumm;
    QTextEdit * textDescription;
    QPushButton * ok;
    QPushButton *buttonPrint;

    Textbutor textbutor;
    HumanLoader humanloader;



    void getFields();



public slots:
    void itsOk();
    void okEnabled();
    void printSticker();

};

#endif // HUMANEDIT_H
