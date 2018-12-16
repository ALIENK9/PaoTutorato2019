#include "mainwindow.h"
#include "todolistmodel.h"
#include "todo.h"
#include "model.h"
#include "listview.h"
#include "iocontroller.h"

// solo per centrare l'app
#include <QDesktopWidget>
#include <QApplication>

#include <QLayout>
#include <QPushButton>
#include <QDebug>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
// #include <QListView> mettere per View normale

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {

    // centra la finestra nello schermo
    move(QApplication::desktop()->screen()->rect().center() - rect().center());

    setWindowTitle(tr("Todo App"));
    setWindowIcon(QIcon(":/data/icon")); // icona del programma

    model = new Model(); // crea modello dati
    controller = new IOController(*model);       // avvia la lettura da file e riempie il modello
    loadData();
    viewmodel = new TodoListModel(*model, this); // crea un viewModel per usarlo con la view
    view = new ListView(this); // crea la view
    view->setModel(viewmodel); // fornisce il viewmodel alla view
    // Spostata nella VIEW: view->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);

    // PULSANTI
    addButton = new QPushButton("Aggiungi", this);
    removeButton = new QPushButton("Rimuovi", this);
    saveButton = new QPushButton("Salva", this);

    // BARRA DEL MENÙ
    QMenuBar* menuBar = new QMenuBar();
    QMenu* menu = new QMenu("File", menuBar);
    QAction* saveAction = new QAction("Save", menu);
    QAction* exitAction = new QAction("Exit", menu);
    // Assemblo menù
    menuBar->addMenu(menu);
    menu->addAction(saveAction);
    menu->addAction(exitAction);

    // LAYOUT
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(menuBar);
    mainLayout->addWidget(view, 0, Qt::AlignCenter);

    QHBoxLayout* buttonsLayout = new QHBoxLayout();
    buttonsLayout->addWidget(addButton);
    buttonsLayout->addWidget(removeButton);
    buttonsLayout->addWidget(saveButton);

    mainLayout->addLayout(buttonsLayout, 50);

    // CONNECT
    connect(saveButton, SIGNAL(clicked()), this, SLOT(saveData()));
    connect(addButton, SIGNAL(clicked()), this, SLOT(addTodo()));
    connect(removeButton, SIGNAL(clicked()), this, SLOT(removeTodo()));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(saveData()));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    // PULSANTE SPECIAL TODO
    QPushButton* toggleButton = new QPushButton("Speciale", this);
    buttonsLayout->addWidget(toggleButton);
    connect(toggleButton, SIGNAL(clicked()), this, SLOT(toggleSpecialTodo()));
}

// NB: non distrugge i QPushButton (di quello se ne occupa Qt)
MainWindow::~MainWindow() {
    // SALVATAGGIO NEL DISTRUTTORE
    // XmlParser xmlParser(QDir::currentPath().append("/../MVC/data/data.xml"));
    // xmlParser.write(model->getList());
    delete controller;
    delete model;
    // delete viewmodel;
}

void MainWindow::addTodo() {
    viewmodel->insertRow(model->getListSize() - 1);
    // retrieve added item's QModelIndex
    const QModelIndex addedIndex = viewmodel->index(model->getListSize() - 1);
    // select last added item
    view->clearSelection();
    view->selectionModel()->clearCurrentIndex();
    view->selectionModel()->select(addedIndex, QItemSelectionModel::Select);
}

void MainWindow::removeTodo() {
    const QModelIndexList selection = view->selectionModel()->selectedRows();
    if(selection.size() > 0)
        viewmodel->removeRow(selection.at(0).row());
}

void MainWindow::saveData() {
    controller->writeDataToFile();
}

void MainWindow::loadData() {
    controller->readDataFromFile();
}

// definisce la dimensione ideale per l'app
QSize MainWindow::sizeHint() const {
    return QSize(300, 700);
}

// SPECIAL TODO: toggle fra SpecialTodo/StandardTodo
void MainWindow::toggleSpecialTodo() {
    // prende l'elenco dei selezionati (0 o 1 elementi)
    const QModelIndexList selection = view->selectionModel()->selectedRows();
    if(selection.size() > 0)
        viewmodel->toggleType(selection.at(0));
}

