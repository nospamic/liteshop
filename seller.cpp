#include "seller.h"

Seller::Seller(QWidget *parent)
    : QDialog(parent)
{
    man.setName("no");
    discount = 0;
    checkSumm = 0;
    this->setWindowTitle("Продавец");
    //QRegExp intager("[0-9]{0,14}");
    QRegExp money("[0-9]{1,13}[.,]{0,1}[0-9]{0,2}");
    exchange = Unit_loader::get()->getUnit(100000).getPrice();

    this->activeSeller = 1;

    keyF1 = new QShortcut(this);
    keyF1->setKey(Qt::Key_F1);
    keyF2 = new QShortcut(this);
    keyF2->setKey(Qt::Key_F2);
    keyF3 = new QShortcut(this);
    keyF3->setKey(Qt::Key_F3);

    timer = new QTimer(this);
    payTimer = new QTimer(this);
    timerActiveSeller = new QTimer(this);
    timerFastFind = new QTimer(this);


    QFont font("Lucida Console",12);
    QFont small("Lucida Console",8);
    this->setFont(font);

    white.setColor(QPalette::Base, Qt::white);
    red.setColor(QPalette::Base, Qt::red);
    yellow.setColor(QPalette::Base, Qt::yellow);
    green.setColor(QPalette::Base, Qt::green);

    QRect r =  QApplication::desktop()->screenGeometry();
    this->resize(800, int(r.height()*0.8));

    this->setStyleSheet("QCheckBox { border: 1px solid gray; padding: 2px }");

    vert = new QVBoxLayout(this);
    QString str = " Код          Название                                   Цена(" + Ini::getInstance()->getNationalCurrency() + ")       К-во(шт.)";
    lblHead = new QLabel(str,this);
    lblHead->setFont(small);
    vert->addWidget(lblHead);
    listSearsh = new QListWidget(this);
    listSearsh->setFont(font);
    vert->addWidget(listSearsh);


    hor1 = new QHBoxLayout(this);
    lineBarcod = new QLineEdit(this);
    lineBarcod->setPlaceholderText("Найти...");
    lineBarcod->setAutoFillBackground(true);
    //lineBarcod->setValidator(new QRegExpValidator(intager, this));
    hor1->addWidget(lineBarcod);
    checkBack = new QCheckBox("Возврат", this);
    hor1->addWidget(checkBack);
    buttonDebt = new QPushButton("Долг", this);
    buttonDebt->setAutoDefault(false);
    buttonDebt->setEnabled(false);
    hor1->addWidget(buttonDebt);

    vert->addLayout(hor1);

    auto *hor2 = new QHBoxLayout(this);
    vert0 = new QVBoxLayout();
    listCheck = new QListWidget(this);
    listCheck->setFont(font);
    vert0->addWidget(listCheck);
    lineManInfo = new QLineEdit(this);
    lineManInfo->setFont(small);
    lineManInfo->setDisabled(true);
    vert0->addWidget(lineManInfo);
    hor2->addLayout(vert0);

    auto *vert2 = new QVBoxLayout(this);
    spinQuantity = new QSpinBox(this);
    spinQuantity->setMaximum(999);
    spinQuantity->setEnabled(false);
    buttonDel = new QPushButton("X",this);
    buttonDel->setEnabled(false);
    buttonDel->setAutoDefault(false);
    vert2->addWidget(spinQuantity);
    vert2->addWidget(buttonDel);
    labelDiscount = new QLabel(this);
    QPalette yellowLabel;
    yellowLabel.setColor(QPalette::Background, Qt::yellow);
    labelDiscount->setAutoFillBackground(false);
    labelDiscount->setPalette(yellowLabel);

    vert2->addWidget(labelDiscount);
    buttonNext = new QPushButton(this);
    QPixmap pixmap("next.bmp");
    QIcon ButtonIcon(pixmap);
    buttonNext->setIcon(ButtonIcon);
    buttonNext->setIconSize(pixmap.rect().size());
    vert2->addWidget(buttonNext);
    buttonNext->setEnabled(false);
    buttonNext->setAutoDefault(false);
    hor2->addLayout(vert2);

    vert->addLayout(hor2);

    auto *hor3 = new QHBoxLayout(this);
    labelSumm = new QLabel("Сумма: --", this);
    linePay = new QLineEdit(this);
    linePay->setValidator(new QRegExpValidator(money, this));
    linePay->setPlaceholderText("Оплачено...");
    labelChange = new QLabel("Сдача: --", this);
    hor3->addWidget(labelSumm);
    hor3->addWidget(linePay);
    hor3->addWidget(labelChange);
    vert->addLayout(hor3);

    setLayout(vert);

    connect(listSearsh, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(addToCheck()));
    connect(listCheck, SIGNAL(clicked(QModelIndex)), this, SLOT(setSpinQuantity()));
    connect(spinQuantity, SIGNAL(valueChanged(int)), this, SLOT(changeQuantity()));
    connect(lineBarcod, SIGNAL(returnPressed()), this, SLOT(barcodeScanned()));
    connect(linePay, SIGNAL(returnPressed()), this, SLOT(sold()));
    connect(linePay, SIGNAL(textChanged(QString)), this, SLOT(showChange()));
    connect(buttonDel, SIGNAL(clicked(bool)), this, SLOT(delFromCheck()));
    connect(listCheck, SIGNAL(clicked(QModelIndex)), this, SLOT(delEnable()));
    connect(buttonNext, SIGNAL(clicked(bool)), this, SLOT(nextPressed()));
    connect(listCheck, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(delFromCheck()));
    connect(checkBack, SIGNAL(clicked(bool)), this, SLOT(backClicked()));
    connect(timer, SIGNAL(timeout()),this, SLOT(colorLine()));
    connect(payTimer, SIGNAL(timeout()),this, SLOT(on_payTimerTimeout()));
    connect(timerFastFind, SIGNAL(timeout()),this, SLOT(on_timerFastFindTimeout()));
    connect(listSearsh, SIGNAL(clicked(QModelIndex)), lineBarcod, SLOT(setFocus()));
    connect(buttonDebt, SIGNAL(pressed()), this, SLOT(debt()));
    connect(timerActiveSeller, SIGNAL(timeout()), this, SLOT(resetActiveSeller()));
    connect(lineBarcod, SIGNAL(textChanged(QString)), this, SLOT(fastFind()));

    connect(keyF1, &QShortcut::activated, [=](){setActiveSeller(1);});
    connect(keyF2, &QShortcut::activated, [=](){setActiveSeller(2);});
    connect(keyF3, &QShortcut::activated, [=](){setActiveSeller(3);});


    getListSelect();
    lineBarcod->setFocus();
    setTabOrder(lineBarcod, linePay);

    timer->start(500);

    listSearsh->setWhatsThis("Это список товаров на складе\nего можно отсортировать. Для этого \nвведите запрос в зеленую строку и нажмите ENTER. Добавить товар в чек можно двойным щелчком мыши");
    lineBarcod->setWhatsThis("Это строка поиска товаров.\n В нее можно вводить штрихкод товара или название. Нажатие ENTER в пустой строке вызовет завершение операции и печать чека");
    checkBack->setWhatsThis("Это возврат товара. Ставим галочку, зеленая строка становиться красной, и считываем штрихкод товара. Товар попадает в чек со знаком '-'");
    buttonDebt->setWhatsThis("Это кнопка позволяет дать товар в долг постоянному клиенту. Для этого нужно просканировать карту клиента, сформировать чек и нажать эту кнопку. Сумма чека прибавится к долгу клиента");
    listCheck->setWhatsThis("Это список товаров в чеке. Удалить позицию из него можно двойным кликом мышки или кнопкой УДАЛИТЬ. Если чек полностью сформирован и клиент рассчитался без сдачи, просто нажмите ENTER");
    linePay->setWhatsThis("Сюда записываем сумму внесенную клиентом. Для быстрого доступа к этой строке нужно нажать TAB. После рассчета с клиентом нажимаем ENTER для завершения операции и печати чека");
    lineManInfo->setWhatsThis("Если просканирована карта клиента, тут появится информация о клиенте");

    setActiveSeller(activeSeller);
//    qDebug()<<Textbutor::checkSummGen("482000102549")<<" 1";
//    qDebug()<<Textbutor::checkSummGen("482000102554")<<" 5";
//    qDebug()<<Textbutor::checkSummGen("482000101000")<<" 8";
//    qDebug()<<Textbutor::checkSummGen("482000100210")<<" 2";
}


