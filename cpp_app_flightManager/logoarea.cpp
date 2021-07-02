#include "logoarea.h"

#include <QPainter>

LogoArea::LogoArea(QWidget *parent) :
    QWidget(parent)
{

}

void LogoArea::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    QColor color2(255, 255, 255);
    QColor color1(0, 191, 255);

    painter.setBrush(color1);
    painter.drawRect(0, 0, width()-1, height()-1);

    painter.setBrush(color2);

    painter.drawEllipse(170, 75, 88, 88);
    painter.drawEllipse(120, 100, 60, 60);
    painter.drawEllipse(240, 100, 60, 60);
    painter.drawEllipse(400, 100, 60, 60);
    painter.drawEllipse(350, 80, 80, 87);
    painter.drawEllipse(290, 50, 95, 100);
    painter.drawEllipse(250, 20, 90, 90);
    painter.drawEllipse(200, 70, 80, 80);

    painter.drawEllipse(285, 130, 35, 35);
}


