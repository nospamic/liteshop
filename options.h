#ifndef OPTIONS_H
#define OPTIONS_H


#include <QWidget>
#include <QDialog>
#include <QString>
#include <QDebug>
#include <QDesktopWidget>
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
#include <ini.h>
#include <textbutor.h>

class Options : public QDialog
{
    Q_OBJECT
public:
    Options(QWidget *parent = 0);
    ~Options();


public slots:
    void onButtonSaveClicked();
    void onButtonCancelClicked();

private:
     Ini ini;

    QLineEdit * stickerVertCorrect;
    QLineEdit * checkPrinterName;
    QLineEdit * stickerPrinterName;
    QLineEdit * reservPath;
    QLineEdit * nationalCurrency;
    QLineEdit * alternativeCurrency;
    QLineEdit * storeName;
    QLineEdit * storeAddress;
    QTextEdit * checkText;
    QPushButton *buttonSave;
    QPushButton *buttonCancel;


};

#endif // OPTIONS_H
