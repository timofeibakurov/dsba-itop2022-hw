#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <fstream>
#include <storage.h>
#include <QSortFilterProxyModel>
#include <analyticswindow.h>
#include <about.h>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:

    //void on_addRowButton_clicked();

    void showTable();

    void on_deleteRowButton_clicked();

    void on_actionOpen_2_triggered();

    void on_addRowButton_clicked();

    void on_saveRowButtom_clicked();

    void on_actionSave_triggered();

    void on_analyticPage_clicked();

    void on_aboutButton_clicked();

protected:
    Ui::MainWindow *ui;
    QStandardItemModel *_mainTableModel;
    Storage *_storage;
    QSortFilterProxyModel *_proxyModel;
    AnalyticsWindow* _anWindow;
    ABOUT* _abWindow;

};
#endif // MAINWINDOW_H
