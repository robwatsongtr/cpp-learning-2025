#include "templates.h"
#include "raw_pointers.h"
#include "smart_pointers.h"
#include <memory>

int main() {





    // template class code
    // mynamespace::MyTemplate<int> obj(42);  // int spec
    // obj.display();

    // mynamespace::MyTemplate<std::string> strObj("Hello, Templates!"); // string spec
    // strObj.display();

    SmartPointers ptrs;
    std::shared_ptr<std::string> ptr = std::make_shared<std::string>("hello");
    ptrs.make_pointers(ptr);

    return 0;
}
