#include "smart_pointers.h"

SmartPointers::SmartPointers() : data(0) {
    std::cout << "smart pointers object created" << std::endl;
}

SmartPointers::~SmartPointers(){
    std::cout << "smart pointers object destroyed" << std::endl;
}