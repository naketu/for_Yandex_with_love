#include "mymodel.h"

#include <QBrush>
#include <QFile>
#include <QTextStream>
#include <QDateTime>

#include <iostream>

MyModel::MyModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}


QVariant MyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    {
        if (role == Qt::DisplayRole && !headerList.empty())
        {
            if (orientation == Qt::Orientation::Horizontal)
            {
                return headerList.at(section);
            }
            else
            {
                return section + 1;
            }
        }
        return QVariant();
    }
}


int MyModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return myData.size();
}

int MyModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    if (myData.empty())
    {
        return 0;
    }

    return myData[0].size();
}

QVariant MyModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        return myData.at(index.row()).at(index.column());
    }

    else if (role == Qt::BackgroundRole)
    {
        return QBrush(Qt::white);
    }

    return QVariant();
}

bool MyModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value)
    {

        bool isNum = false;


        QDateTime dateSection = QDateTime::fromString(value.toString(), Qt::ISODate);
        if(dateSection.isValid())
        {
            myData[index.row()][index.column()] = dateSection;
            return true;
        }

        QTime timeSection = QTime::fromString(value.toString(), "h:mm:ss.zzz");

        if(timeSection.isValid())
        {
            myData[index.row()][index.column()] = timeSection;
            return true;
        }


        QVariant numValue = value.toInt(&isNum);
        if(isNum)
        {
            myData[index.row()][index.column()] = value.toInt();
            return true;
        }

        numValue = value.toDouble(&isNum);
        if(isNum)
        {
            myData[index.row()][index.column()] = value.toDouble();
            return true;
        }

        myData[index.row()][index.column()] = value.toString();
        return true;
    }
    return false;
}

Qt::ItemFlags MyModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
}


void MyModel::appendRow(QList<QVariant> newRow)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());

    if(myData.isEmpty())
    {
        beginInsertColumns(QModelIndex(), 0, colSize);
        endInsertColumns();
    }

    myData.append(newRow);

    endInsertRows();
}

void MyModel::deleteRow(int index)
{
    beginRemoveRows(QModelIndex(), index, index);
    myData.removeAt(index);
    endRemoveRows();
}

void MyModel::deleteAll()
{
    if(!myData.isEmpty())
    {
        beginRemoveColumns(QModelIndex(), 0, columnCount() - 1);
        beginRemoveRows(QModelIndex(), 0, rowCount() - 1);
        myData.clear();
        endRemoveRows();
        endRemoveColumns();
    }

}

QList<QString> MyModel::getHeader()
{
    return headerList;
}

void MyModel::fillModel(QString path)
{
    QFile inputFile(path);
    inputFile.open(QFile::ReadOnly | QFile::Text);
    QTextStream inputStream(&inputFile);

    QString firstLine = inputStream.readLine();
    headerList = firstLine.split(",");

    colSize = headerList.size() - 1;

    while(!inputStream.atEnd())
    {
        QString line = inputStream.readLine();
        QList<QVariant> row;

        int k = 0;

        for(QString& section : line.split(','))
        {
            ++k;

            if(k == 2)
            {
                QDateTime dateSection = QDateTime::fromString(section, Qt::ISODate);
                row.append(dateSection);
                continue;
            }

            if(k == 3)
            {
                QTime timeSection = QTime::fromString(section, "h:mm");
                if(!timeSection.isValid())
                {
                    QTime timeSection = QTime::fromString(section, "h:mm:ss.zzz");
                }
                row.append(timeSection);
                continue;
            }


            bool isNum = false;
            QVariant numSection = section.toInt(&isNum);
            if(isNum)
            {
                row.append(numSection);
                continue;
            }

            numSection = section.toDouble(&isNum);
            if(isNum)
            {
                row.append(numSection);
                continue;
            }
            row.append(section);
        }
        appendRow(row);
    }
    inputFile.close();
}

