#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "dialogabout.h"
#include "dialogadd.h"

#include <QDateTime>
#include <QWidget>
#include <QStandardItemModel>
#include <QFile>
#include <QTextStream>
#include <QList>
#include <QFileDialog>
#include <vector>

#include <iostream>





MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    flightModel = new MyModel;
    flightList = new QTransposeProxyModel;
    headerInfo = new QStringListModel;
    sortModel = new QSortFilterProxyModel(this);

    ui->listView->setModelColumn(0);

    flightList->setSourceModel(flightModel);

    ui->listView->setModel(flightList);

    sortModel->setSourceModel(flightModel);
    ui->tableView->setModel(sortModel);
    ui->tableView->setSortingEnabled(true);

    connect(ui->tableView->selectionModel(),
            SIGNAL(currentChanged(QModelIndex,QModelIndex)),
            this,
            SLOT(onTableViewCurrentChanged(QModelIndex,QModelIndex)));

    connect(ui->listView->selectionModel(),
            SIGNAL(currentChanged(QModelIndex,QModelIndex)),
            this,
            SLOT(on_listView_clicked(QModelIndex,QModelIndex)));

}

MainWindow::~MainWindow()
{
    delete ui;
    delete flightModel;
    delete flightList;
    delete sortModel;
    delete headerInfo;
}

void MainWindow::loadButtonClicked()
{
    QString path = QFileDialog::getOpenFileName(this);

    if (path.isNull())
    {
        return;
    }

    flightModel->deleteAll();

    flightModel->fillModel(path);
    ui->tableView->sortByColumn(0, Qt::SortOrder::AscendingOrder);

    QList<QString> head = flightModel->getHeader();

    headerInfo->setStringList(head);

    ui->listView_2->setModel(headerInfo);

    ui->listView_2->setSelectionMode(QAbstractItemView::NoSelection);
}

void MainWindow::saveButtonClicked()
{
    QFileDialog fDial;

    fDial.setFileMode(QFileDialog::AnyFile);

    QString path = QFileDialog::getSaveFileName();

    QFile outFile(path);
    outFile.open(QFile::WriteOnly | QFile::Text);
    QTextStream out(&outFile);

    QList<QString> head;
    head = flightModel->getHeader();

    for(int i = 0; i < head.size(); ++i)
    {
        out << head[i];
        if(i != head.size() - 1)
        {
            out << ',';
        }
        else
        {
            out << "/n";
        }
    }


    for (int i = 0; i < flightModel->rowCount(); ++i)
    {
        for (int j = 0; j < flightModel->columnCount(); ++j)
        {
            QModelIndex idx = flightModel->index(i, j);
            out << flightModel->data(idx).toString();
            if (j != flightModel->columnCount() - 1)
            {
                out << ",";
            }
        }
        out << "\n";
    }
    outFile.close();
}


void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    int row = sortModel->mapToSource(index).row();
    ui->listView->setModelColumn(row);
}


// this thing did not work during the defence

void MainWindow::on_listView_clicked(const QModelIndex &index)
{
//    int row = index.row();
//    QModelIndex index33 = flightList->index(row, 0);
//    ui->listView_2->setCurrentIndex(index33);
}


void MainWindow::addFlightClicked()
{
    DialogAdd dialog1;
    dialog1.exec();

    QList<QVariant> newFlight = dialog1.getFlight();

    QString dateStr = newFlight[1].toString();

    if(dateStr.count(' ') != 0)
    {
        QList<QString> dateStrSplit = dateStr.split(' ');
        dateStr = dateStrSplit[0] + 'T' + dateStrSplit[1];
    }

    QDateTime date1 = QDateTime::fromString(dateStr, Qt::ISODate);
    if(date1.isValid())
    {
        newFlight[1] = date1;
    }
    else
    {
        newFlight[1] = QDateTime::fromString("2000-01-01T00:00", Qt::ISODate);
    }

    QTime time1 = QTime::fromString(newFlight[2].toString(), "h:mm");
    if(time1.isValid())
    {
        newFlight[2] = time1;
    }
    else
    {
        newFlight[2] = QTime::fromString("00:00", "h:mm");
    }

    flightModel->appendRow(newFlight);
}

void MainWindow::on_actionAbout_triggered()
{
    DialogAbout dialog;
    dialog.exec();
}

void MainWindow::onTableViewCurrentChanged(QModelIndex next, QModelIndex prev)
{
    int row = sortModel->mapToSource(next).row();
    ui->listView->setModelColumn(row);
}

void MainWindow::deleteButtonClicked()
{
    QModelIndex index = ui->tableView->currentIndex();

    QModelIndex index1 = sortModel->mapToSource(index);

    if(index.row()>-1)
    {
        flightModel->deleteRow(index1.row());
    }
}


