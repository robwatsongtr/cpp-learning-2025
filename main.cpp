// #include "templates.h"
// #include "raw_pointers.h"
// #include "smart_pointers.h"
// #include <memory>

#include <iostream>
#include "lru_cache_basic.h"
#include <string>

int main() {

    LRUCache my_cache(3);
    my_cache.put("a", "Rob loves C++. Kind of.");
    my_cache.put("b", "This is a bunch of data I'm caching");
    my_cache.put("c", "Holy sh&$ this is more data I might need");

    std::cout << "initial state" << std::endl;
    my_cache.print(); // initial state "c", "b", "a"
    std::cout << std::endl; 

    std::string getBdata = my_cache.get("b"); 
    std::cout << "Data requested: " << getBdata << std::endl; 
    std::cout << std::endl; 

    std::cout << "b moved to head" << std::endl;
    my_cache.print(); // "b", "c", "a"
    
    my_cache.put("d", "This should evict since its one over capacity");
    
    std::cout << std::endl; 
    std::cout << "put in a new key d, evict a and add d to head" << std::endl;
    my_cache.print(); // "d", "b" , "c "
    

    // SmartPointers ptrs;
    // std::shared_ptr<std::string> ptr = std::make_shared<std::string>("hello");
    // ptrs.make_pointers(ptr);

    // template class code
    // mynamespace::MyTemplate<int> obj(42);  // int spec
    // obj.display();

    // mynamespace::MyTemplate<std::string> strObj("Hello, Templates!"); // string spec
    // strObj.display();

    return 0;
}
