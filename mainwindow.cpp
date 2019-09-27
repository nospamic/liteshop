#include "mainwindow.h"
#include "ui_mainwindow.h"




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->isQueue = new bool;
    *isQueue = false;
    this->state = "normal";
    ui->setupUi(this);
    this->setWindowTitle("Склад");
    QFont font("Lucida Console",10);
    this->setFont(font);

    timerSeller = new QTimer();
    wait = 160000;
    timerSeller->start(wait);


    if(!Unit_loader::get()->fileExists())Unit_loader::get()->newFile();


    //------------------------------------------------------------------

    //QString s = QString::number(i);
    // QString name=QString::fromLocal8Bit((str).c_str());
    //float price = linePrice->text().toFloat();
    //std::string word = ui->lineSelect->text().toLocal8Bit().constData();
    //-----------------------------------------------------------------

    getListSelect();
    //if(Unit_loader::get()->base.size()>10) Unit_loader::get()->makeReservCopy();
    this->date = Unit_loader::get()->getDate();
    ui->print->hide();
    ui->pushEdit->setEnabled(false);
    getGroups();
    setGroupsVisible(false);

    connect (ui->list, SIGNAL(itemSelectionChanged()), this, SLOT(setEditable()));
    connect (timerSeller, SIGNAL(timeout()), this, SLOT(on_buttonSaller_clicked()));
    connect (ui->lineSelect, SIGNAL(textChanged(QString)), this, SLOT(getListSelect()));
    //connect (ui->lineSelect, SIGNAL(returnPressed()), this, SLOT(showOrderVal()));
    for(auto check : groups) connect(check, SIGNAL(clicked(bool)), this, SLOT(getListSelect()));

//    for(auto unit : Unit_loader::get()->base){
//        QString bar = QString::fromLocal8Bit((unit.getBarcode()).c_str());
//        if (bar!=Textbutor::testBarcode13(bar)){
//            qDebug()<<unit.getCode()<<" "<<bar<<" "<<Textbutor::testBarcode13(bar);
//        }
//    }

}

MainWindow::~MainWindow()
{
    delete isQueue;
    delete ui;
}


void MainWindow::on_list_doubleClicked()
{
    on_pushEdit_clicked();
}


void MainWindow::on_pushAdd2_clicked()
{
    timerSeller->stop();

    Add2 unit(this);
    unit.show();
    unit.exec();
    Unit_loader::get()->load();
    this->getListSelect();
    ui->pushEdit->setEnabled(false);
    ui->list->scrollToBottom();

}


void MainWindow::setEditable()
{
    ui->pushEdit->setEnabled(true);
    ui->del->setEnabled(true);
    timerSeller->stop();
    timerSeller->start(wait);
}


void MainWindow::on_pushEdit_clicked()
{
    int pos = ui->list->currentRow();
    timerSeller->stop();
    QString str = ui->list->currentItem()->text().left(6);
    un code = unsigned(str.toInt());
    Unit_edit unit(code, this);
    unit.show();
    unit.exec();
    Unit_loader::get()->load();
    this->getListSelect();
    ui->pushEdit->setEnabled(false);
    ui->list->scrollToItem(ui->list->item(pos));
    if(pos>9)ui->list->scrollToItem(ui->list->item(pos-9));
    ui->list->setCurrentRow(pos);
}


void MainWindow::on_lineSelect_editingFinished(){}


void MainWindow::on_lineSelect_returnPressed()
{
    this->state = "searsh";
    getListSelect();
}


void MainWindow::on_buttonSaller_clicked()
{
    if(this->isActiveWindow())
    {
        timerSeller->stop();
        Seller  shop;
        shop.show();
        shop.exec();
    }
}


