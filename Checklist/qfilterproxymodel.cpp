#include "qfilterproxymodel.h"
#include "qlistmodel.h"

QFilterProxyModel::QFilterProxyModel(QObject* parent) : QSortFilterProxyModel(parent) {}

bool QFilterProxyModel::toggleType(const QModelIndex & index) {
    QModelIndex item = mapToSource(index);
    return static_cast<QListModel*>(sourceModel())->toggleType(item);
}

/* bool QFilterModel::removeRows(int row, int count, const QModelIndex & parent) {
    const QModelIndex trueindex = mapToSource(index(row, 0, parent));
    return sourceModel()->removeRows(trueindex.row(), count, parent);
}*/

// va reimplementata altrimenti cerca di mappare row nel qtmodel (ma non va bene perchè row
// è già l'ultima riga del qtmodel)
bool QFilterProxyModel::insertRows(int row, int count, const QModelIndex & parent) {
    bool result = sourceModel()->insertRows(row, count, parent);
    invalidateFilter();
    return result;
}

bool QFilterProxyModel::filterAcceptsRow(int row_source, const QModelIndex& /*parent*/ ) const {
    QModelIndex index_source = sourceModel()->index(row_source, 0);

    return sourceModel()->data(index_source).toString().contains(filterRegExp());
}
