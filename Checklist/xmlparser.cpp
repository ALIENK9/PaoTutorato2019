#include "xmlparser.h"
#include "todo.h"
#include "specialtodo.h"

#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QDebug>
#include <QFile>
#include <QSaveFile>
#include <QList>
#include <QListIterator>

XmlParser::XmlParser(QString filename) : filename(filename) {}
   // qDebug() << QFile::exists(QDir::currentPath().append("/../Checklist/data/data.xml"));

QList<Todo*> XmlParser::read() const {

    QList<Todo*> list;

    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly)) { // se non esiste, "open" crea un nuovo file vuoto
        qDebug() << "Cannot read file" << file.errorString();
        return list;
    }
    // Elenco delle flag di apertura: http://doc.qt.io/qt-5/qiodevice.html#OpenModeFlag-enum

    QXmlStreamReader reader(&file);
    if(reader.readNextStartElement()) {
        if(reader.name() == "root") {
            while(reader.readNextStartElement()) {
                if(reader.name() == "todo") {
                    const QXmlStreamAttributes attributes = reader.attributes();
                    const QString type = attributes.hasAttribute("type") ? attributes.value("type").toString() : "skip";
                    const QString textValue = reader.readElementText();
                    if (type == "standard")
                        list.append(new Todo(textValue.toStdString()));
                    else if (type == "special")
                        list.append(new SpecialTodo(textValue.toStdString()));
                }
                else
                    reader.skipCurrentElement();
            }
        }
        else {
            reader.skipCurrentElement();
            reader.raiseError("Incorrect root tag"); // solo per debug
        }
    }

    file.close();
    return list;
}

void XmlParser::write(QList<Todo*> list) const {

    // QSaveFile rispetto a QFile è più adatto per effettuare scritture su disco. Gestisce meglio
    // i casi di errore, garantendo che non vengano persi i dati del file in caso di errori in scrittura
    QSaveFile file(filename);

    if(!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Cannot open file to write" << file.errorString();
    }

    QXmlStreamWriter writer(&file);

    // "autoFormatting": Il writer aggiunge automaticamente indentazioni e caporiga per migliorare la leggibilità
    // link: http://doc.qt.io/archives/qt-4.8/qxmlstreamwriter.html#autoFormatting-prop
    writer.setAutoFormatting(true);
    writer.writeStartDocument(); // scrive le informazioni iniziali di un file XML (versione 1.0)
    writer.writeComment("File di salvataggio usato dall'applicazione TodoList. Non modificare a mano!"); // È possibile scrivere commenti
    writer.writeStartElement("root"); // <root>

    QListIterator<Todo*> i(list); // Java style iterator

    while (i.hasNext()) {
        writer.writeStartElement("todo"); // <todo>
        const Todo* item = i.next();
        const string type = item->getType();
        const string value = item->getValue();
        qDebug() << "Scrivendo" + QString::fromStdString(type);
        writer.writeAttribute("type", QString::fromStdString(type)); // <todo type="...">
        writer.writeCharacters(QString::fromStdString(value)); // scrive il testo del todo
        writer.writeEndElement(); // </todo>
    }
    writer.writeEndElement(); // </root>
    writer.writeEndDocument(); // Closes all remaining open start elements and writes a newline.

    file.commit();
}
