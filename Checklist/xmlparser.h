#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <QString>

class Todo;

class XmlParser {
public:
    XmlParser(QString);

    QList<Todo*> read() const;
    void write(QList<Todo*>) const;
private:
    QString filename;
};

#endif // XMLPARSER_H
