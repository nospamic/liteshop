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
#include <QShortcut>
#include <windows.h>
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
    Seller(QWidget *parent = nullptr);
    ~Seller();

private:
    QVBoxLayout *vert;
    QVBoxLayout *vert0;
    QHBoxLayout *hor1;
    QLabel * lblHead;
    QListWidget *listSearsh;
    QLineEdit *lineBarcod;
    QCheckBox *checkBack;
    QPushButton *buttonDebt;
    //QPushButton *buttonSearsh;
    QListWidget *listCheck;
    QSpinBox *spinQuantity;
    QPushButton *buttonDel;
    //QPushButton *buttonPay;
    QLabel *labelSumm;
    QLineEdit *linePay;
    QLabel *labelChange;
    QLabel *labelDiscount;
    QPushButton *buttonNext;
    QLineEdit *lineManInfo;
    QTimer *timer;
    QTimer *payTimer;
    QTimer *timerActiveSeller;
    QTimer *timerFastFind;
    QPalette white;
    QPalette red;
    QPalette yellow;
    QPalette green;


    //Unit_loader uLoad;
    Textbutor textbutor;
    HumanLoader humanloader;
    Human man;
    std::vector<Unit>check;
    std::vector<int>quantity;
    float exchange;
    float checkSumm;
    int discount;
    std::string date;
    int activeSeller;
    QShortcut *keyF1;
    QShortcut *keyF2;
    QShortcut *keyF3;





    void checkShow();
    void findRepeat();
    std::string createLog();
    QString getQPrice(Unit unit);
    void changeHelp(float change);
    void reset();
    int result();
    void writeOff();
    void reject();
    QString getListItem(Unit &unit);

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
    void humanTest(const QString& barcode);
    void manShow();
    void nextPressed();
    void searsh(QString word);
    void printCheck();
    void backClicked();
    void colorLine();
    void debt();
    void setActiveSeller(int activeSeller);
    void resetActiveSeller();
    void fastFind();
    void on_payTimerTimeout();
    void on_timerFastFindTimeout();

};

#endif // SELLER_H