Seller::~Seller()
{
    timer->stop();
    delete timer;
}


void Seller::getListSelect()
{
    listSearsh->clear();
    QString word = lineBarcod->text();

    std::vector<Unit>base = Unit_loader::get()->base;
    size_t size = base.size();

    if (word.isEmpty())
    {
        for(size_t n=1; n<size; n++)
        {
            listSearsh->addItem(getListItem(base[n]));
        }
    }
    else
    {
        searsh(word);
        if(listSearsh->count() == 0)
        {
            searsh(Textbutor::latinToKiril(word));
        }
    listSearsh->scrollToTop();
    }
    lineBarcod->setFocus();
}


void Seller::sold()
{
    if(Textbutor::isBarcode(linePay->text()))
    {
        lineBarcod->setText(linePay->text());
        linePay->clear();
        this->barcodeScanned();
    }
    else if(!check.empty() && Textbutor::toDot(linePay->text()).toFloat() >= result())
    {
        writeOff();
        printCheck();

        man.setSumm(man.getSumm() + result());
        if (man.getName()!="no")humanloader.edit(man);

        Unit_loader::get()->addToLog(createLog());
        reset();
        Beep(800,100);
        //QApplication::beep();
    }
}


void Seller::showChange()
{
    float change = Textbutor::toDot(linePay->text()).toFloat() - (result());
    change = float(Unit_loader::get()->round(change*100.0f)/100);
    QString qchange;
    if(linePay->text().isEmpty() ||Textbutor::toDot(linePay->text()).toFloat() <= (result()))
    {
        qchange = "Сдача: --";
    }
    else
    {
        qchange = "Сдача: " + QString::number(change) + Ini::getInstance()->getNationalCurrency();
        this->changeHelp(change);
    }

    labelChange->setText(qchange);

}


