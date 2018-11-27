#ifndef TODO_H
#define TODO_H

#include <iostream>
#include <string>

using std::string;
using std::ostream;

class Todo {
    friend ostream& operator<<(ostream& os, const Todo& dt);
public:
    Todo(string = "");
    virtual ~Todo() = default;
    virtual string getType() const;
    virtual string getValue() const;
    void editValue(string);
protected:
    string text;
};

#endif // TODO_H
