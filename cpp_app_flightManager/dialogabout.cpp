#include "dialogabout.h"
#include "ui_dialogabout.h"

DialogAbout::DialogAbout(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAbout)
{
    ui->setupUi(this);

    logoArea = new LogoArea(ui->frame);
    ui->gridLayout->addWidget(logoArea);
}

DialogAbout::~DialogAbout()
{
    delete ui;
    delete logoArea;

}
