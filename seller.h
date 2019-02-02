#ifndef SELLER_H
#define SELLER_H


#include <QDesktopWidget>
#include <QDebug>
#include <QValidator>
#include <QDialog>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QSpinBox>
#include <QLabel>
#include <QTextEdit>
#include <QListWidget>
#include <QFont>
#include <QDateTime>
#include <vector>
#include <cmath>
#include <QTimer>
#include <QFontDatabase>
#include <QPrinterInfo>
#include "unit_loader.h"
#include "unit.h"
#include "textbutor.h"
#include "human.h"
#include "humanedit.h"
#include "humanloader.h"
#include "ini.h"

class Seller : public QDialog
{
    Q_OBJECT

public:
    Seller(QWidget *parent = 0);
    ~Seller();

private:
    QListWidget *listSearsh;
    QLineEdit *lineBarcod;
    QCheckBox *checkBack;
    QPushButton *buttonDebt;
    QPushButton *buttonSearsh;
    QListWidget *listCheck;
    QSpinBox *spinQuantity;
    QPushButton *buttonDel;
    QPushButton *buttonPay;
    QLabel *labelSumm;
    QLineEdit *linePay;
    QLabel *labelChange;
    QLabel *labelDiscount;
    QPushButton *buttonNext;
    QLineEdit *lineManInfo;
    QTimer *timer;
    QTimer *payTimer;
    QPalette white;
    QPalette red;
    QPalette yellow;
    QPalette green;


    Unit_loader uLoad;
    Textbutor textbutor;
    HumanLoader humanloader;
    Human man;
    Ini ini;
    std::vector<Unit>check;
    std::vector<int>quantity;
    float exchange;
    float checkSumm;
    int discount;
    std::string date;





    void checkShow();
    void findRepeat();
    std::string createLog();
    QString getQPrice(Unit unit);
    void changeHelp(float change);
    void reset();
    int result();
    void writeOff();

private slots:
    void addToCheck();
    void setSpinQuantity();
    void changeQuantity();
    void barcodeScanned();
    void getListSelect();
    void sold();
    void showChange();
    void delFromCheck();
    void delEnable();
    void humanTest(QString barcode);
    void manShow();
    void nextPressed();
    void searsh(QString word);
    void printCheck();
    void backClicked();
    void colorLine();
    void debt();

};

#endif // SELLER_H
