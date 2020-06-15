#include "unit_edit.h"


Unit_edit::Unit_edit(unsigned code, QWidget *parent)
    : QDialog(parent)
{
    QFont font("Lucida Console",12);
    QFont small("Arial Narrow",10);
    int id = QFontDatabase::addApplicationFont("EANG000.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont evan(family, 32);
    //QFont evan("EanGnivc",34);

    QRegExp money("[0-9]{1,4}[.,]{0,1}[0-9]{0,2}");
    QRegExp intager("[0-9]{0,14}");
    this->setFont(font);
    this->setWindowTitle("Редактировать товар");

    QRect r = QApplication::desktop()->screenGeometry();
    this->resize(r.width()*0.4, this->height());

    //this->setFixedWidth(400);
    this->code = code;
    if(code < 100000)this->close();
    getFields();



    vert = new QVBoxLayout;

    lineName = new QLineEdit;
    lineName->setText(QString::fromLocal8Bit((unit.getName()).c_str()));
    lineName->setPlaceholderText("Наименование товара");
    //lineName->setFixedWidth(200);
    vert->addWidget(lineName);

    QHBoxLayout * hor0 = new QHBoxLayout;
    linePrice = new QLineEdit;
    linePrice->setValidator(new QRegExpValidator(money, this));
    linePrice->setText(QString::number(unit.getPrice()));
    QString mes  = "Цена ("+Ini::getInstance()->getAlternativeCurrency()+")";
    linePrice->setPlaceholderText(mes);
    hor0->addWidget(linePrice);
    QLabel * lblPrice = new QLabel("- цена в: ");
    hor0->addWidget(lblPrice);
    checkUah = new QCheckBox(Ini::getInstance()->getNationalCurrency());
    hor0->addWidget(checkUah);
    if(unit.isUah())checkUah->setChecked(true);
    checkUsd = new QCheckBox(Ini::getInstance()->getAlternativeCurrency());
    hor0->addWidget(checkUsd);
    vert->addLayout(hor0);
    if(!unit.isUah())checkUsd->setChecked(true);

    QHBoxLayout * hor1 = new QHBoxLayout;
    QLabel * lab1 = new QLabel("- количество ");
    spinQuant = new QSpinBox;
    spinQuant->setMaximum(99999);
    spinQuant->setValue(unit.getQuantity());
    hor1->addWidget(spinQuant);
    hor1->addWidget(lab1);
    vert->addLayout(hor1);

    QHBoxLayout * horSales = new QHBoxLayout;
    QLabel * labHor = new QLabel("- минимальный остаток");
    spinSales = new QSpinBox;
    spinSales->setValue(unit.getMinimum());
    horSales->addWidget(spinSales);
    horSales->addWidget(labHor);
    vert->addLayout(horSales);

    QHBoxLayout * hor2 = new QHBoxLayout;
    QLabel * lblBar = new QLabel("- штрихкод");
    lineBarcode = new QLineEdit;
    lineBarcode->setValidator(new QRegExpValidator(intager, this));
    QString qBarcode=QString::fromLocal8Bit((unit.getBarcode()).c_str());
    lineBarcode->setText(qBarcode);
    hor2->addWidget(lineBarcode);
    hor2->addWidget(lblBar);
    vert->addLayout(hor2);


    lineGroup = new QLineEdit;
    lineGroup->setText(QString::fromLocal8Bit((unit.getGroup()).c_str()));
    if(lineGroup->text() == "No group") lineGroup->clear();
    lineGroup->setPlaceholderText("Группа..");
    vert->addWidget(lineGroup);

    showGroups();

    textDescription = new QTextEdit;
    textDescription->setText(QString::fromLocal8Bit((unit.getDescription()).c_str()));
    if(textDescription->toPlainText() == "No description") textDescription->clear();
    textDescription->setPlaceholderText("Описание ...");
    textDescription->setFixedHeight(80);
    vert->addWidget(textDescription);

    QHBoxLayout * hor4 = new QHBoxLayout;
    textSticker = new QTextEdit;
    hor4->addWidget(textSticker);

    textSticker->moveCursor( QTextCursor::End );
    QTextCursor cursor( textSticker->textCursor() );
    QTextCharFormat format;
    format.setFont(small);
    cursor.setCharFormat( format );
    QString sales = "Продано " + QString::number(unit.getSales()) + " шт.\n";
    sales +="Продаж в неделю: ";
    sales += QString::number(double(unit.getSalesPerWeek()), 'g' ,2);

    sales +=" шт.\n";
    cursor.insertText(sales);

    format.setFont(evan);
    cursor.setCharFormat( format );
    cursor.insertText(textbutor.barcodeToEvan(QString::fromLocal8Bit(unit.getBarcode().c_str())));

    format.setFont(small);
    cursor.setCharFormat( format );
    QString info = "\nИнфо:\n" + QString::fromLocal8Bit((unit.getHidden()).c_str());
    cursor.insertText(info);
    textSticker->moveCursor( QTextCursor::Start );
    textSticker->setReadOnly(true);


    QLabel * labelPrint = new QLabel(" Печатать \n ценники: ");
    hor4->addWidget(labelPrint);
    spinPrint = new QSpinBox();
    spinPrint->setMinimum(0);
    spinPrint->setFixedHeight(40);
    spinPrint->setFixedWidth(50);
    hor4->addWidget(spinPrint);
    vert->addLayout(hor4);

    ok = new QPushButton(" \n Сохранить / печатать ценники \n ");
    ok->setAutoDefault(false);
    vert->addWidget(ok);

    setLayout(vert);

    connect(ok, SIGNAL(clicked(bool)), this, SLOT(itsOk()));
    connect(checkUah, SIGNAL(clicked(bool)), this, SLOT(on_checkUah()));
    connect(checkUsd, SIGNAL(clicked(bool)), this, SLOT(on_checkUsd()));
    connect(spinPrint, SIGNAL(valueChanged(int)), this, SLOT(on_changePrint()));
    for(auto radio : groupList)
        connect(radio, SIGNAL(clicked(bool)), this, SLOT(setGroup()));

}

Unit_edit::~Unit_edit()
{

}


void Unit_edit::getFields()
{
    unit = Unit_loader::get()->getUnit(code);
    isUah = unit.isUah();
}


void Unit_edit::barcodeRepair()
{
    if (lineBarcode->text() != textbutor.makeBarcode(code))
    {
        lineBarcode->setText(textbutor.makeBarcode(code));
    }
}


void Unit_edit::showGroups(){
    horGroups = new QHBoxLayout(this);
    vertGroup0 = new QVBoxLayout(this);
    vertGroup1 = new QVBoxLayout;
    vertGroup2 = new QVBoxLayout;
    vertGroup3 = new QVBoxLayout;



   this->groupBox = new QGroupBox;
    groupBox->setLayout(horGroups);

    vert->addWidget(groupBox);
    this->groupStyleSheet = groupBox->styleSheet();
    if(this->lineGroup->text().isEmpty()) {
        groupBox->setStyleSheet("QRadioButton {font-size: 12pt; font-family: Lucida Console;} QGroupBox {background-color: red;}");
   }

    std::vector<QString>q_goups = Unit_loader::get()->getGroups();
    for(auto str : q_goups){
        QRadioButton * check = new QRadioButton(str);
        groupList.push_back(check);
    }
    for(un n = 0; n< groupList.size(); n++){
        if(n<3)         vertGroup0->addWidget(groupList[n]);
        if(n>=3 && n<6) vertGroup1->addWidget(groupList[n]);
        if(n>=6 && n<9) vertGroup2->addWidget(groupList[n]);
        if(n>=9) vertGroup3->addWidget(groupList[n]);
        if (lineGroup->text().size() > 0 && lineGroup->text() == q_goups[n]){
            groupList[n]->setChecked(true);
        }
    }
    vertGroup0->addItem(new QSpacerItem(0,0,QSizePolicy::Expanding, QSizePolicy::Expanding));
    vertGroup1->addItem(new QSpacerItem(0,0,QSizePolicy::Expanding, QSizePolicy::Expanding));
    vertGroup2->addItem(new QSpacerItem(0,0,QSizePolicy::Expanding, QSizePolicy::Expanding));
    vertGroup3->addItem(new QSpacerItem(0,0,QSizePolicy::Expanding, QSizePolicy::Expanding));
    horGroups->addLayout(vertGroup0);
    horGroups->addLayout(vertGroup1);
    horGroups->addLayout(vertGroup2);
    horGroups->addLayout(vertGroup3);
    vert->addLayout(horGroups);

}


void Unit_edit::itsOk()
{
    std::string name = lineName->text().toLocal8Bit().constData();
    if (name!="") unit.setName(name);

    unit.setQuantity(spinQuant->value());

    unit.setPrice(textbutor.toDot(linePrice->text()).toFloat());

    std::string barcode = lineBarcode->text().toLocal8Bit().constData();
    if (barcode!="") unit.setBarcode(barcode);

    //unit.setEcharge(textbutor.toDot(lineEcharge->text()).toFloat());


    //std::string section = lineSection->text().toLocal8Bit().constData();
    //if (section!="") unit.setSection(section);

    std::string group = lineGroup->text().toLocal8Bit().constData();
    if (group!="") unit.setGroup(group);

    QString descr = textDescription->toPlainText();
    std::string description = descr.toLocal8Bit().constData();
    if (description != "") unit.setDescription(description);

    unit.setMinimum(spinSales->value());

    if(Unit_loader::get()->getUnit(barcode).getCode() == code || !Unit_loader::get()->unitExists(unit.getBarcode()))
    {
        Unit_loader::get()->edit(unit);
        printing();
        this->close();
    }
    else
    {
        QString message=QString::fromLocal8Bit(Unit_loader::get()->nameByBarcode(barcode).c_str());
        QMessageBox msg;
        msg.setText("Товар с таким штрих-кодом уже есть в базе: " + message);
        msg.exec();
    }
}

void Unit_edit::printing()
{

#ifndef QT_NO_PRINTER
    if(QPrinterInfo::availablePrinterNames().size() > 0)
    {
        ok->setEnabled(false);
        int yCorrect = Ini::getInstance()->getStickerVertCorrect();
        std::vector<QString>words = textbutor.stringToVector(lineName->text());

        QString upWord = "";
        QString downWord = "";
        if (words.size()>=2)
        {
            upWord = words[0] + " " + words[1];
            if(upWord.size() > 12)
            {
                upWord = words[0];
                for (unsigned n = 1; n < words.size(); n++) {downWord+=words[n]; downWord+=" ";}
            }
            else
            {
                upWord = words[0] + " " + words[1];
                for (unsigned n = 2; n < words.size(); n++) {downWord+=words[n]; downWord+=" ";}
            }
        }
        else
        {
            upWord = words[0];
        }

        QString Qname = upWord;
        QString QnameRight = textbutor.cutter(downWord, 25);

        QString Qprice = textbutor.makePrice(textbutor.toDot(linePrice->text()).toFloat(), isUah) + "\n";
        QFont small("Arial Narrow",9);
        QFont big("Arial Narrow", 10);
        //big.setBold(true);
        int id = QFontDatabase::addApplicationFont("EANG000.ttf"); //путь к шрифту
        QString family = QFontDatabase::applicationFontFamilies(id).at(0); //имя шрифта
        QFont evan(family, 32);

        QPrinter printer(QPrinter::HighResolution);
        printer.setPrinterName(Ini::getInstance()->getStickerPrinterName());
        printer.setPaperSize(QSizeF(38.0, 23.0), QPrinter::Millimeter);

        for(int n = 0; n < spinPrint->value(); ++n )
        {
            printer.setPageMargins(0.0, 0.0, 0.0, 0.0, QPrinter::Millimeter);
            QPainter paint(&printer);
            paint.setPen(Qt::black);
            paint.setFont(small);
            paint.drawText(QRect(10, 20 + yCorrect, 400, 200), Qt::AlignLeft, Qname);
            paint.setFont(big);
            paint.drawText(QRect(210, 20 + yCorrect, 200, 100), Qt::AlignLeft, Qprice);
            paint.setFont(evan);
            paint.drawText(QRect(10, 60 + yCorrect, 400, 200), Qt::AlignLeft, textbutor.barcodeToEvan(lineBarcode->text()));
            paint.setFont(small);
            paint.drawText(QRect(10, 155 + yCorrect, 400, 200), Qt::AlignLeft, QnameRight);
        }
        ok->setEnabled(true);
    }
#endif
//----------------------------------------------------
//    QFont evan("EanGnivc",70);
//    QString text = textbutor.barcodeToEvan(lineBarcode->text());
//    QPrinter printer(QPrinter::HighResolution);
//    printer.setFullPage(true);
//    printer.setPageMargins(QMarginsF(2,2,2,2));
//    textSticker->setContentsMargins(0,0,0,0);
//    QTextDocument *doc = new QTextDocument;
//    doc->setPageSize(QSizeF(printer.pageRect().size()));
//    doc->setDefaultFont(evan);
//    doc->setPlainText(text);
//    doc->print(&printer);
//---------------------------------------------------------------


}


void Unit_edit::on_checkUah()
{
    checkUsd->setChecked(false);
    unit.setUah(true);

}


void Unit_edit::on_checkUsd()
{
    checkUah->setChecked(false);
    unit.setUah(false);
}


void Unit_edit::setGroup()
{
    for(auto radio : groupList){
        if(radio->isChecked()) lineGroup->setText(radio->text());
    }
    groupBox->setStyleSheet("QRadioButton {font-size: 12pt; font-family: Lucida Console;}");
}

void Unit_edit::on_changePrint()
{
    if (this->spinPrint->value() > this->spinQuant->value()) this->spinQuant->setValue(this->spinPrint->value());
}
