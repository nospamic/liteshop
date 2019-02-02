#ifndef HUMANADD_H
#define HUMANADD_H

#include <iostream>
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
#include <QTextEdit>
#include "textbutor.h"
#include "humanloader.h"

class HumanAdd : public QDialog
{
    Q_OBJECT

public:
    HumanAdd(QWidget *parent = 0);
    ~HumanAdd();
private:
    QLineEdit * lineName;
    QLineEdit * lineTel;
    QSpinBox * spinDiscount;
    QTextEdit * textDescription;
    QPushButton * ok;

    Textbutor textbutor;
    HumanLoader humanloader;


public slots:
    void itsOk();

};

#endif // HUMANADD_H
