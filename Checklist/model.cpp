#include "model.h"
#include "xmlio.h"
#include "todo.h"

#include <QDir> // non serve con resources
#include <QList>
#include <QDebug>
#include <QtAlgorithms> // per qDeleteAll
// #include <QListIterator> non serve se uso qDeleteAll

Model::Model() {} // carica la lista di todo dal file

Model::~Model() {

    qDeleteAll(list);

    /*
    for (QList<Todo*>::ConstIterator it = list.begin(); it != list.end(); it++) {
        const Todo* todo = *it;
        delete todo;
    }
    */

    /*
    QListIterator<Todo*> it(list);
    while(it.hasNext()) {
        const Todo* todo = it.next();
        delete todo;
    }
    */
}

int Model::getListSize() const {
    return list.size();
}
// Metodo per aggiungere un elemento di nome el EQUIVALE ad append()
void Model::add(Todo* el) { list.push_back(el); }

// Metodo per togliere l'elemento all'indice index della lista
void Model::remove(int index) {
    if (index < list.size()) {
        delete list[index];
        list.removeAt(index);
    }
}

// Ritorna il Todo* in posizione index
const Todo* Model::getTodo(int index) const {
    if (index < list.size())
        return list.at(index);
    return nullptr;
}

/* Sostituisce il Todo in posizione "index" della lista con "newTodo". Il Todo precedente viene distrutto
 * con delete.
 * Serve per sostituire un Todo con uno SpecialTodo e viceversa. Per la modifica del testo ho preferito
 * aggiungere il metodo editTodo sotto. */
void Model::replace(int index, Todo* newTodo) {
    if (index < list.size()) {
        delete list.at(index);
        qDebug() << "Deleted todo at " << index;
        list[index] = newTodo;
    }
    else // se l'indice non è valido (non dovrebbe accadere) bisogna pulire il Todo che non sarà aggiunto
        delete newTodo;
}

/* Sostituisce il campo "text" del Todo in posizione "index" con "newText".
 * Suppone che il Todo non sia immutabile */
void Model::editTodo(int index, string newText) {
    if (index < list.size()) {
        list[index]->editValue(newText);
    } // N.B: con todo immutabile serviva cancellare
}

// Metodo di salvataggio della lista nel file indicato
void Model::saveToFile(string filename) const {
    // cosa più semplice è dargli path assoluto
    XmlIO xmlIO("/home/alessandro/uni/tutorati/pao/PaoTutorato2019/Checklist/data/" + QString::fromStdString(filename) + ".xml");
    xmlIO.write(list);
}

// Legge l'elenco di todo dal file con il nome indicato e sovrascrive la lista già esistente
void Model::loadFromFile(string filename) {
    XmlIO xmlIO("/home/alessandro/uni/tutorati/pao/PaoTutorato2019/Checklist/data/" + QString::fromStdString(filename) + ".xml");
    list = xmlIO.read();
}
