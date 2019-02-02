#include "humanedit.h"

HumanEdit::HumanEdit(unsigned code, bool activateCard, QWidget *parent)
    : QDialog(parent)
{


    this->setFixedWidth(450);
    this->code = code;
    this->activateCard = activateCard;
    if(code < 100000)this->close();
    getFields();
    QFont font("Lucida Console",12);
    QFont small("Arial Narrow",10);
    QFont evan("EanGnivc",34);
    QRegExp money("[0-9]{1,4}[.,]{0,1}[0-9]{0,2}");
    QRegExp intager("[0-9]{0,14}");
    this->setFont(font);


    this->setWindowTitle(QString::fromLocal8Bit((name).c_str()));
    QVBoxLayout * vert = new QVBoxLayout;

    QHBoxLayout *hor0 = new QHBoxLayout;
    QVBoxLayout *vert0 = new QVBoxLayout;
    lineName = new QLineEdit;
    lineName->setPlaceholderText("Ф.и.о...");
    lineName->setText(QString::fromLocal8Bit((name).c_str()));
    vert0->addWidget(lineName);
    buttonPrint = new QPushButton;
    buttonPrint->setFixedWidth(50);
    QPixmap pixmap("printer.bmp");
    QIcon ButtonIcon(pixmap);
    buttonPrint->setIcon(ButtonIcon);
    buttonPrint->setIconSize(pixmap.rect().size());

    lineTel = new QLineEdit;
    lineTel->setPlaceholderText("Телефон...");
    lineTel->setValidator(new QRegExpValidator(intager, this));
    lineTel->setText(QString::fromLocal8Bit((tel).c_str()));
    vert0->addWidget(lineTel);
    hor0->addLayout(vert0);
    if (!activateCard)hor0->addWidget(buttonPrint);
    vert->addLayout(hor0);

    QHBoxLayout * hor1 = new QHBoxLayout;
    QLabel * lab1 = new QLabel("- размер скидки %");
    spinDiscount = new QSpinBox;
    spinDiscount->setFixedWidth(200);
    spinDiscount->setMaximum(20);
    spinDiscount->setValue(discount);
    hor1->addWidget(spinDiscount);
    hor1->addWidget(lab1);
    vert->addLayout(hor1);


    QHBoxLayout * hor2 = new QHBoxLayout;
    QString str = "- долг (" + ini.getNationalCurrency() + ")";
    QLabel * lab2 = new QLabel(str);
    lineDebt = new QLineEdit;
    lineDebt->setFixedWidth(200);
    lineDebt->setPlaceholderText("Долг...");
    lineDebt->setValidator(new QRegExpValidator(intager, this));
    lineDebt->setText(QString::number(debt));
    hor2->addWidget(lineDebt);
    hor2->addWidget(lab2);
    vert->addLayout(hor2);

    QHBoxLayout * hor3 = new QHBoxLayout;
    QLabel * lab3 = new QLabel("- сумма покупок");
    lineSumm = new QLineEdit;
    lineSumm->setFixedWidth(200);
    lineSumm->setPlaceholderText("Сумма покупок..");
    lineSumm->setValidator(new QRegExpValidator(intager, this));
    lineSumm->setText(QString::number(summ));
    hor3->addWidget(lineSumm);
    hor3->addWidget(lab3);
    vert->addLayout(hor3);

    textDescription = new QTextEdit;
    textDescription->setPlaceholderText("Описание ...");
    textDescription->setFixedHeight(80);
    textDescription->setText(QString::fromLocal8Bit((description).c_str()));
    vert->addWidget(textDescription);


    ok = new QPushButton("Сохранить данные");
    vert->addWidget(ok);

    setLayout(vert);

    if(activateCard)
    {
        lineName->clear();
        lineTel->clear();
        textDescription->clear();
        lineDebt->clear();
        lineSumm->clear();
        ok->setEnabled(false);
        connect(lineName, SIGNAL(textEdited(QString)), this, SLOT(okEnabled()));
        connect(lineTel, SIGNAL(textEdited(QString)), this, SLOT(okEnabled()));
    }
    else
    {
        connect(buttonPrint, SIGNAL(clicked(bool)), this, SLOT(printSticker()));
    }

    connect(ok, SIGNAL(clicked(bool)), this, SLOT(itsOk()));


}

HumanEdit::~HumanEdit()
{

}

void HumanEdit::getFields()
{
    man = humanloader.getHuman(code);
    name = man.getName();
    tel = man.getTel();
    description = man.getDescription();
    debt = man.getDebt();
    summ = man.getSumm();
    discount = man.getDiscount();
}


void HumanEdit::itsOk()
{
    name = lineName->text().toLocal8Bit().constData();
    if(name.size()==0) name="no_name";
    tel = lineTel->text().toLocal8Bit().constData();
    if(tel.substr(0,1)=="!")tel = tel.substr(1, tel.size());
    if(tel.size()==0) tel="000";
    description = textDescription->toPlainText().toLocal8Bit().constData();
    if(description.size()==0) description="no_description";
    debt = textbutor.toDot(lineDebt->text()).toFloat();
    summ = textbutor.toDot(lineSumm->text()).toFloat();
    discount = spinDiscount->value();

    humanloader.editHuman(code, name, tel, description, discount, debt, summ);
    this->close();
}

void HumanEdit::okEnabled()
{
    if(!lineName->text().isEmpty() && !lineTel->text().isEmpty() )ok->setEnabled(true);
}

void HumanEdit::printSticker()
{
    if(QPrinterInfo::availablePrinterNames().size() > 0)
    {
        QString barcode = "575757" + QString::number(code);
        barcode = textbutor.checkSummGen(barcode);
#ifndef QT_NO_PRINTER
        QString Qname = "Карточка клиента";
        QFont small("Arial Narrow",9);
        int id = QFontDatabase::addApplicationFont("EANG000.ttf"); //путь к шрифту
        QString family = QFontDatabase::applicationFontFamilies(id).at(0); //имя шрифта
        QFont evan(family, 32);
        QPrinter printer(QPrinter::HighResolution);
        printer.setPrinterName(ini.getStickerPrinterName());
        printer.setPaperSize(QSizeF(38.0, 23.0), QPrinter::Millimeter);
        printer.setPageMargins(0.0, 0.0, 0.0, 0.0, QPrinter::Millimeter);
        QPainter paint(&printer);
        paint.setPen(Qt::black);
        paint.setFont(small);
        paint.drawText(QRect(20, 20, 400, 200), Qt::AlignLeft, Qname);
        paint.setFont(evan);
        paint.drawText(QRect(10, 60, 400, 200), Qt::AlignLeft, textbutor.barcodeToEvan(barcode));

#endif
    }
}

