#ifndef TODOLISTMODEL_H
#define TODOLISTMODEL_H

#include <QAbstractListModel>

class Todo;
class Model;

class QListModel : public QAbstractListModel {
public:
    QListModel(QObject* = nullptr);
    ~QListModel() override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    // EDITABLE
    Qt::ItemFlags flags(const QModelIndex&) const override;
    bool setData(const QModelIndex&, const QVariant&, int) override;
    bool insertRows(int, int, const QModelIndex& = QModelIndex()) override;
    bool removeRows(int, int, const QModelIndex& = QModelIndex()) override;
    // SPECIAL TODO: funzione per togglare il tipo (special o standard)
    bool toggleType(const QModelIndex&);

    void readDataFromFile();
    void writeDataToFile();

    // void sort(int, Qt::SortOrder) override; ABOZZATO
private:
    Model* model;
};

#endif // TODOLISTMODEL_H
