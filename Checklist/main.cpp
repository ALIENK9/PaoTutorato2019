#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include <QDebug>

/*
Risorse Qt:
- https://doc.qt.io/qtvstools/qtvstools-managing-resources.html
- http://doc.qt.io/qt-5/resources.html#resource-collection-files-op-op-qrc
*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile file(":/data/qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    a.setStyleSheet(styleSheet);
    file.close();

    MainWindow w;
    w.show();

    return a.exec();
}
