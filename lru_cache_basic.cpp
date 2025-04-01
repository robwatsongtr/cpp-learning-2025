#include "lru_cache_basic.h"

// DLL Node constructor 
LRUCache::DLLNode::DLLNode(const std::string& k, const std::string& v) : 
    key(k), value(v), prev(nullptr), next(nullptr) {}


LRUCache::LRUCache() {}

LRUCache::~LRUCache() {}


void LRUCache::addNodeToHead(DLLNode* node) {
    if (head == nullptr) {
        head = node;
        tail = node;
    } else {
        node->next = head;
        head->prev = node;
        head = node;
    }
}

void LRUCache::removeNode(DLLNode* node) {
    if (node != head) {
        node->prev->next = node->next; // rewire forwards
        node->next->prev = node->prev; // rewire backwards 
    } else {
        head = head->next; 
        // edge case if head ends up being last node 
        if (head) {
            head->prev = nullptr;
        }
    }
    if (node == tail) {
        tail = tail->prev;
        // edge case if tail ends up being last node 
        if (tail) {
            tail->next = nullptr;
        }
    }
    delete node; 
}

void LRUCache::moveToHead(DLLNode* node) {
    removeNode(node);
    addNodeToHead(node);
}

void LRUCache::evictCache() {
    if (tail) {
        lookup.erase(tail->key);
        removeNode(tail);
        length--;
    }
}