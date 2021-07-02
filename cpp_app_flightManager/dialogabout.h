#ifndef DIALOGABOUT_H
#define DIALOGABOUT_H

#include <QDialog>
#include "logoarea.h"

namespace Ui {
class DialogAbout;
}

class DialogAbout : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAbout(QWidget *parent = nullptr);
    ~DialogAbout();

private:
    Ui::DialogAbout *ui;
    LogoArea* logoArea;
};

#endif // DIALOGABOUT_H

