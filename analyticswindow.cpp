#include "analyticswindow.h"
#include "ui_analyticswindow.h"
#include "QtCharts/QtCharts"
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <map>
#include <QMessageBox>
#include <QtCharts>
#include <QPieSeries>

AnalyticsWindow::AnalyticsWindow(QWidget *parent) :
    QWidget(parent),
    uiAn(new Ui::AnalyticsWindow)
{
    uiAn->setupUi(this);
}

AnalyticsWindow::AnalyticsWindow(QWidget* parent,QSortFilterProxyModel* derived) :
    QWidget(parent),
    uiAn(new Ui::AnalyticsWindow),
    _derivedMain(derived)
{
    uiAn->setupUi(this);
    chartView1 = new QChartView(this);
    //chartView1->resize(100,100);
    uiAn->chartLayOut_1->addWidget(chartView1);

    uiAn->chooseColumn->setEnabled(false);
}

AnalyticsWindow::~AnalyticsWindow()
{
    delete uiAn;
}

void AnalyticsWindow::constructPie(const int& index)
{
    uiAn->chartLayOut_1->removeWidget(chartView1);
    delete chartView1;
    std::map<std::string,int> values;
    for (int i = 0; i!=_derivedMain->rowCount();++i)
    {
        QModelIndex ind = _derivedMain->index(i,index + 1);
        QVariant var = _derivedMain->data(ind);
        if (!var.isValid())
            continue;
        std::string val = var.toString().toStdString();
        if (values.find(val) == values.end())
            values[val] = 0;
        int value = values.at(val);
        ++value;
        values[val] = value;
    }

    QPieSeries *series = new QPieSeries();
    for (std::map<std::string,int>::iterator it = values.begin(); it != values.end(); ++it)
    {
        std::string key = it->first;
        double value = it->second;
        double percentage = round((value / _derivedMain->rowCount())*100);
        *series << new QPieSlice(QVariant(percentage).toString() + "%", qreal(value));
        //series->setName(QVariant(percentage).toString() + "%");
    }
    series->setLabelsVisible();

    QChart *chart = new QChart();
    chart->setTitle(uiAn->chooseColumn->itemText(index) + " pie chart");
    chart->addSeries(series);
    chart->setAnimationOptions(QChart::AllAnimations);


    QChartView* chartView = new QChartView(chart);

    chartView1 = chartView;
    chartView1->setRenderHint(QPainter::Antialiasing);
    uiAn->chartLayOut_1->addWidget(chartView1);
}

void AnalyticsWindow::constructBar(const int &index)
{
    uiAn->chartLayOut_1->removeWidget(chartView1);
    delete chartView1;
    std::map<std::string,int> values;
    for (int i = 0; i!=_derivedMain->rowCount();++i)
    {
        QModelIndex ind = _derivedMain->index(i,index + 1);
        QVariant var = _derivedMain->data(ind);
        if (!var.isValid())
            continue;
        std::string val = var.toString().toStdString();
        if (values.find(val) == values.end())
        {
            values[val] = 0;
        }
        int value = values.at(val);
        ++value;
        values[val] = value;
    }
    QBarSeries* series = new QBarSeries();
    int max = 0;
    int min = 10000000;
    for(std::map<std::string,int>::iterator it = values.begin(); it != values.end(); ++it)
    {
        std::string key = it->first;
        int value = it->second;
        if (value > max);
            max = value;
        if (value < min);
            min = value;
        QBarSet* barSet = new QBarSet(key.c_str());
        *barSet << value;
        series->append(barSet);
    }

    QChart *chart = new QChart();
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setTitle(uiAn->chooseColumn->itemText(index) + " bar chart");
    chart->createDefaultAxes();
    chart->addSeries(series);

    QStringList categories;
    categories << uiAn->chooseColumn->itemText(index);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(min,max);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    QChartView* chartView = new QChartView(chart);

    chartView1 = chartView;
    chartView1->setRenderHint(QPainter::Antialiasing);
    uiAn->chartLayOut_1->addWidget(chartView1);
}

