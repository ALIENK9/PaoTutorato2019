#include "qfiltermodel.h"
#include "todolistmodel.h"

QFilterModel::QFilterModel(QObject* parent) : QSortFilterProxyModel(parent) {}

bool QFilterModel::toggleType(const QModelIndex & index) {
    QModelIndex item = mapToSource(index);
    return static_cast<TodoListModel*>(sourceModel())->toggleType(item);
}

/* bool QFilterModel::removeRows(int row, int count, const QModelIndex & parent) {
    const QModelIndex trueindex = mapToSource(index(row, 0, parent));
    return sourceModel()->removeRows(trueindex.row(), count, parent);
}*/

// va reimplementata altrimenti cerca di mappare row nel qtmodel (ma non va bene perchè row
// è già l'ultima riga del qtmodel)
bool QFilterModel::insertRows(int row, int count, const QModelIndex & parent) {
    bool result = sourceModel()->insertRows(row, count, parent);
    invalidateFilter();
    return result;
}

bool QFilterModel::filterAcceptsRow(int row_source, const QModelIndex& /*parent*/ ) const {
    QModelIndex index_source = sourceModel()->index(row_source, 0);

    return sourceModel()->data(index_source).toString().contains(filterRegExp());
}
