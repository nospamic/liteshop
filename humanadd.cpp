#include "humanadd.h"


HumanAdd::HumanAdd(QWidget *parent)
    : QDialog(parent)
{
    QFont font("Lucida Console",12);
    QFont small("Arial Narrow",10);
    QFont evan("EanGnivc",34);
    QRegExp money("[0-9]{1,4}[.,]{0,1}[0-9]{0,2}");
    QRegExp intager("[0-9]{0,14}");
    this->setFont(font);

    this->setWindowTitle("Добавить клиента");
    QVBoxLayout * vert = new QVBoxLayout;

    lineName = new QLineEdit;
    lineName->setPlaceholderText("Ф.и.о...");
    vert->addWidget(lineName);

    lineTel = new QLineEdit;
    lineTel->setPlaceholderText("Телефон...");
    lineTel->setValidator(new QRegExpValidator(intager, this));
    vert->addWidget(lineTel);

    QHBoxLayout * hor1 = new QHBoxLayout;
    QLabel * lab1 = new QLabel("- размер скидки %");
    spinDiscount = new QSpinBox;
    spinDiscount->setMaximum(20);
    hor1->addWidget(spinDiscount);
    hor1->addWidget(lab1);
    vert->addLayout(hor1);

    textDescription = new QTextEdit;
    textDescription->setPlaceholderText("Описание ...");
    textDescription->setFixedHeight(80);
    vert->addWidget(textDescription);


    ok = new QPushButton("Добавить клиента");
    vert->addWidget(ok);


    setLayout(vert);

    connect(ok, SIGNAL(clicked(bool)), this, SLOT(itsOk()));

}

HumanAdd::~HumanAdd()
{

}


void HumanAdd::itsOk()
{
    if(!lineName->text().isEmpty() && !lineTel->text().isEmpty())
    {

        std::string name = lineName->text().toLocal8Bit().constData();
        std::string tel = lineTel->text().toLocal8Bit().constData();
        int discount = spinDiscount->value();
        std::string description = textDescription->toPlainText().toLocal8Bit().constData();
        if (description.size()==0) description="no_description";
        humanloader.addHuman(name, tel, description, discount);
        this->close();
    }

}