void MainWindow::getListSelect()
{
    timerSeller->stop();
    timerSeller->start(wait);

    ui->list->clear();
    QString word = ui->lineSelect->text();

    std::vector<Unit>base = Unit_loader::get()->base;
    unsigned size = un(base.size());

    if (textbutor.isBarcode(word))
    {
        this->state = "searsh";
        QString text = "Поиск по штрих-коду: " + word;
        ui->labelContent->setText(text);
        ui->buttonRefresh->setEnabled(true);
        for(un n=0; n<size; n++)
        {
            QString barcode = QString::fromLocal8Bit((base[n].getBarcode()).c_str());
            if(word == barcode)ui->list->addItem(getListItem(base[n]));
        }
    }

    if (word.isEmpty() && state == "normal")
    {
        ui->labelContent->setText("Все товары на складе.");
        ui->buttonRefresh->setEnabled(false);
        for(un n=0; n < size; n++)
        {
            ui->list->addItem(getListItem(base[n]));
        }
        ui->list->scrollToBottom();
    }

    if (!word.isEmpty() && !textbutor.isBarcode(word))
    {
        this->state = "searsh";
        QString text = "Результаты поиска: " + word;
        ui->labelContent->setText(text);
        ui->buttonRefresh->setEnabled(true);
        searsh(word);
        if(ui->list->count() == 0)
        {
            //qDebug()<<"change";
            ui->lineSelect->setText(textbutor.latinToKiril(word));
            searsh(textbutor.latinToKiril(word));
        }
        ui->list->scrollToTop();
    }

    if(this->state == "order")
    {
        Unit_loader::get()->sortBaseByGroup(base);
        for(un n=1; n<size; n++)
        {
            un minimum = base[n].getMinimum();
            int quantityInt = (base[n].getQuantity());
            if (quantityInt < int(minimum) && isGroupChecked(base[n]))
            {
                ui->list->addItem(getListItem(base[n]));
            }
        }
        ui->list->scrollToTop();
    }
    ui->pushEdit->setEnabled(false);
    ui->del->setEnabled(false);
    this->state == "order" && ui->list->count()>0?ui->print->setHidden(false):ui->print->setHidden(true);
    showOrderVal();

}



void MainWindow::on_del_clicked()
{
    int pos = ui->list->currentRow();
    if(!ui->list->currentItem()->text().isEmpty())
    {
        unsigned code = ui->list->currentItem()->text().left(6).toInt();
        Unit unit = Unit_loader::get()->getUnit(code);
        QString msg;
        msg = "Удалить " + QString::fromLocal8Bit((unit.getName()).c_str()) + "?";
        QMessageBox msgBox;
        msgBox.setWindowTitle("Удаление товара");
        msgBox.setText(msg);
        msgBox.setStandardButtons(QMessageBox::Yes);
        msgBox.addButton(QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::No);
        if(msgBox.exec() == QMessageBox::Yes)
        {
            Unit_loader::get()->del(code);
            getListSelect();
        }
    }
    ui->list->scrollToItem(ui->list->item(pos));
    if(pos>9)ui->list->scrollToItem(ui->list->item(pos-9));
    ui->list->setCurrentRow(pos);
}


void MainWindow::on_buttonOrder_clicked()
{
    showOrderVal();
    ui->lineSelect->clear();
    this->state = "order";
    ui->list->clear();
    ui->labelContent->setText("Заказать товары...");
    ui->buttonRefresh->setEnabled(true);
    setGroupsVisible(true);

    getListSelect();
    ui->pushEdit->setEnabled(false);
    ui->del->setEnabled(false);

}


void MainWindow::on_buttonRefresh_clicked()
{
    this->state = "normal";
    ui->lineSelect->clear();
    setGroupsVisible(false);
    getListSelect();
}


void MainWindow::on_buttonCustomers_clicked()
{
    timerSeller->stop();
    Customers box(this);
    box.show();
    box.exec();
}


void MainWindow::searsh(QString word)
{
    word = word.toLower();
    std::vector<QString>whatSearsh;
    QString add = "";
    for(int n=0; n<word.size(); n++)
    {
        if(word.mid(n,1)!=" "){add+=word.mid(n,1);}
        else
            if(add.size()>0)
            {
                whatSearsh.push_back(add);
                add = "";
            }
    }
    if(add.size()>0) whatSearsh.push_back(add);

    std::list<Unit>vBase = Unit_loader::get()->getBaseList();
    size_t size = whatSearsh.size();

    for(size_t n = size; n-- >0;)
    {
        std::list<Unit>::iterator it = vBase.begin();
        while(it != vBase.end())
        {
            size_t coincidence = 0;
            QString name = QString::fromLocal8Bit(((*it).getName()).c_str());
            for(size_t a=0; a<size; a++)
            {
                if(name.contains(whatSearsh[a], Qt::CaseInsensitive)){coincidence++;}
            }

            if (coincidence==(n+1)){
                ui->list->addItem(getListItem(*it));
                it = vBase.erase(it);
            }else{
            it++;
            }
        }

    }
}



