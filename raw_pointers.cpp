#include "raw_pointers.h"

// constructor 
RawPointers::RawPointers() : data(0) {
    std::cout << "raw pointers object created" << std::endl;
}

RawPointers::~RawPointers(){
    std::cout << "raw pointers object destroyed" << std::endl;
}