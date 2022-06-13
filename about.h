#ifndef ABOUT_H
#define ABOUT_H
#include <QWidget>
#include <logo.h>

#include <QDialog>

namespace Ui {
class ABOUT;
}

class ABOUT : public QDialog
{
    Q_OBJECT

public:
    explicit ABOUT(QWidget *parent = nullptr);
    ~ABOUT();
    void customiseUi();

private:
    Ui::ABOUT *ui;
    logo* _logo;
signals:
    void callBack();
private slots:
    void on_returnButon_clicked();
};

#endif // ABOUT_H
