#include "lru_cache_generic.h"
#include <iostream>
#include <string>

// DLL Node constructor implementation
LRUCacheGeneric::DLLNode::DLLNode(const std::string& k, const std::string& v) : 
    key(k), value(v), prev(nullptr), next(nullptr) {}

// LRU Cache constructor impelmentation 
LRUCacheGeneric::LRUCacheGeneric(size_t cap) : capacity(cap), length(0), head(nullptr), tail(nullptr) {}

// LRU Cache destructor implementation. Free all linked list memory. 
LRUCacheGeneric::~LRUCacheGeneric() {
    // free memory of any remaining nodes in the DLL
    DLLNode* curr = head;
    while(curr != nullptr) {
        DLLNode* temp = curr;
        curr = curr->next;
        delete temp; 
    }
    // clear out the map
    lookup.clear();
}

// Doubly Linked List methods ---------------------------------------------------------

void LRUCacheGeneric::addNodeToHead(DLLNode* node) {
    if (head == nullptr) {
        head = node;
        tail = node;
    } else {
        node->next = head;
        head->prev = node;
        head = node;
    }
}

void LRUCacheGeneric::removeNode(DLLNode* node) {
    if (node == head && node == tail) {
        head = nullptr;
        tail = nullptr;
    } else if (node == head) {
        head = head->next; 
        //edge case if head ends up being last node 
        if (head) {
            head->prev = nullptr;
        }
    } else if (node == tail) {
        tail = tail->prev;
        // if tail ends up being last node 
        if (tail) {
            tail->next = nullptr;
        }
    } else {
        node->prev->next = node->next; // rewire forwards
        node->next->prev = node->prev; // rewire backwards
    }
}


// make most recently used. Doesn't leak memory because reuses the same pointer.
void LRUCacheGeneric::moveToHead(DLLNode* node) {
    if (node == head) return; // Already MRU
    removeNode(node);
    addNodeToHead(node);
}

// LRU Methods -----------------------------------------------------------------------

// free memory in cache eviction!
void LRUCacheGeneric::evictCache() {
    if (tail) {
        lookup.erase(tail->key); // remove from hashmap
        DLLNode* oldTail = tail; // copy pointer to tail
        removeNode(tail); // detach tail from DLL
        delete oldTail; // free memory 
        tail = nullptr; // prevent dangling pointer
        length--; // decrement cache size 
    }
}

void LRUCacheGeneric::put(const std::string& key, const std::string& value) {
    auto it = lookup.find(key);
    if (it != lookup.end()) {
        // key found, so make MRU 
        DLLNode* existingNode = it->second; // the reference is in the value 
        existingNode->value = value; // update with new value
        moveToHead(existingNode); // make most recently used 
    } else {
        // key not found make new node and add to hashmap. Unless at capacity.
        if (length == capacity) {
            evictCache();
        }
        DLLNode* newLRUNode = new DLLNode(key, value);
        addNodeToHead(newLRUNode);
        lookup[key] = newLRUNode;
        length++;
    }   
}

std::string LRUCacheGeneric::get(const std::string& key) {
    auto it = lookup.find(key);
    if (it != lookup.end()) {
        DLLNode* retrievedNode = it->second;
        moveToHead(retrievedNode);
        return retrievedNode->value;
    }
    return "not found";
}

void LRUCacheGeneric::print() {
    DLLNode* curr = head;
    while (curr != nullptr) {
        std::cout << "Key: " << curr->key << " Value: " << curr->value << std::endl;
        curr = curr->next; 
    }
}

void LRUCacheGeneric::runTestsGenericCache () {
    
}