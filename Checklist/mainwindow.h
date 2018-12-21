#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

class QListModel; // definizioni incomplete
class QListView;
class QPushButton;
class QLineEdit;
class QFilterProxyModel;

class MainWindow : public QWidget {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    // ~MainWindow();
    QSize sizeHint() const;
private:
    QListModel* qtmodel;
    QFilterProxyModel* proxymodel;
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
