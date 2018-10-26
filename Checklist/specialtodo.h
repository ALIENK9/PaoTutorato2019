#ifndef SPECIALTODO_H
#define SPECIALTODO_H

#include "todo.h"

class SpecialTodo : public Todo {
public:
    SpecialTodo(string = "");
    string getType() const override;
};

#endif // SPECIALTODO_H
