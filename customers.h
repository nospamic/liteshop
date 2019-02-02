#ifndef CUSTOMERS_H
#define CUSTOMERS_H

#include <iostream>
#include <QListWidget>
#include <QValidator>
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
#include <QFontDatabase>
#include <QPrinterInfo>
#include "textbutor.h"
#include "human.h"
#include "humanloader.h"
#include "humanadd.h"
#include "humanedit.h"
#include "ini.h"


class Customers : public QDialog
{
    Q_OBJECT

public:
    Customers(QWidget *parent = 0);
    ~Customers();
private:

    Textbutor textbutor;
    HumanLoader humanloader;
    Ini ini;

    QPushButton * buttonCards;
    QSpinBox * spinCards;
    QListWidget *list;
    QLineEdit *lineSearsh;
    QPushButton *buttonAdd;
    QPushButton *buttonEdit;
    QPushButton *buttonDelete;

    void getListSelect();

public slots:
    void addHuman();
    void editHuman();
    void delHuman();
    void selectHuman();
    void setDelEditEnable();
    void setEnableCards();
    void addBlanks();

};


#endif // CUSTOMERS_H
