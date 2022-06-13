#include "about.h"
#include "ui_about.h"

ABOUT::ABOUT(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ABOUT)
{
    ui->setupUi(this);
    customiseUi();
}

ABOUT::~ABOUT()
{
    delete ui;
}

void ABOUT::customiseUi()
{
    _logo = new logo(this);
    ui->gridLayout_3->addWidget(_logo);
}

void ABOUT::on_returnButon_clicked()
{
    emit callBack();
    hide();
}

