#include "recive.h"

Recive::Recive(QWidget *parent) : QDialog(parent)
{
    this->setWindowTitle("Прием товара по штрихкоду");
    this->setFixedWidth(650);
    QFont font("Lucida Console",12);
    this->setFont(font);
    exchange = loader.getUnit(100000).getPrice();
    QRegExp intager("[0-9]{0,14}");

    QVBoxLayout *vert = new QVBoxLayout;

    QHBoxLayout *hor0 = new QHBoxLayout;

    line = new QLineEdit;
    line->setPlaceholderText("Штрихкод...");
    line->setValidator(new QRegExpValidator(intager, this));
    hor0->addWidget(line);

    spin = new QSpinBox;
    spin->setEnabled(false);
    hor0->addWidget(spin);

    del = new QPushButton("Удалить");
    hor0->addWidget(del);
    del->setEnabled(false);
    del->setAutoDefault(false);


    list = new QListWidget;
    list->setFont(font);


    QHBoxLayout *hor = new QHBoxLayout;

    ok = new QPushButton("Принять товар");
    ok->setAutoDefault(false);
    cancel = new QPushButton("Отмена");
    cancel->setAutoDefault(false);

    hor->addWidget(ok);
    hor->addWidget(cancel);

    vert->addLayout(hor0);
    vert->addWidget(list);
    vert->addLayout(hor);
    this->setLayout(vert);

    connect(line, SIGNAL(returnPressed()), SLOT(lineEnterPressed()));
    connect(spin, SIGNAL(valueChanged(int)), SLOT(spinChanged()));
    connect(list, SIGNAL(clicked(QModelIndex)), this, SLOT(setSpinQuantity()));
    connect(del, SIGNAL(clicked(bool)), this, SLOT(delFromInvoice()));
    connect(ok, SIGNAL(clicked(bool)), this, SLOT(okClicked()));
    connect(cancel, SIGNAL(clicked(bool)), this, SLOT(cancelClicked()));


}

void Recive::findRepeat()
{
    Unit item = invoice[invoice.size()-1];
    for(unsigned n=0; n<(invoice.size()-1); n++)
    {
        if(item.getCode()==invoice[n].getCode())
        {
            quantity[n]++;
            invoice.pop_back();
            quantity.pop_back();
        }
    }
}


void Recive::showInvoice()
{
    list->clear();
    for(unsigned n=0; n<invoice.size(); n++)
    {
        QString str = Textbutor::cutter(Textbutor::stdToQ(invoice[n].getName()), 28);
        str += "    ";
        str += Textbutor::cutter(QString::number(quantity[n]), 3);
        str += " X  ";
        QString currency = invoice[n].isUah()?ini.getNationalCurrency():ini.getAlternativeCurrency();

        str += Textbutor::cutter(QString::number(invoice[n].getPrice()),6);
        str += " " + currency;
        list->addItem(str);
        invoice.size()>0?spin->setEnabled(true):spin->setEnabled(false);

        //list->setCurrentRow(invoice.size()-1);
    }
    qDebug()<<"inv - "<<invoice.size()<<"  quan - "<<quantity.size();
    for (un n=0; n<invoice.size(); n++)
    {
        qDebug()<<n<<" - "<<Textbutor::stdToQ(invoice[n].getName())<<" X "<<quantity[n];
    }

}


void Recive::lineEnterPressed()
{
    if (line->text().size() > 0 && line->text().size() < 6 )
    {
        scannedQuant = line->text().toInt();
        if(quantity.size()>0)
        {
            quantity[quantity.size()-1] = scannedQuant;
            scannedQuant = 0;
            line->clear();
        }
    }
    else
    {
        invoice.push_back(loader.getUnit(Textbutor::qToStd(line->text())));
        quantity.push_back(1);
        findRepeat();
    }
    line->clear();
    showInvoice();
    list->setCurrentRow(invoice.size()-1);
    setSpinQuantity();
    line->setFocus();
    //qDebug()<<"inv - "<<invoice.size()<<"  quan - "<<quantity.size();
}


void Recive::spinChanged()
{
    if (invoice.size()>0)
    {
        int position = list->currentRow();
        if(quantity[position] != spin->value())
        {
            quantity[position] = spin->value();
            showInvoice();
        }
        list->setCurrentRow(position);
        line->setFocus();
    }
}

void Recive::setSpinQuantity()
{
    int position = list->currentRow();
    int quant = quantity[position];
    spin->setValue(quant);
    list->setCurrentRow(position);
    line->setFocus();
    del->setEnabled(true);
}


void Recive::delFromInvoice()
{
    if(invoice.size()>1)
    {
        int position = list->currentRow();
        invoice.erase(invoice.begin()+position);
        quantity.erase(quantity.begin()+position);
    }
    else
    {
        invoice.clear();
        quantity.clear();
    }
    del->setEnabled(false);
    line->setFocus();
    showInvoice();
    qDebug()<<"delete";
}


void Recive::okClicked()
{
    for (un n=0; n<invoice.size(); n++)
    {
        if (invoice[n].getQuantity() < 0) invoice[n].setQuantity(0);
        invoice[n].setQuantity(invoice[n].getQuantity()+quantity[n]);
    }
    loader.editSome(invoice);
    this->close();
}

void Recive::cancelClicked()
{
    this->close();
}
