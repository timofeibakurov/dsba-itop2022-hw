#ifndef LOGO_H
#define LOGO_H


#include <QWidget>

class logo : public QWidget
{
    Q_OBJECT
public:
    explicit logo(QWidget *parent = nullptr);
protected:
    void paintEvent(QPaintEvent *event) override;
signals:

};

#endif // LOGO_H
