#include "listview.h"

#include <QMouseEvent> // per poter usare gli eventi del mouse come i click

ListView::ListView(QWidget* parent) : QListView(parent) {
    setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
    // per non complicare è selezionabile solo un item alla volta
}

// override delle dimensioni della view per farla espandere con il pannello
QSize ListView::sizeHint() const {
    return QSize(350, 600);
}

// gestisce il click singolo su qualunque elemento della vista
void ListView::mousePressEvent(QMouseEvent* event) {
    // se dove si è cliccato non c'è un elemento della lista (=> indice non valido) pulisce la selezione
    if (!indexAt(event->pos()).isValid()) {
        clearSelection();
        selectionModel()->clearCurrentIndex();
    }
    // altrimenti richiama il comportamento standard della QListView (che seleziona l'elemento cliccato)
    QListView::mousePressEvent(event);
}
