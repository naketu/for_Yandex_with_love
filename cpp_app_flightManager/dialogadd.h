#ifndef DIALOGADD_H
#define DIALOGADD_H

#include "mymodel.h"

#include <QDialog>

namespace Ui {
class DialogAdd;
}

class DialogAdd : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAdd(QWidget *parent = nullptr);
    ~DialogAdd();
    QList<QVariant> getFlight();

private:
    Ui::DialogAdd *ui;
    MyModel *flightModel;
    QList<QVariant> flight;

private slots:
    void addButtonClicked();
};

#endif // DIALOGADD_H
