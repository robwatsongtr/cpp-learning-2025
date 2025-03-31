#ifndef LRUCACHE_H
#define LRUCACHE_H

#include <iostream>
#include <unordered_map>
#include <list>
#include <iterator>


class LRUCache {
public:
    LRUCache();
    ~LRUCache();

private:
    size_t _capacity; 
    // in this non templated implementation, each list node is ("string", int)
    std::list<std::pair<std::string, int>> _node; 
    // the map stores the same key as within the list node, and an iterator back to the list
    // the iterator needs to be of the same type as the list  
    std::unordered_map<std::string, std::list<std::pair<std::string, int>>::iterator> _map;
};

#endif