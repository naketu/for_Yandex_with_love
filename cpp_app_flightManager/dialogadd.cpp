#include "dialogadd.h"
#include "ui_dialogadd.h"

DialogAdd::DialogAdd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAdd)
{
    ui->setupUi(this);
    MyModel *flightModel;
}

void DialogAdd::addButtonClicked()
{
    flight.append(ui->lineEdit->text());
    flight.append(ui->lineEdit_2->text());
    flight.append(ui->lineEdit_3->text());
    flight.append(ui->lineEdit_4->text());
    flight.append(ui->lineEdit_5->text());
    flight.append(ui->lineEdit_6->text());
    flight.append(ui->lineEdit_7->text());
    flight.append(ui->lineEdit_8->text());
    flight.append(ui->lineEdit_9->text());
    flight.append(ui->lineEdit_10->text());
}

QList<QVariant> DialogAdd::getFlight()
{
    return flight;
}

DialogAdd::~DialogAdd()
{
    delete ui;
}
