#include "mainwindow.h"
#include "todolistmodel.h"
#include "qfiltermodel.h"
#include "listview.h"

// solo per centrare l'app
#include <QDesktopWidget>
#include <QApplication>

#include <QLayout>
#include <QPushButton>
#include <QDebug>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QLineEdit>
// #include <QListView> mettere per View normale

MainWindow::MainWindow(QWidget *parent) : QWidget(parent),
    qtmodel(new TodoListModel(this)),
    proxymodel(new QFilterModel(this)),
    view(new ListView(this)),
    searchbar(new QLineEdit(this)) {

    // centra la finestra nello schermo
    move(QApplication::desktop()->screen()->rect().center() - rect().center());

    setWindowTitle(tr("Todo App"));
    setWindowIcon(QIcon(":/data/icon")); // icona del programma

    loadData();
    proxymodel->setSourceModel(qtmodel);

    view->setModel(proxymodel); // fornisce il viewmodel alla view
    // Spostata nella VIEW: view->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);

    // PULSANTI
    QPushButton* addButton = new QPushButton("Aggiungi", this);
    QPushButton* removeButton = new QPushButton("Rimuovi", this);
    QPushButton* saveButton = new QPushButton("Salva", this);

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
    mainLayout->addWidget(searchbar);
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

    // RICERCA
    searchbar->setPlaceholderText("Ricerca");
    connect(searchbar, SIGNAL(textChanged(QString)), this, SLOT(textFilterChanged()));

    // PULSANTE SPECIAL TODO
    QPushButton* toggleButton = new QPushButton("Speciale", this);
    buttonsLayout->addWidget(toggleButton);
    connect(toggleButton, SIGNAL(clicked()), this, SLOT(toggleSpecialTodo()));
}

// NB: non distrugge i QPushButton (di quello se ne occupa Qt)
// MainWindow::~MainWindow() {
    // delete qtmodel;
//}

void MainWindow::addTodo() {
    const int rows = proxymodel->rowCount() - 1;
    proxymodel->insertRows(rows, 1);
    // retrieve added item's QModelIndex
    const QModelIndex addedIndex = qtmodel->index(qtmodel->rowCount() - 1);
    // select last added item
    view->clearSelection();
    view->selectionModel()->clearCurrentIndex();
    view->selectionModel()->select(addedIndex, QItemSelectionModel::Select);
}

void MainWindow::removeTodo() {
    const QModelIndexList selection = view->selectionModel()->selectedIndexes();
    if(selection.size() > 0)
        proxymodel->removeRows(selection.at(0).row(), 1);
}

void MainWindow::saveData() {
    try {
        qtmodel->writeDataToFile();
    } catch (std::exception) {
        QMessageBox box(QMessageBox::Warning, "Errore di salvataggio", "Non è stato possibile scrivere sul file", QMessageBox::Ok);
        box.exec();
    }
}

void MainWindow::loadData() {
    qtmodel->readDataFromFile();
}

// definisce la dimensione ideale per l'app
QSize MainWindow::sizeHint() const {
    return QSize(300, 700);
}

// SPECIAL TODO: toggle fra SpecialTodo/StandardTodo
void MainWindow::toggleSpecialTodo() {
    // prende l'elenco dei selezionati (0 o 1 elementi)
    const QModelIndexList selection = view->selectionModel()->selectedIndexes();
    if(selection.size() > 0)
        proxymodel->toggleType(selection.at(0));
}

void MainWindow::textFilterChanged() {
    QRegExp regexp(searchbar->text(), Qt::CaseInsensitive, QRegExp::Wildcard);
    proxymodel->setFilterRegExp(regexp);
}

