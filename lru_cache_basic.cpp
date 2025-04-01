#include "lru_cache_basic.h"

// DLL Node constructor 
LRUCache::DLLNode::DLLNode(const std::string& k, const std::string& v) : 
    key(k), value(v), prev(nullptr), next(nullptr) {}


LRUCache::LRUCache() {}

LRUCache::~LRUCache() {}

void LRUCache::addNewNode(const std::string& key, const std::string& value) {
    DLLNode* newNode = new DLLNode(key, value);
    if (head == nullptr) {
        head = newNode;
        tail = newNode;
    } else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
}

