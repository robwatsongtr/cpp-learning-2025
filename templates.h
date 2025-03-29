#ifndef TEMPLATES_H
#define TEMPLATES_H

#include <iostream>

namespace mynamespace {

// Template class definition of a typed named "T"
template <typename T>
class MyTemplate {
public:
    explicit MyTemplate(T value);  // Constructor
    ~MyTemplate();                 // Destructor

    void display() const;           // Member function

private:
    T data;                         // Private member variable
};

// Template function definitions must be in the header file
// Constructor 
template <typename T>
MyTemplate<T>::MyTemplate(T value) : data(value) {
    std::cout << "MyTemplate object created with value: " << data << std::endl;
}

// destructor 
template <typename T>
MyTemplate<T>::~MyTemplate() {
    std::cout << "MyTemplate object destroyed!" << std::endl;
}

template <typename T>
void MyTemplate<T>::display() const {
    std::cout << "Stored value: " << data << std::endl;
}

} // namespace mynamespace

#endif // MYTEMPLATE_H
