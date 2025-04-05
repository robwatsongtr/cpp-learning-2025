#ifndef LRUCACHE_H
#define LRUCACHE_H

#include <iostream>
#include <unordered_map>
#include <string>

class LRUCache {
private:
    struct DLLNode {
        std::string key;
        std::string value;
        DLLNode* prev;
        DLLNode* next;
 
        // node constructor definition
        DLLNode(const std::string& k, const std::string& v);
    };

    std::unordered_map<std::string, DLLNode*> lookup;
    DLLNode* head; // most recently used
    DLLNode* tail; // least recently used 
    size_t capacity; 
    size_t length; 

    void addNodeToHead(DLLNode* node);
    void removeNode(DLLNode* node);
    void moveToHead(DLLNode* node);
    
public:
    // LRU Cache constructor definition 
    LRUCache(size_t cap);
    // LRU Cache destructor definition 
    ~LRUCache();
    void put(const std::string& key, const std::string& value); 
    std::string get(const std::string& key);
    void evictCache();
    void print();
    static void runTestsBasicCache();
};

#endif