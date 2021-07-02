#ifndef LOGOAREA_H
#define LOGOAREA_H

#include <QWidget>

class LogoArea : public QWidget
{
    Q_OBJECT

public:
    explicit LogoArea(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

signals:

};

#endif // LOGOAREA_H


