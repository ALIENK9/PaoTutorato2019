#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <QString>

class Todo;

class XmlIO {
public:
    XmlIO(QString);

    QList<Todo*> read() const;
    void write(const QList<Todo *> &) const;
private:
    QString filename;
};

#endif // XMLPARSER_H
