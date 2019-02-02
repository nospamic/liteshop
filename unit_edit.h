#ifndef UNIT_EDIT_H
#define UNIT_EDIT_H


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
    Unit_edit(unsigned code, QWidget *parent = 0);
    ~Unit_edit();

private:
    unsigned code;


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



    QPushButton * ok;

    bool isUah;
    Textbutor textbutor;
    Unit_loader uLoad;
    Unit unit;
    Ini ini;
    void getFields();
    void barcodeRepair();


public slots:
    void itsOk();
    void printing();
    void on_checkUah();
    void on_checkUsd();
};

#endif // UNIT_EDIT_H
