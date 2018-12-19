#ifndef QFILTERMODEL_H
#define QFILTERMODEL_H

#include <QSortFilterProxyModel>

class QFilterModel : public QSortFilterProxyModel {
public:
    QFilterModel(QObject* = nullptr);
    bool toggleType(const QModelIndex&);
    // bool removeRows(int, int, const QModelIndex& = QModelIndex()) override;
    bool insertRows(int, int, const QModelIndex& = QModelIndex()) override;
protected:
    bool filterAcceptsRow(int, const QModelIndex&) const override;
};

#endif // QFILTERMODEL_H
