#include "specialtodo.h"

#include <QDebug>

SpecialTodo::SpecialTodo(string text) : Todo(text) {}

string SpecialTodo::getType() const {
    return "special";
}
