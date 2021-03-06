#include "qlistmodel.h"
#include "model.h"
#include "todo.h"
#include "specialtodo.h"

#include <QFont> // per cambiare il font in "data()"

QListModel::QListModel(QObject *parent)
    : QAbstractListModel(parent), model(new Model()) {}

QListModel::~QListModel() {
    delete model;
}

// deve essere reimplementata per dire alla view quante righe costruire per rappresentare il modello
int QListModel::rowCount(const QModelIndex& /*parent*/) const {
    return model->getListSize();
}

// dice alla view come mappare ogni riga (della view) al modello dei dati (ogni riga un Todo)
QVariant QListModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid())
        return QVariant();

    if (index.row() >= model->getListSize())
        return QVariant();

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        return QString::fromStdString(model->getTodo(index.row())->getText());
    }

    // SPECIAL TODO: per cambiare colore della riga se è "special"
    if (role == Qt::FontRole) {
        const string type = model->getTodo(index.row())->getType();
        if (type == "special") {
            QFont font = QFont("Arial", 14, QFont::Bold);
            font.setCapitalization(QFont::AllUppercase);
            return font;
        }
    }
    return QVariant();
}

// EDITABLE

// Questo metodo specifica le proprietà di ogni riga (come se è editabile oppure no)
Qt::ItemFlags QListModel::flags(const QModelIndex &index) const {
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractListModel::flags(index) | Qt::ItemIsEditable;
}


bool QListModel::setData(const QModelIndex& index, const QVariant& value, int role) {
    if (index.isValid() && role == Qt::EditRole) {
        // SPECIAL TODO
        const string type = model->getTodo(index.row())->getType();
        /* CON TODO IMMUTABILE serve sostituire l'intero Todo
        Todo* todo;
        if (type == "special")
            todo = new SpecialTodo(value.toString().toStdString());
        else
            todo = new Todo(value.toString().toStdString()); */
        // ~SPECIAL TODO

        model->editTodo(index.row(), value.toString().toStdString());
        // la documentazione chiede di emettere il segnale esplicitamente
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

bool QListModel::removeRows(int begin, int count, const QModelIndex& parent) {
    beginRemoveRows(parent, begin, begin + count - 1);
    model->remove(begin); // nel nostro caso si rimuove una riga ovvero begin
    endRemoveRows();
    return true;
}

/**
 * @brief TodoListModel::insertRow. Aggiunge todo vuoti al modello
 * @param begin: index where to insert first new row
 * @param count: number of rows to insert
 * @param parent
 * @return true if insertion was completed
 */
bool QListModel::insertRows(int begin, int count, const QModelIndex& parent) {
    beginInsertRows(parent, begin, begin + count - 1); // parent, first row, last row
    model->add(new Todo("Nuovo todo"));
    endInsertRows();
    return true;
}

// SPECIAL TODO: edita il tipo da special a standard e viceversa
bool QListModel::toggleType(const QModelIndex& index) {
    if (!index.isValid()) // se l'indice non è valido (es. nessun indice selezionato) non fa nulla
        return false;
    const Todo* todo = model->getTodo(index.row()); // recupera il Todo
    const string type = todo->getType(); // recupera il tipo del todo
    const string value = todo->getText(); // recupera il testo del todo
    Todo* newTodo = (type == "standard" ? new SpecialTodo(value) : new Todo(value));
    model->replace(index.row(), newTodo); // rimpiazza il nuovo todo a quello vecchio che viene eliminato

    emit dataChanged(index, index); // segnale per avvisare la view del cambiamento (fonte: Doc di Qt)
    return true; // convenzionalmente Qt ritorna true quando l'operazione va a buon fine
}

void QListModel::readDataFromFile() {
    model->loadFromFile("data");
}

void QListModel::writeDataToFile() {
    model->saveToFile("data");
}

// inutile per i QAbstractListModel ma può servire per QAbstractTableModel
/* QVariant TodoListModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole && role != Qt::EditRole)
        return QVariant();
    if (orientation == Qt::Horizontal)
        return QString("Lista");
} */

/* void TodoListModel::sort(int col, Qt::SortOrder order = Qt::AscendingOrder) {
   - aggiungere operatore < fra Todo
   - Aggiungere un metodo sort al modello Model che ordina la lista a seconda del parametro

   QUI
   - layoutAboutToBeChanged()
   - ordinare il Model con sort()
   - changePersistentIndexList()
   - Emit the layoutChanged() signal.
} */


