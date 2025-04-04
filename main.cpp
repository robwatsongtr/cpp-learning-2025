// #include "templates.h"
// #include "raw_pointers.h"
// #include "smart_pointers.h"
// #include <memory>

#include <iostream>
#include "lru_cache_basic.h"
#include <string>
#include <cassert>

int main() {

    // test 1: requeset a missing key
    LRUCache my_cache(3);
    assert(my_cache.get("a") == "not found");

    // test 2: insert key value pair 
    my_cache.put("a", "Rob loves C++. Kind of.");
    assert(my_cache.get("a") == "Rob loves C++. Kind "); 

    // test 3: fill up cache to capacity 
    my_cache.put("b", "This is a bunch of data I'm caching");
    my_cache.put("c", "Holy sh&$ this is more data I might need");

    std::cout << "initial state" << std::endl;
    my_cache.print(); // initial state "c", "b", "a"
    std::cout << std::endl; 

    // test 4: access "b", which should move it to head 
    std::string getBdata = my_cache.get("b"); 
    std::cout << "Data requested: " << getBdata << std::endl; 
    std::cout << "b moved to head" << std::endl;
    my_cache.print(); // "b", "c", "a"
    std::cout << std::endl; 

    // test 5: Insert "d" which should evict "a" off the tail   
    my_cache.put("d", "Brand new data so important");
    std::cout << std::endl; 
    std::cout << "Inserted new key 'd', evict 'a', add 'd' to head:" << std::endl;
    my_cache.print(); // "d", "b" , "c "
    assert(my_cache.get("a") == "not found"); // ensure "a" was evicted

    // test 6: try getting a missing key 
    std::cout << std::endl;
    std::cout << "Get a key that doesnt exist: " << std::endl;
    std::string getLdata = my_cache.get("l");
    std::cout << "Data requested: " << getLdata << std::endl; 
    assert(getLdata == "not found");

    std::cout << "🎉 All LRU Cache tests passed!\n";
    

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
