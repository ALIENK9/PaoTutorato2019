#ifndef MODEL_H
#define MODEL_H

#include <fstream>
#include <string>
// #include <list>

#include <QList>

class Todo;

// using std::list;
using std::string;
// using std::ofstream;

class Model {
private:
    QList<Todo*> list;

public:
    Model();
    ~Model();

    int getListSize() const;
    const Todo* getTodo(int) const;
    void add(Todo*);
    void remove(int);
    void saveToFile(string) const; // scrittura su file
    void loadFromFile(string);  // lettura da file
    void replace(int, Todo*);
};

#endif // MODEL_H
