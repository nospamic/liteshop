#include "options.h"

Options::Options(QWidget *parent) : QDialog(parent)
{

    this->setWindowTitle("Настройки");


    QVBoxLayout *vertComun = new QVBoxLayout;
    QHBoxLayout *hor = new QHBoxLayout;
    QVBoxLayout *vertLabel = new QVBoxLayout;
    QVBoxLayout *vertLine = new QVBoxLayout;
    QRegExp intager("[-]{0,1}[0-9]{0,3}");

    QLabel *labelCorrect = new QLabel("Вертикальное смещение стикера - ");
    vertLabel->addWidget(labelCorrect);
    stickerVertCorrect = new QLineEdit;
    vertLine->addWidget(stickerVertCorrect);
    stickerVertCorrect->setValidator(new QRegExpValidator(intager, this));
    stickerVertCorrect->setText(QString::number(Ini::getInstance()->getStickerVertCorrect()));

    QLabel *labelCheck = new QLabel("Имя принтера чеков - ");
    vertLabel->addWidget(labelCheck);
    checkPrinterName = new QLineEdit;
    vertLine->addWidget(checkPrinterName);
    checkPrinterName->setText(Ini::getInstance()->getCheckPrinterName());

    QLabel *labelSticker = new QLabel("Имя принтера этикеток - ");
    vertLabel->addWidget(labelSticker);
    stickerPrinterName = new QLineEdit;
    vertLine->addWidget(stickerPrinterName);
    stickerPrinterName->setText(Ini::getInstance()->getStickerPrinterName());

    QLabel *labelreservPath = new QLabel("Путь для резервного копирования - ");
    vertLabel->addWidget(labelreservPath);
    reservPath = new QLineEdit;
    vertLine->addWidget(reservPath);
    reservPath->setText(Ini::getInstance()->getReservPath());

    QLabel *labelnationalCurrency = new QLabel("Национальная валюта - ");
    vertLabel->addWidget(labelnationalCurrency);
    nationalCurrency = new QLineEdit;
    vertLine->addWidget(nationalCurrency);
    nationalCurrency->setText(Ini::getInstance()->getNationalCurrency());

    QLabel *labelalternativeCurrency = new QLabel("Альтернативная валюта - ");
    vertLabel->addWidget(labelalternativeCurrency);
    alternativeCurrency = new QLineEdit;
    vertLine->addWidget(alternativeCurrency);
    alternativeCurrency->setText(Ini::getInstance()->getAlternativeCurrency());

    QLabel *labelstoreName= new QLabel("Название магазина - ");
    vertLabel->addWidget(labelstoreName);
    storeName = new QLineEdit;
    vertLine->addWidget(storeName);
    storeName->setText(Ini::getInstance()->getStoreName());

    QLabel *labelstoreAddress= new QLabel("Адрес магазина - ");
    vertLabel->addWidget(labelstoreAddress);
    storeAddress = new QLineEdit;
    vertLine->addWidget(storeAddress);
    storeAddress->setText(Ini::getInstance()->getStoreAddress());


    hor->addLayout(vertLabel);
    hor->addLayout(vertLine);
    QGroupBox *boxUp = new QGroupBox;
    boxUp->setLayout(hor);
    vertComun->addWidget(boxUp);



    QGroupBox *box = new QGroupBox("Текст в конце чека:");
    QVBoxLayout *vertText = new QVBoxLayout;
//    QLabel *labelcheckText= new QLabel("Текст на чеке - ");
//    vertComun->addWidget(labelcheckText);
    checkText = new QTextEdit;
    checkText->setFixedHeight(100);
    vertText->addWidget(checkText);
    checkText->setText(Ini::getInstance()->getCheckText());
    box->setLayout(vertText);
    vertComun->addWidget(box);



    QHBoxLayout *horButton = new QHBoxLayout;
    buttonSave = new QPushButton("Сохранить");
    horButton->addWidget(buttonSave);
    buttonCancel = new QPushButton("Отмена");
    horButton->addWidget(buttonCancel);
    vertComun->addLayout(horButton);

//    QSpacerItem *spacer = new QSpacerItem(20,20, QSizePolicy::Minimum, QSizePolicy::Expanding);
//    vertLabel->addItem(spacer);


    this->setLayout(vertComun);

    connect(buttonSave,SIGNAL(clicked(bool)), this, SLOT(onButtonSaveClicked()));
    connect(buttonCancel,SIGNAL(clicked(bool)), this, SLOT(onButtonCancelClicked()));
}

Options::~Options()
{

}


void Options::onButtonSaveClicked()
{
    Ini::getInstance()->setStickerVertCorrect(stickerVertCorrect->text().toInt());
    if (!checkPrinterName->text().isEmpty())Ini::getInstance()->setCheckPrinterName("---");
    if (!stickerPrinterName->text().isEmpty())Ini::getInstance()->setStickerPrinterName(stickerPrinterName->text());
    if (!reservPath->text().isEmpty())Ini::getInstance()->setReservPath(reservPath->text());
    Ini::getInstance()->setNationalCurrency(nationalCurrency->text());
    Ini::getInstance()->setAlternativeCurrency(alternativeCurrency->text());
    Ini::getInstance()->setStoreName(storeName->text());
    Ini::getInstance()->setStoreAddress(storeAddress->text());
    Ini::getInstance()->setCheckText(checkText->toPlainText());
    Ini::getInstance()->save();
    this->close();
}


void Options::onButtonCancelClicked()
{
    this->close();
}



