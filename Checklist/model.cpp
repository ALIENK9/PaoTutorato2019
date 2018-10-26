#include "model.h"
#include "xmlparser.h"
#include "todo.h"

// #include <QDir> non serve con resources
#include <QList>
#include <QDebug>
#include <QtAlgorithms> // per qDeleteAll
// #include <QListIterator> non serve se uso qDeleteAll

Model::Model() {} // carica la lista di todo dal file

Model::~Model() {

    qDeleteAll(list);

    /*
    QListIterator<Todo*> it(list);
    while(it.hasNext()) {
        const Todo* todo = it.next();
        qDebug() << "Destroyed " + QString::fromStdString(todo->getValue());
        delete todo;
    } */
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

// Sostituisce il Todo* in posizione "index" con newEl ed elimina quello vecchio
void Model::replace(int index, Todo* newEl) {
    if (index < list.size()) {
        delete list[index];
        qDebug() << "Deleted";
        list[index] = newEl;
    }
}

// Metodo di salvataggio della lista nel file indicato
void Model::saveToFile(string filename) const {
    // XmlParser xmlParser(QDir::currentPath().append("/../MVC/data/" + QString::fromStdString(filename) + ".xml"));
    XmlParser xmlParser(":/data/" + QString::fromStdString(filename));
    xmlParser.write(list);
}

// Legge l'elenco di todo dal file con il nome indicato e sovrascrive la lista già esistente
void Model::loadFromFile(string filename) {
    XmlParser xmlParser(":/data/" + QString::fromStdString(filename));
    list = xmlParser.read();
}
