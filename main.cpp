#include "templates.h"
#include "raw_pointers.h"
#include "smart_pointers.h"


int main() {





    // template class code 
    mynamespace::MyTemplate<int> obj(42);  // int spec 
    obj.display();

    mynamespace::MyTemplate<std::string> strObj("Hello, Templates!"); // string spec
    strObj.display();

    return 0;
}
