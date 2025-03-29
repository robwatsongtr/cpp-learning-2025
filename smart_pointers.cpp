#include "smart_pointers.h"
#include <vector>

SmartPointers::SmartPointers() : data(0) {
    std::cout << "smart pointers object created" << std::endl;
}

SmartPointers::~SmartPointers(){
    std::cout << "smart pointers object destroyed" << std::endl;
}

void SmartPointers::make_pointers(std::shared_ptr<std::string> &of) {
    std::shared_ptr<std::string> *pointers[100];
    for (int i=0; i < 100; ++i) {
        std::shared_ptr<std::string> *new_ptr = new std::shared_ptr<std::string>();
        (*new_ptr) = of;
        pointers[i] = new_ptr;
    }
    std::cout << "count is " << of.use_count() << std::endl;
    for (int i=0; i < 100; ++i) {
        delete pointers[i];
        pointers[i] = NULL;
    }
    std::cout << "count is " << of.use_count() << std::endl;
}