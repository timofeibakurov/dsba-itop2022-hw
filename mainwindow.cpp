#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <storage.h>
#include <QTableView>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _mainTableModel = new QStandardItemModel(this);
    ui->tableView->setModel(_mainTableModel);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);


    _storage = new Storage(this);
    _proxyModel = new QSortFilterProxyModel(this);
    _proxyModel->setSourceModel(_mainTableModel);
    ui->treeView->setModel(_proxyModel);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete _mainTableModel;
}

void MainWindow::on_deleteRowButton_clicked()
{
    QModelIndex ind = ui->tableView->currentIndex();
    _storage->getModel()->removeRows(ind.row(),1);
    _mainTableModel->removeRows(ind.row(),1);
    ui->tableView->setModel(_mainTableModel);
}



void MainWindow::showTable()
{
    QStringListModel *qSTLModel = _storage->getModel();
    QStandardItemModel *qSIModel = new QStandardItemModel(qSTLModel->rowCount()-1, 12);

    QModelIndex lineIndex = qSTLModel->index(0);
    QString line = (qSTLModel->data(lineIndex)).toString();
    QStringList labels = line.split(',');
    QString label;


    _storage->setLabels(labels);
    for (int it = 0; it < labels.count(); ++it)
    {
        label = (labels.at(it));
        std::string lad = label.toStdString();
        qSIModel->setHeaderData(it,Qt::Horizontal,label);
    }



    for (int jt = 0;jt < qSTLModel->rowCount()-1;++jt)
        {
            lineIndex = qSTLModel->index(jt+1);
            line = (qSTLModel->data(lineIndex)).toString();
            QStringList items = line.split(',');
            for (int wt = 0; wt < items.count(); ++wt)
            {
                QVariant word = (items.at(wt));
                if (wt == 0)
                    word = word.toInt();
                QModelIndex wordIndex = qSIModel->index(jt,wt);
                //ui->mainTab->setCurrentIndex(wordIndex);
                qSIModel->setData(wordIndex,word);
                //_storage->addItemToModel(wordIndex,word);
            }

        }

        _mainTableModel = qSIModel;
        _proxyModel->setSourceModel(qSIModel);
        ui->tableView->setModel(_mainTableModel);
        ui->treeView->setModel(_proxyModel);
        ui->treeView->setSortingEnabled(true);
        ui->treeView->sortByColumn(0, Qt::AscendingOrder);

}


void MainWindow::on_actionOpen_2_triggered()
{
    QString fileName = "D:/learn/BigHW/train.csv";

    // checks whather a user has chosen a real file
    if (fileName.isNull())      // if the returned string is null, the user didn't choose a file
        return;

    //int a = 0;
    // So, now we are ready to read data from a storage (the given file).
    // We create a special helper object (in the constructer) helping us to do that
    _storage->loadFile(fileName);
    showTable();
}




void MainWindow::on_addRowButton_clicked()
{
    QStandardItem *item = new QStandardItem(1,_storage->getModel()->rowCount());
    _mainTableModel->insertRow(_mainTableModel->rowCount(),_mainTableModel->index(_mainTableModel->rowCount(),0));
}


void MainWindow::on_saveRowButtom_clicked()
{
    QStringList store;
    for(int wt = 1; wt != _mainTableModel->rowCount(); ++wt)
    {
        std::string str;
        for (int jt = 0; jt != _mainTableModel->columnCount(); ++jt)
        {
            QModelIndex itemIndex = _mainTableModel->index(wt,jt);
            std::string item1 = (_mainTableModel->data(itemIndex)).toString().toStdString();
            ui->tableView->setCurrentIndex(itemIndex);
            if (jt == _mainTableModel->columnCount()-1)

                str += item1;

            else
                str += item1 +',';
            QString item = QString::fromStdString(item1);
        }
        store << QString::fromStdString(str);
    }
    _storage->getModel()->setStringList(store);
}


void MainWindow::on_actionSave_triggered()
{
    if (this->_storage->getVal())
    {
        QFile DB("D:/learn/BigHW/train.csv");
        DB.open(QIODevice::WriteOnly | QIODevice::Truncate);
        QTextStream fStream(&DB);
        QString str;
        QStringList labels = _storage->getLabels();
        std::string listOfLabels;
        for(int it = 0; it != labels.count(); ++it)
        {
            std::string label = labels.at(it).toStdString();
            if (it == labels.count()-1)
            {
                listOfLabels = listOfLabels + label + '\n';
                break;
            }
            listOfLabels += label + ',';
        }
        DB.write(listOfLabels.c_str());
        for(int it = 0; it != _mainTableModel->rowCount(); ++it)
        {
            std::string str;
            for (int jt = 0; jt != _mainTableModel->columnCount(); ++jt)
            {
                QModelIndex wordIndex = _mainTableModel->index(it,jt);
                std::string word = (_mainTableModel->data(wordIndex)).toString().toStdString();
                if (jt == _mainTableModel->columnCount()-1)
                {
                    str = str + word + '\n';
                    break;
                }
                str = str + word + ',';
            }
            DB.write(str.c_str());
        }
        DB.close();
    }
}


void MainWindow::on_analyticPage_clicked()
{
    _anWindow = new AnalyticsWindow(nullptr,_proxyModel);
    connect(_anWindow, &AnalyticsWindow::callBack, this, &MainWindow::show);
    _anWindow->show();
    hide();
}


void MainWindow::on_aboutButton_clicked()
{
     _abWindow = new ABOUT(nullptr);
    connect(_abWindow, &ABOUT::callBack, this, &MainWindow::show);
    _abWindow->show();
    hide();
}

