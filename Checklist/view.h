#ifndef VIEW_H
#define VIEW_H

#include <QListView>

class View : public QListView {
public:
    View(QWidget* = nullptr);
    QSize sizeHint() const override;
    void mousePressEvent(QMouseEvent*) override; // per pulire la selezione
};

#endif // VIEW_H
