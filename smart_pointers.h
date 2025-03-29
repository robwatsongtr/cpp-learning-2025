#ifndef SMARTPOINTERS_H
#define SMARTPOINTERS_H

#include <iostream>
#include <memory>
#include <string>

class SmartPointers {
public:
    SmartPointers();
    ~SmartPointers();

    void make_pointers(std::shared_ptr<std::string> &of);

private:
    int data;

};

#endif