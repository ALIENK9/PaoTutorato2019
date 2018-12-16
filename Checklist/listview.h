#ifndef VIEW_H
#define VIEW_H

#include <QListView>

class ListView : public QListView {
public:
    ListView(QWidget* = nullptr);
    QSize sizeHint() const override;
    void mousePressEvent(QMouseEvent*) override; // per pulire la selezione
};

#endif // VIEW_H
