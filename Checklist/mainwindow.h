#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

class TodoListModel; // definizioni incomplete
class QListView;
class QPushButton;
class QLineEdit;
class QFilterModel;

class MainWindow : public QWidget {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    // ~MainWindow();
    QSize sizeHint() const;
private:
    TodoListModel* qtmodel;
    QFilterModel* proxymodel;
    QListView* view;
    QLineEdit* searchbar;

    void loadData(); // non è chiamata da un pulsante quindi non serve sia uno SLOT

private slots:
    void addTodo();
    void removeTodo();
    void saveData();
    void toggleSpecialTodo();
    void textFilterChanged();
};

#endif // MAINWINDOW_H
