// #include "templates.h"
// #include "smart_pointers.h"
// #include <memory>

#include "lru_cache_generic.h"
#include "lru_cache_basic.h"
#include <iostream>
#include <string>
#include <cassert>

// to compile and get an executable:
// 

int main() {

    // test basic cache 
    LRUCache::runTestsBasicCache();

    // test generic cache. <string string> is placeholder for the compiler since it's a templated class.
    LRUCacheGeneric<std::string, std::string>::runTestsGenericCache();

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