void Seller::delFromCheck()
{
    if(check.size()>1)
    {
        int position = listCheck->currentRow();
        check.erase(check.begin()+position);
        quantity.erase(quantity.begin()+position);
    }
    else
    {
        check.clear();
        quantity.clear();
    }
    buttonDel->setEnabled(false);
    lineBarcod->setFocus();
    checkShow();
}


void Seller::delEnable()
{
    buttonDel->setEnabled(true);
    buttonDel->setAutoDefault(false);
    spinQuantity->setEnabled(true);
}


void Seller::humanTest(const QString& barcode)
{
    humanloader.loadBase();
    int code = barcode.midRef(6, 6).toInt();

    if(man.getTel().substr(0,1) == "!")
    {
        auto * edit = new HumanEdit(code, true, this);
        edit->show();
        edit->exec();
        humanloader.loadBase();
    }
    this->man = humanloader.getHuman(code);
    manShow();
    lineBarcod->setFocus();
    buttonDebt->setEnabled(true);
    buttonNext->setEnabled(true);
}


void Seller::manShow()
{
    if(this->man.getName() != "no")
    {
        QString qDiscount = QString::number(int(checkSumm*discount/100));
        QString manInfo = "Скидка:" + qDiscount + " "+Ini::getInstance()->getNationalCurrency()+"    " + QString::fromLocal8Bit((this->man.getName()).c_str())
        + "     Долг:" + QString::number(this->man.getDebt()) + " "+Ini::getInstance()->getNationalCurrency();
        lineManInfo->setText(manInfo);
    }
}


void Seller::nextPressed()
{
   reset();
}


void Seller::searsh(QString word)
{
    word = word.toLower();
    std::vector<QString>whatSearsh;
    QString add = "";
    for(int n=0; n<word.size(); n++)
    {
        if(word.midRef(n,1)!=" "){add+=word.midRef(n,1);}
        else
            if(add.size()>0)
            {
                whatSearsh.push_back(add);
                add = "";
            }
    }
    if(add.size()>0) whatSearsh.push_back(add);

    std::list<Unit>vBase = Unit_loader::get()->getBaseList();

    size_t size =  whatSearsh.size();
    for(size_t n = size; n-- > 0;)
    {
        std::list<Unit>::iterator it = vBase.begin();
        while(it != vBase.end())
        {
            size_t coincidence = 0;
            QString name = QString::fromLocal8Bit((it->getName()).c_str());
            for(size_t a=0; a<size; a++)
            {
                if(name.contains(whatSearsh[a], Qt::CaseInsensitive)){coincidence++;}
            }

            if (coincidence==(n+1))
            {
                listSearsh->addItem(getListItem(*it));
                it = vBase.erase(it);
            }else{
                it++;
            }
        }

    }

}


