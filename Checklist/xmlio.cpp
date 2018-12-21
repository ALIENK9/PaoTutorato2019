#include "xmlio.h"
#include "todo.h"
#include "specialtodo.h"

#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QDebug>
#include <QFile>
#include <QSaveFile>
#include <QList>
#include <QListIterator>

XmlIO::XmlIO(QString filename) : filename(filename) {}
   // qDebug() << QFile::exists(filename) << filename;

QList<Todo*> XmlIO::read() const {

    QList<Todo*> list;

    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly)) { // se non esiste, "open" crea un nuovo file vuoto
        qCritical() << "Cannot read file" << file.errorString();
        return list;
    }
    // Elenco delle flag di apertura: http://doc.qt.io/qt-5/qiodevice.html#OpenModeFlag-enum

    QXmlStreamReader reader(&file); // QIODevice*
    if(reader.readNextStartElement()) { // altrimenti la lista è vuota
        if(reader.name() == "root") { // altrimenti skippa
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
    }

    file.close();
    return list;
}

void XmlIO::write(const QList<Todo*>& list) const {

    // QSaveFile rispetto a QFile è più adatto per effettuare scritture su disco. Gestisce meglio
    // i casi di errore, garantendo che non vengano persi i dati del file in caso di errori in scrittura
    QSaveFile file(filename);

    if(!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Cannot open file to write" << file.errorString();
        throw std::exception();
    }

    QXmlStreamWriter writer(&file);

    // "autoFormatting": Il writer aggiunge automaticamente indentazioni e caporiga per migliorare la leggibilità
    // link: http://doc.qt.io/archives/qt-4.8/qxmlstreamwriter.html#autoFormatting-prop
    writer.setAutoFormatting(true);
    writer.writeStartDocument(); // scrive le informazioni iniziali di un file XML (versione 1.0)
    writer.writeComment("File di salvataggio usato dall'applicazione TodoList. Non modificare a mano!"); // È possibile scrivere commenti
    writer.writeStartElement("root"); // <root>

    QListIterator<Todo*> i(list); // Java style iterator
    // If an error occurs while writing to the underlying device, hasError() starts returning true
    // and subsequent writes are ignored.

    while (i.hasNext()) {
        writer.writeStartElement("todo"); // <todo>
        const Todo* item = i.next();
        const string type = item->getType();
        const string value = item->getText();
        qDebug() << "Scrivendo" + QString::fromStdString(type);
        writer.writeAttribute("type", QString::fromStdString(type)); // <todo type="...">
        writer.writeCharacters(QString::fromStdString(value)); // scrive il testo del todo
        writer.writeEndElement(); // </todo>
        if (writer.hasError()) // esempio di eccezione. Ne andrebbe creata una personalizzata.
            throw std::exception();
    }
    writer.writeEndElement(); // </root>
    writer.writeEndDocument(); // Closes all remaining open start elements and writes a newline.

    file.commit();
}