void AnalyticsWindow::constructSpline(const int &index)
{
    QSplineSeries *series = new QSplineSeries();
    uiAn->chartLayOut_1->removeWidget(chartView1);
    delete chartView1;
    std::map<std::string,int> values;
    int k = _derivedMain->rowCount();
    int max = 0;
    int min = 10000000;
    for (int i = 0; i<=_derivedMain->rowCount();i += 300)
    {
        QModelIndex ind = _derivedMain->index(i,index + 1);
        QVariant var = _derivedMain->data(ind);
        if (!var.isValid() || !var.canConvert<double>())
            continue;
        double v = var.toDouble();
        if (v > max)
            max = v;
        if (v < min)
            min = v;
        *series << QPoint(i,var.toDouble());
        series->setName(uiAn->chooseColumn->itemText(index));
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QValueAxis *axisX = new QValueAxis();
    axisX->setRange(0,_derivedMain->rowCount());
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(min,max+1);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    QChartView* chartView = new QChartView(chart);

    chartView1 = chartView;
    chart->setTitle(uiAn->chooseColumn->itemText(index) + " spline chart");
    chartView1->setRenderHint(QPainter::Antialiasing);
    uiAn->chartLayOut_1->addWidget(chartView1);
}

void AnalyticsWindow::constructScatter(const int &index)
{
    QScatterSeries *series = new QScatterSeries();
    uiAn->chartLayOut_1->removeWidget(chartView1);
    delete chartView1;
    std::map<std::string,int> values;
    int k = _derivedMain->rowCount();
    int max = 0;
    int min = 10000000;
    for (int i = 0; i<=_derivedMain->rowCount();i += 300)
    {
        QModelIndex ind = _derivedMain->index(i,index + 1);
        QVariant var = _derivedMain->data(ind);
        if (!var.isValid() || !var.canConvert<double>())
            continue;
        double v = var.toDouble();
        if (v > max)
            max = v;
        if (v < min)
            min = v;
        *series << QPoint(i,var.toDouble());
        series->setName(uiAn->chooseColumn->itemText(index));
    }

    QChart *chart = new QChart();
    chart->setTitle(uiAn->chooseColumn->itemText(index) + " scatter plot");
    chart->addSeries(series);
    chart->setAnimationOptions(QChart::SeriesAnimations);
    //chart->createDefaultAxes();
    //chart->resize(QSizeF(10,10));

    QValueAxis *axisX = new QValueAxis();
    axisX->setRange(0,_derivedMain->rowCount());
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(min,max+1);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    QChartView* chartView = new QChartView(chart);

    chartView1 = chartView;
    chartView1->setRenderHint(QPainter::Antialiasing);
    uiAn->chartLayOut_1->addWidget(chartView1);
}

void AnalyticsWindow::constrBar2()
{

}

void AnalyticsWindow::on_returnButton_clicked()
{
    emit callBack();
    hide();
}


void AnalyticsWindow::on_chooseChart_activated(int index)
{
    uiAn->chooseColumn->setEnabled(true);
    _chosenChart = index;
    if (index == 0)
        constructPie(_pieSelectedCol);
    else if (index == 1)
        constructBar(_pieSelectedCol);
    else if (index == 2)
    {
        if (_pieSelectedCol != 0 && _pieSelectedCol != 1 && _pieSelectedCol != 6
            && _pieSelectedCol != 7)
            constructScatter(_pieSelectedCol);
        else
        {
            QMessageBox att;
            att.setText("It is impossible to constuct scatter plor for "
                        "columns containing non-digital values");
            att.exec();
        }
    }
    else if (index == 3)
    {
        if (_pieSelectedCol != 0 && _pieSelectedCol != 1 && _pieSelectedCol != 6
            && _pieSelectedCol != 7)
            constructSpline(_pieSelectedCol);
        else
            QMessageBox::information(this,"Attention","It is impossible to constuct line chart for "
                                                      "columns containing non-digital values");
    }
}


void AnalyticsWindow::on_chooseColumn_activated(int index)
{
    _pieSelectedCol = index;
    if (_chosenChart == 0)
        constructPie(_pieSelectedCol);
    else if (_chosenChart == 1)
        constructBar(_pieSelectedCol);
    else if (_chosenChart == 2)
        constructScatter(_pieSelectedCol);
    else if(_chosenChart == 3)
        constructSpline(_pieSelectedCol);
}


void AnalyticsWindow::on_chooseChart_2_activated(int index)
{
    uiAn->chooseColumn->setEnabled(false);
    if (index == 1)
        constrBar2();
}