void Seller::printCheck()
{
    QDateTime dt = QDateTime::currentDateTime();
    QString dateTime = dt.toString();
    QString qResult = "--------------------------------\n";
    qResult += Ini::getInstance()->getStoreName();
    qResult += "\n";
    qResult += Ini::getInstance()->getStoreAddress();
    qResult += "\n";
    qResult += "--------------------------------\n";
    qResult +="\n\n--" + dateTime + "--" + "\n\n";
    unsigned size = check.size();
    for(unsigned n=0; n<size; n++)
    {
        qResult += listCheck->item(n)->text().leftRef(32);
        qResult +="= ";
        qResult +=listCheck->item(n)->text().midRef(40,6);
        qResult += "\n";
    }
    qResult += "--------------------------------\n";
    if (discount > 0) qResult +="Скидка: " + QString::number(Unit_loader::get()->round(checkSumm*discount/100))+"\n";
    qResult +=labelSumm->text() + "\n\n\n";
    qResult += "--------------------------------\n";
    qResult += "Касса: >>>> " + QString::number(activeSeller) + " <<<<\n";
    qResult +=Ini::getInstance()->getCheckText();
    qResult += "\n--------------------------------\n";

#ifndef QT_NO_PRINTER
    if(!QPrinterInfo::availablePrinterNames().empty() && !(Ini::getInstance()->getCheckPrinterName()=="---"))
    {
        QFont small("Lucida Console",6);
        QPrinter printer(QPrinter::HighResolution);
        printer.setPrinterName(Ini::getInstance()->getCheckPrinterName());
        printer.setPageMargins(QMarginsF(0,0,0,0));
        QPainter paint(&printer);
        paint.setPen(Qt::black);
        paint.setFont(small);
        paint.drawText(QRect(0, 0, 450, 900), Qt::AlignLeft, qResult);
    }
#endif
}


void Seller::backClicked()
{
    if(checkBack->isChecked())
    {
        this->lineBarcod->setPalette(red);
        this->lineBarcod->setFocus();
    }
    else
    {
        this->lineBarcod->setPalette(white);
        this->lineBarcod->setFocus();
    }
}


void Seller::colorLine()
{
    if(this->date != Unit_loader::get()->getDate())
    {Unit_loader::get()->makeReservCopy();
    humanloader.saveReserv();
    this->date = Unit_loader::get()->getDate();}

    lineBarcod->hasFocus() ? lineBarcod->setPalette(green): lineBarcod->setPalette(white);
    if (checkBack->isChecked()) lineBarcod->setPalette(red);

    if (listSearsh->hasFocus() || listCheck->hasFocus()) lineBarcod->setFocus();

    if(!lineBarcod->hasFocus() && !payTimer->isActive())payTimer->start(20000);
    if(lineBarcod->hasFocus() && payTimer->isActive())payTimer->stop();
}


void Seller::debt()
{
    if(checkSumm > 0)
    {
        writeOff();
        printCheck();

        man.setDebt(man.getDebt() + result() - Textbutor::toDot(linePay->text()).toFloat());
        man.setDescription(man.getDescription() + createLog());
        humanloader.edit(man);

        Unit_loader::get()->addToLog(createLog());
        reset();
        QApplication::beep();
    }
}