void MainWindow::on_statistica_clicked()
{
    ui->list->clear();
    this->state = "statistica";
    ui->labelContent->setText("Статистика");
    ui->buttonRefresh->setEnabled(true);

    QStringList files = Unit_loader::get()->getFiles("LOG");
    un length = un(files.length());
    for(un n = 0; n < length; n++)
    {
        QString info = files[int(n)];
        if (info.right(3)=="log")
        {
            float balance = Unit_loader::get()->daySummFromLog(info);
            info = info.mid(4, info.size());
            info.chop(4);
            info = textbutor.cutter(info, 12)+ QString::number(double(balance)) + " грн.";
            ui->list->addItem(info);
        }
    }
    ui->list->scrollToTop();
}


void MainWindow::on_buttonOptions_clicked()
{
    timerSeller->stop();
    Options options(this);
    options.show();
    options.exec();
}


void MainWindow::on_buttonRecive_clicked()
{
    timerSeller->stop();
    Recive  recive(this);
    recive.show();
    recive.exec();
    Unit_loader::get()->load();
    this->state = "normal";
    ui->lineSelect->clear();
    getListSelect();
}


void MainWindow::on_print_clicked()
{
    QString qResult = "\n\n";
    for (int n = 0; n < ui->list->count(); ++n)
    {
        QListWidgetItem* item = ui->list->item(n);
        qResult+=item->text().mid(9,33);
        qResult+=item->text().mid(60 , 5);
        qResult+="\n";
    }
#ifndef QT_NO_PRINTER
    if(QPrinterInfo::availablePrinterNames().size() > 0)
    {
        QFont small("Lucida Console",6);
        QPrinter printer(QPrinter::HighResolution);
        printer.setPrinterName(Ini::getInstance()->getCheckPrinterName());
        printer.setPageMargins(QMarginsF(0,0,0,0));
        QPainter paint(&printer);
        paint.setPen(Qt::black);
        paint.setFont(small);
        paint.drawText(QRect(0, 0, 500, 8000), Qt::AlignLeft, qResult);
        QThread::sleep(2);
    }
#endif
    //std::cout<<qResult.toLocal8Bit().constData();
}

void MainWindow::showOrderVal()
{
    un value = 0;
    std::vector<Unit>base = Unit_loader::get()->base;
    unsigned size = un(base.size());
    for(un n=1; n<size; n++)
    {
        un minimum = base[n].getMinimum();
        un quantityInt = unsigned(base[n].getQuantity());
        if (quantityInt < minimum)
        {
            value++;
        }
    }
    ui->buttonOrder->setText(ui->buttonOrder->text().left(8));
    QString text = ui->buttonOrder->text() + " (" + QString::number(value) + ")";
    ui->buttonOrder->setText(text);
}

void MainWindow::getGroups()
{
    for(auto str : Unit_loader::get()->getGroups()){
        QCheckBox * check = new QCheckBox(str);
        check->setChecked(true);
        groups.push_back(check);
    }
    for(auto check : groups)ui->horizontalLayout_2->addWidget(check);
}


void MainWindow::setGroupsVisible(bool isVisible)
{
    for(auto check : groups)check->setVisible(isVisible);
}


bool MainWindow::isGroupChecked(Unit  &unit)
{
    bool result = false;
    for(auto check : groups){
        if(unit.getGroup() == "No group"){
            result = true;
            break;
        }
        if (check->isChecked() && QString::fromLocal8Bit((unit.getGroup()).c_str()) == check->text()){
            result = true;
            break;
        }
    }
    return result;
}



QString MainWindow::getListItem( Unit &unit)
{
    QString code = QString::number(unit.getCode());
    QString name = textbutor.cutter(QString::fromLocal8Bit((unit.getName()).c_str()),40);
    QString price = textbutor.cutter(QString::number(unit.getPrice()),10);
    if(unit.isUah()) {price = "# " + price;} else {price = "$ " + price;}
    QString quantity = textbutor.cutter(QString::number(unit.getQuantity()),4)+"шт.";
    return code+"   "+name+"  "+price+" "+quantity;
}
