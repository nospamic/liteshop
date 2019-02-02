#ifndef RECIVE_H
#define RECIVE_H

#include <QWidget>
#include <QDialog>
#include <QString>
#include <QDebug>
#include <QDesktopWidget>
#include <QListWidget>
#include <QValidator>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QSpinBox>
#include <QLabel>
#include <QTextEdit>
#include <QCheckBox>
#include <QMessageBox>
#include <QSpacerItem>
#include <QGroupBox>
#include "ini.h"
#include "textbutor.h"
#include "unit.h"
#include "unit_loader.h"
#include <vector>

class Recive : public QDialog
{
    Q_OBJECT
public:
    Recive(QWidget *parent = 0);
private:
    Ini ini;
    QLineEdit *line;
    QSpinBox *spin;
    QPushButton *del;
    QListWidget *list;
    QPushButton *ok;
    QPushButton *cancel;

    Unit_loader loader;
    std::vector <Unit> invoice;
    std::vector<int> quantity;
    float exchange;
    int scannedQuant;

    void findRepeat();
    void showInvoice();



private slots:
    void lineEnterPressed();
    void spinChanged();
    void setSpinQuantity();
    void delFromInvoice();
    void okClicked();
    void cancelClicked();
};

#endif // RECIVE_H
