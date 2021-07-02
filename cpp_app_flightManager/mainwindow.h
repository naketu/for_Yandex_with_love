#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTransposeProxyModel>
#include <QSortFilterProxyModel>
#include <QStringListModel>

#include "mymodel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void loadButtonClicked();
    void saveButtonClicked();
    void addFlightClicked();
    void on_actionAbout_triggered();
    void on_tableView_clicked(const QModelIndex &index);
    void on_listView_clicked(const QModelIndex &index);
    void onTableViewCurrentChanged(QModelIndex next, QModelIndex prev);
    void deleteButtonClicked();

private:
    Ui::MainWindow *ui;
    MyModel *flightModel;
    QTransposeProxyModel *flightList;
    QSortFilterProxyModel *sortModel;
    QStringListModel *headerInfo;
};
#endif // MAINWINDOW_H
