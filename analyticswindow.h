#ifndef ANALYTICSWINDOW_H
#define ANALYTICSWINDOW_H

#include <QWidget>
#include <QSortFilterProxyModel>>
#include <QChartView>

namespace Ui {
class AnalyticsWindow;
}

class AnalyticsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AnalyticsWindow(QWidget *parent = nullptr);

    AnalyticsWindow(QWidget *parent,QSortFilterProxyModel* derived);

    ~AnalyticsWindow();

    void constructPie(const int& index);

    void constructBar(const int& index);

    void constructSpline(const int& index);

    void constructScatter(const int& index);

    void constrBar2();

private:
    Ui::AnalyticsWindow* uiAn;
    QSortFilterProxyModel* _derivedMain;
    int _pieSelectedCol = 0;
    int _chosenChart = 0;
    int _xColumn = 0;
    int _yColumn = 0;
    QChartView* chartView1;
    QChartView* chartView2;
signals:
    void callBack();
private slots:
    void on_returnButton_clicked();
    void on_chooseChart_activated(int index);
    void on_chooseColumn_activated(int index);
    void on_chooseChart_2_activated(int index);
};

#endif // ANALYTICSWINDOW_H
