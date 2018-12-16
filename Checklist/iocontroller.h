#ifndef IOCONTROLLER_H
#define IOCONTROLLER_H

class Model;

class IOController {
private:
    Model& model;
public:
    IOController(Model&);
    void writeDataToFile();
    void readDataFromFile();
};

#endif // IOCONTROLLER_H
