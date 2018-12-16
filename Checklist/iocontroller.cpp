#include "iocontroller.h"
#include "model.h"

#include <QMessageBox>

IOController::IOController(Model& model) : model(model) {}

void IOController::writeDataToFile() {
    try {
        model.saveToFile("data");
    } catch (std::exception) {
        QMessageBox box(QMessageBox::Critical, "Errore di salvataggio", "Non è stato possibile scrivere sul file", QMessageBox::Ok);
        box.exec();
    }
}

void IOController::readDataFromFile() {
    // try {
        model.loadFromFile("data");
    // } catch (std::exception) {
        // QMessageBox box(QMessageBox::Warning, "Errore in lettura", "Non è stato possibile caricare i dati", QMessageBox::Ok);
        // box.exec();
    // }
}