void Seller::checkShow()
{
    if(check.empty())
    {
        buttonDel->setEnabled(false);

        spinQuantity->setEnabled(false);
        listCheck->clear();
        checkSumm = 0;
        labelSumm->setText("К оплате: --");
        labelChange->setText("Сдача: --");
        //buttonNext->setEnabled(false);
    }
    else
    {
        buttonDel->setAutoDefault(false);
        findRepeat();
        listCheck->clear();
        checkSumm = 0;
        for(unsigned n=0; n<check.size(); n++)
        {
            //QString QCode = QString::number(check[n].getCode());
            QString QName = Textbutor::cutter(QString::fromLocal8Bit((check[n].getName()).c_str()), 20);
            QString QQuantity = Textbutor::cutter(QString::number(quantity[n]), 3);
            float price;
            if(check[n].isUah())
            {
                price = Unit_loader::get()->round(check[n].getPrice());
            }
            else
            {
                price = Unit_loader::get()->round(check[n].getPrice() * exchange);
            }
            QString QPrice = Textbutor::cutter(QString::number(price),10);
            QString QPriceXQuantity = QString::number(price * quantity[n]);

            QString toList = QName + "  " + QQuantity + "x " + QPrice + " = " + QPriceXQuantity;
            listCheck->addItem(toList);
            checkSumm += int(price * quantity[n]);
        }
        int checkResult = result();
        QString summ = "К оплате: " + QString::number(checkResult) + " "+Ini::getInstance()->getNationalCurrency();
        labelSumm->setText(summ);
        showChange();
        manShow();
        buttonNext->setEnabled(true);
        buttonNext->setAutoDefault(false);
        lineBarcod->setFocus();
    }
}


void Seller::findRepeat()
{
    Unit item = check[check.size()-1];
    for(unsigned n=0; n<(check.size()-1); n++)
    {
        if(item.getCode()==check[n].getCode())
        {
            checkBack->isChecked() ? quantity[n]-- : quantity[n]++;
            check.pop_back();
            quantity.pop_back();
        }
    }

}


std::string Seller::createLog()
{
    QDateTime dt = QDateTime::currentDateTime();

    QString dateTime = dt.toString();

    QString qResult ="--------------------" + dateTime + "--------------------" + QString::number(Unit_loader::get()->getBalance()) + "\n\n";
    unsigned size = check.size();
    for(unsigned n=0; n<size; n++)
    {
        qResult += listCheck->item(n)->text();
        qResult += "\n";
    }
    qResult += "----------------------------------------------------------------------\n";
    if (discount > 0) qResult +="Скидка = -" + QString::number(Unit_loader::get()->round(checkSumm*discount/100)) + "\n";
    qResult +=labelSumm->text();
    qResult +="\t Оплачено: " + linePay->text() + " " + Ini::getInstance()->getNationalCurrency();
    qResult +="\t" + labelChange->text() + "\n";
    qResult += "Касса: >>>>>>>>>>>>>> " + QString::number(activeSeller) + " <<<<<<<<<<<<<<\n\n\n";

    return qResult.toLocal8Bit().constData();
}


QString Seller::getQPrice(Unit unit)
{
    float price;
    if(unit.isUah())
    {
        price = Unit_loader::get()->round(unit.getPrice());
    }
    else
    {
        price = Unit_loader::get()->round(unit.getPrice() * exchange);
    }
    return QString::number(price);
}


void Seller::changeHelp(float change)
{
    int tail = int(change) - int(change/100)*100;
    if(tail >= 30 && tail < 50)
    {
        QString text = "Дайте " + QString::number(50 - tail) + " " + Ini::getInstance()->getNationalCurrency();
        this->lineManInfo->setText(text);
    }
    else if(tail >= 8 && tail < 10)
    {
        QString text = "Дайте " + QString::number(10 - tail) + " " + Ini::getInstance()->getNationalCurrency();
        this->lineManInfo->setText(text);
    }

}


void Seller::reset()
{
    check.clear();
    quantity.clear();
    listCheck->clear();
    labelSumm->setText("К оплате: --");
    linePay->clear();
    labelChange->setText("Сдача: --");
    getListSelect();
    lineBarcod->setFocus();
    this->discount = 0;
    labelDiscount->clear();
    labelDiscount->setAutoFillBackground(false);
    man.setName("no");
    lineManInfo->clear();
    buttonNext->setEnabled(false);
    checkSumm = 0;
    buttonDebt->setEnabled(false);
}


int Seller::result()
{
    return static_cast<int> (checkSumm - Unit_loader::get()->round(checkSumm*discount/100));
}


void Seller::writeOff()
{
    Unit_loader::get()->load();

    for(unsigned n=0; n<check.size(); n++)
    {
        unsigned position = Unit_loader::get()->getPosition(check[n].getCode());
        Unit_loader::get()->base[position].setQuantity(Unit_loader::get()->base[position].getQuantity() - quantity[n]);
        Unit_loader::get()->base[position].addSales(quantity[n]);

    }
    Unit_loader::get()->save();
}


