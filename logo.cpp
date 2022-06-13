#include "logo.h"
#include <QPainter>

logo::logo(QWidget *parent)
    : QWidget{parent}
{

}

void logo::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing, true);
    QBrush backGr(Qt::GlobalColor::magenta);
    painter.setBrush(backGr);
    painter.drawRect(QRect(0, 0, width() - 1, height() - 1));
    QBrush figBrush(Qt::GlobalColor::green);
    painter.setBrush(figBrush);
    QPen pen(Qt::blue, 3, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin);
    painter.setPen(pen);
    painter.drawRect(380, 300, width()-1050 , height()-250 );
    QPen pencil(Qt::red, 3, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin);
    painter.setPen(pencil);
    painter.drawRect(3, 3, width()- 250 , height()-500 );
}

