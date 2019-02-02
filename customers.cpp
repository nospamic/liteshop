#include "customers.h"

Customers::Customers(QWidget *parent)
    : QDialog(parent)
{
    QFont font("Lucida Console",12);
    this->setFont(font);
    this->setWindowTitle("Клиенты");
    this->setFixedWidth(720);
    QVBoxLayout * vert = new QVBoxLayout;

    QHBoxLayout * hor0 = new QHBoxLayout;
    buttonCards = new QPushButton("Распечатать ");
    hor0->addWidget(buttonCards);
    buttonCards->setDisabled(true);
    QLabel * lab1 = new QLabel(" скидочных карточек");
    spinCards = new QSpinBox;
    spinCards->setMaximum(50);
    hor0->addWidget(spinCards);
    hor0->addWidget(lab1);
    vert->addLayout(hor0);

    QFrame *line;
    line = new QFrame(this);
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    vert->addWidget(line);



    list = new QListWidget;
    vert->addWidget(list);
    list->setFont(font);

    QHBoxLayout * hor = new QHBoxLayout;

    lineSearsh = new QLineEdit;
    hor->addWidget(lineSearsh);

    buttonAdd = new QPushButton("Добавить");
    hor->addWidget(buttonAdd);

    buttonEdit = new QPushButton("Редактировать");
    hor->addWidget(buttonEdit);

    buttonDelete = new QPushButton("Удалить");
    hor->addWidget(buttonDelete);

    vert->addLayout(hor);

    setLayout(vert);

    getListSelect();

    buttonAdd->setAutoDefault(false);
    buttonDelete->setEnabled(false);
    buttonEdit->setEnabled(false);
    lineSearsh->setFocus();

    connect(buttonAdd, SIGNAL(clicked(bool)), this, SLOT(addHuman()));
    connect(buttonDelete, SIGNAL(clicked(bool)), this, SLOT(delHuman()));
    connect(buttonEdit, SIGNAL(clicked(bool)), this, SLOT(editHuman()));
    connect(lineSearsh, SIGNAL(returnPressed()), this, SLOT(selectHuman()));
    connect(list, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(editHuman()));
    connect(list, SIGNAL(clicked(QModelIndex)), this, SLOT(setDelEditEnable()));
    connect(spinCards, SIGNAL(valueChanged(int)), this, SLOT(setEnableCards()));
    connect(buttonCards, SIGNAL(clicked(bool)), this, SLOT(addBlanks()));

}

Customers::~Customers()
{

}

void Customers::getListSelect()
{
    list->clear();
    QString word = lineSearsh->text();
    int size = humanloader.size;
    Human *base = humanloader.base;

    if (word.isEmpty())
    {
        for(int n=0; n<size; n++)
        {
            QString code = QString::number(base[n].getCode());
            QString name = textbutor.cutter(QString::fromLocal8Bit((base[n].getName()).c_str()),20);
            QString tel = textbutor.cutter(QString::fromLocal8Bit((base[n].getTel()).c_str()),14);
            QString discount = textbutor.cutter(QString::number(base[n].getDiscount())+"%", 4);
            QString debt = textbutor.cutter(QString::number(base[n].getDebt()) + "грн.", 6);
            list->addItem(code+"  " + name + "  " + discount + "  " + debt + "  " + tel);
        }
    }
    else
    {
        word = word.toLower();
        for(int n=0; n<size; n++)
        {
            QString code = QString::number(base[n].getCode());
            QString name = textbutor.cutter(QString::fromLocal8Bit((base[n].getName()).c_str()),20);
            QString tel = textbutor.cutter(QString::fromLocal8Bit((base[n].getTel()).c_str()),14);
            QString discount = textbutor.cutter(QString::number(base[n].getDiscount())+"%", 4);
            QString debt = textbutor.cutter(QString::number(base[n].getDebt()) + "грн.", 6);

            if (name.contains(word, Qt::CaseInsensitive))
            {
                list->addItem(code+"  " + name + "  " + discount + "  " + debt + "  " + tel);
            }
        }
    }

    buttonEdit->setEnabled(false);
    buttonDelete->setEnabled(false);
}

void Customers::addHuman()
{
    HumanAdd * add = new HumanAdd(this);
    add->show();
    add->exec();
    humanloader.loadBase();
    getListSelect();
}

void Customers::editHuman()
{
    QString str = list->currentItem()->text().left(6);
    unsigned code = str.toInt();
    HumanEdit * edit = new HumanEdit(code, false, this);
    edit->show();
    edit->exec();
    humanloader.loadBase();
    getListSelect();
}

void Customers::delHuman()
{
    int code = list->currentItem()->text().left(6).toInt();
    humanloader.delHuman(code);
    getListSelect();
}

void Customers::selectHuman()
{
    getListSelect();
}

void Customers::setDelEditEnable()
{
    buttonDelete->setEnabled(true);
    buttonEdit->setEnabled(true);
}

void Customers::setEnableCards()
{
    buttonCards->setEnabled(true);
}

void Customers::addBlanks()
{
    unsigned size = spinCards->value();
    for (unsigned n=0; n<size; n++)
    {
        humanloader.addHuman("--", "!", "--", 3);

        int code = humanloader.getLastCode();
        QString barcode = "575757" + QString::number(code);
        barcode = textbutor.checkSummGen(barcode);
#ifndef QT_NO_PRINTER
        if(QPrinterInfo::availablePrinterNames().size() > 0)
        {
            QString Qname = "Карточка клиента";
            QFont small("Arial Narrow",9);
            int id = QFontDatabase::addApplicationFont("EANG000.ttf"); //путь к шрифту
            QString family = QFontDatabase::applicationFontFamilies(id).at(0); //имя шрифта
            QFont evan(family, 32);
            QPrinter printer(QPrinter::HighResolution);
            printer.setPrinterName(ini.getStickerPrinterName());
            QPainter paint(&printer);
            paint.setPen(Qt::black);
            paint.setFont(small);
            paint.drawText(QRect(20, 20, 400, 200), Qt::AlignLeft, Qname);
            paint.setFont(evan);
            paint.drawText(QRect(10, 60, 400, 200), Qt::AlignLeft, textbutor.barcodeToEvan(barcode));
        }
#endif
    }

    spinCards->setValue(0);
    buttonCards->setEnabled(false);
    getListSelect();
}
