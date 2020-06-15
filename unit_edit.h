#ifndef UNIT_EDIT_H
#define UNIT_EDIT_H

#include <QGroupBox>
#include <QDebug>
#include <QRadioButton>
#include <QDesktopWidget>
#include <QValidator>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QSpinBox>
#include <QLabel>
#include <QTextEdit>
#include <QCheckBox>
#include <QMessageBox>
#include <QPrinter>
#include <QPrintDialog>
#include <QPrinterInfo>
#include <QPainter>
#include <QFontDatabase>
#include "textbutor.h"
#include "unit.h"
#include "unit_loader.h"
#include "ini.h"

class Unit_edit : public QDialog
{
    Q_OBJECT

public:
    Unit_edit(unsigned code, QWidget *parent = nullptr);
    ~Unit_edit();

private:
    unsigned code;
    QString groupStyleSheet;

    QGroupBox *groupBox;
    QLineEdit * lineName;
    QLineEdit * linePrice;
    QCheckBox *checkUah;
    QCheckBox *checkUsd;
    QSpinBox * spinQuant;
    QLineEdit * lineBarcode;
    QLineEdit * lineEcharge;
    QLineEdit * lineSection;
    QLineEdit * lineGroup;
    QTextEdit * textDescription;
    QTextEdit * textHidden;
    QTextEdit * textSticker;
    QSpinBox * spinSales;
    QSpinBox * spinPrint;
    QVBoxLayout * vert;
    QHBoxLayout * horGroups;
    QVBoxLayout * vertGroup0;
    QVBoxLayout * vertGroup1;
    QVBoxLayout * vertGroup2;
    QVBoxLayout * vertGroup3;


    QPushButton * ok;

    bool isUah;
    Textbutor textbutor;
    //Unit_loader uLoad;
    Unit unit;
    void getFields();
    void barcodeRepair();

    std::vector<QRadioButton*>groupList;
    void showGroups();



public slots:
    void itsOk();
    void printing();
    void on_checkUah();
    void on_checkUsd();
    void setGroup();
    void on_changePrint();
};

#endif // UNIT_EDIT_H
