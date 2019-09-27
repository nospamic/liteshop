#ifndef ADD2_H
#define ADD2_H

#include <iostream>
#include <QRadioButton>
#include <QValidator>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QSpinBox>
#include <QLabel>
#include <QMessageBox>
#include <QCheckBox>
#include <QPrinter>
#include <QPrinterInfo>
#include <QPainter>
#include <QFontDatabase>
#include <QTimer>
#include "textbutor.h"
#include "unit_loader.h"
#include "ini.h"


class Add2 : public QDialog
{
    Q_OBJECT

public:
    Add2(QWidget *parent = nullptr);
    ~Add2();
private:

    QVBoxLayout * vert;
    QLineEdit * lineName;
    QLineEdit * linePrice;
    QCheckBox *checkUah;
    QSpinBox * spinQuant;
    QLineEdit *lineBarcode;
    QPushButton *buttonGen;
    QCheckBox *checkQueue;
    QSpinBox *spinPrint;
    QPushButton * ok;
    std::vector<QRadioButton*>groupList;
    void showGroups();
    Textbutor textbutor;
    //Unit_loader uLoad;



public slots:
    void itsOk();
    void currencySwich();
    void setBarcode();
    void printSticker();
    void okEnable();
    void groupChecked();
};

#endif // ADD2_H
