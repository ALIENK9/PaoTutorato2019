#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

class TodoListModel; // definizioni incomplete
class QListView;
class QPushButton;
class Model;


class MainWindow : public QWidget {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QSize sizeHint() const;
private:
    Model* model;
    TodoListModel* viewmodel;
    QListView* view;
    QPushButton *addButton, *removeButton, *saveButton;

    void loadData(); // non è chiamata da un pulsante quindi non serve sia uno SLOT

private slots:
    void addTodo();
    void removeTodo();
    void saveData();
    void toggleSpecialTodo();
};

#endif // MAINWINDOW_H
