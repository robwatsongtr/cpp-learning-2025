#ifndef LRUCACHE_H
#define LRUCACHE_H

#include <iostream>
#include <unordered_map>
#include <list>
#include <iterator>


class LRUCache {
private:
    struct DLLNode {
        std::string key;
        std::string value;
        DLLNode* prev;
        DLLNode* next;
 
        DLLNode(const std::string& k, const std::string& v);
    };

    std::unordered_map<std::string, DLLNode*> lookup;
    DLLNode* head = nullptr; // most recently used
    DLLNode* tail = nullptr; // least recently used 
    size_t capacity; 
    int length; 

    void addNewNode(const std::string& key, const std::string& value);

public:

    
};

#endif