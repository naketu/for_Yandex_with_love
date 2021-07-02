#ifndef MYMODEL_H
#define MYMODEL_H

#include <QAbstractTableModel>
#include <QList>

class MyModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit MyModel(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    void setHeaderData(QList<QString> head);

    QList<QString> getHeader();


    // Basic functionality:

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    // Add data:

    void appendRow(QList<QVariant> newRow);

    void fillModel(QString path);

    void deleteRow(int index);

    void deleteAll();

private:
    int colSize;
    QList<QList<QVariant>> myData;
    QList<QString> headerList;

};

#endif // MYMODEL_H
