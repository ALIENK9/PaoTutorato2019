#ifndef QFILTERMODEL_H
#define QFILTERMODEL_H

#include <QSortFilterProxyModel>

class QFilterProxyModel : public QSortFilterProxyModel {
public:
    QFilterProxyModel(QObject* = nullptr);
    bool toggleType(const QModelIndex&);
    // bool removeRows(int, int, const QModelIndex& = QModelIndex()) override;
    bool insertRows(int, int, const QModelIndex& = QModelIndex()) override;
protected:
    bool filterAcceptsRow(int, const QModelIndex&) const override;
};

#endif // QFILTERMODEL_H
