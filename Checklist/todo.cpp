#include "todo.h"

#include <QDebug>

Todo::Todo(string text) : text(text) {}

string Todo::getType() const {
    return "standard";
}

string Todo::getValue() const {
    return text;
}

/* bool Todo::operator==(const Todo& todo) const {
    return text == todo.toString();
}*/

ostream& operator<<(ostream& os, const Todo& todo) {
    os << todo.text;
    return os;
}
