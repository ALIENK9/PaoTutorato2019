#ifndef TODOLISTMODEL_H
#define TODOLISTMODEL_H

#include <QAbstractListModel>

class Todo;
class Model;

class TodoListModel : public QAbstractListModel {
public:
    TodoListModel(Model&, QObject* = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    // EDITABLE
    Qt::ItemFlags flags(const QModelIndex&) const override;
    bool setData(const QModelIndex&, const QVariant&, int) override;
    bool insertRow(int, const QModelIndex& = QModelIndex());
    bool removeRow(int, const QModelIndex& = QModelIndex());
    // SPECIAL TODO: funzione per togglare il tipo (special o standard)
    bool toggleType(const QModelIndex&);
private:
    Model& model;
};

#endif // TODOLISTMODEL_H