void Seller::addToCheck()
{
    QString strCode = listSearsh->currentItem()->text();
    strCode = strCode.left(6);
    int code = strCode.toInt();
    Unit item = Unit_loader::get()->getUnit(un(code));
    check.push_back(item);
    !checkBack->isChecked()?quantity.push_back(1):quantity.push_back(-1);
    checkShow();
    checkBack->setChecked(false);
    this->backClicked();
    buttonDel->setEnabled(false);
    spinQuantity->setEnabled(false);
    lineBarcod->clear();
    Beep(1000,100);
}


void Seller::setSpinQuantity()
{
    int position = listCheck->currentRow();
    int quant = quantity[un(position)];
    spinQuantity->setValue(quant);
    listCheck->setCurrentRow(position);
}


void Seller::changeQuantity()
{
    int position = listCheck->currentRow();
    quantity[un(position)] = spinQuantity->value();
    checkShow();
    listCheck->setCurrentRow(position);
}


void Seller::barcodeScanned()
{
    Unit unit;
    QString barcode = lineBarcod->text();
    if(!Textbutor::isBarcode(barcode) && barcode != "")
    {
        this->getListSelect();
    }
    else if(barcode.left(6)=="575757")
    {
        humanTest(barcode);
        int code = barcode.midRef(6, 6).toInt();
        Human man = humanloader.getHuman(code);
        discount = man.getDiscount();
        QString disc = "  "  + QString::number(discount) + " %";
        labelDiscount->setAutoFillBackground(true);
        labelDiscount->setText(disc);
        qDebug()<<"discount = "<<discount;
    }
    else if(barcode=="")
    {
        if(linePay->text().toFloat()==0.0F) {
            linePay->setText(QString::number(checkSumm));
        }
        sold();
    }
    else
    {
        unit = Unit_loader::get()->getUnit(barcode.toLocal8Bit().constData());
        check.push_back(unit);


        !checkBack->isChecked()?quantity.push_back(1):quantity.push_back(-1);
        this->backClicked();
        if(unit.getBarcode()=="0000000000000"){
            Beep(2000,400);
        }else{
            Beep(1000,100);
            if(int(Unit_loader::get()->base.size()-1) > listSearsh->count()){
                        lineBarcod->clear();
                        getListSelect();
                    }
                    int position = int(Unit_loader::get()->getPosition(unit.getCode())) - 1;
                    listSearsh->scrollToTop();
                    listSearsh->scrollToItem(listSearsh->item(position + 6));
                    listSearsh->item(position)->setTextColor(Qt::red);


        }


    }
    lineBarcod->clear();
    checkShow();
    checkBack->setChecked(false);
    lineBarcod->setFocus();
}


void Seller::setActiveSeller(int activeSeller)
{
    if(activeSeller==1) lblHead->setStyleSheet("background: #33CC33");
    if(activeSeller==2) lblHead->setStyleSheet("background: #FF6633");
    if(activeSeller==3) lblHead->setStyleSheet("background: #3366CC");
    this->activeSeller = activeSeller;
    if(activeSeller != 1) timerActiveSeller->start(600000);
    QString newTitle = this->windowTitle().left(8) +" - Касса №" + QString::number(activeSeller);
    this->setWindowTitle(newTitle);
}

void Seller::resetActiveSeller()
{
    if(activeSeller != 1 && check.empty()){
        timerActiveSeller->stop();
        setActiveSeller(1);
    }
}


void Seller::fastFind()
{
    if(!lineBarcod->text().contains(QRegExp("[0-9]{7,14}")) && !lineBarcod->text().isEmpty()){
        getListSelect();
        timerFastFind->start(5000);
        //qDebug()<<"FastFind-"<<lineBarcod->text();
    }
}


void Seller::on_payTimerTimeout()
{
    lineBarcod->setFocus();

}


void Seller::on_timerFastFindTimeout()
{
    lineBarcod->clear();
}


void Seller::reject() {
    if(check.empty()) {
        done(0);
    }else{
        this->nextPressed();
    }
}

QString Seller::getListItem(Unit &unit)
{
    QString code = QString::number(unit.getCode());
    QString name = Textbutor::cutter(QString::fromLocal8Bit((unit.getName()).c_str()),30);
    QString price = Textbutor::cutter(getQPrice(unit),9);
    QString quantity = QString::number(unit.getQuantity());
    return code+"   "+name+"  "+price+" "+quantity;
}
