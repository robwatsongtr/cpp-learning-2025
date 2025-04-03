#include "lru_cache_basic.h"

// DLL Node constructor implementation
LRUCache::DLLNode::DLLNode(const std::string& k, const std::string& v) : 
    key(k), value(v), prev(nullptr), next(nullptr) {}

// LRU Cache constructor impelmentation 
LRUCache::LRUCache(size_t cap) : capacity(cap), length(0), head(nullptr), tail(nullptr) {}

// LRU Cache destructor implementation. Free all linked list memory. 
LRUCache::~LRUCache() {
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


// make most recently used 
void LRUCache::moveToHead(DLLNode* node) {
    if (node == head) return; // Already MRU
    removeNode(node);
    addNodeToHead(node);
}

// LRU Methods -----------------------------------------------------------------------

// free memory in cache eviction!
void LRUCache::evictCache() {
    if (tail) {
        lookup.erase(tail->key); // remove from hashmap
        DLLNode* oldTail = tail; // copy pointer to tail
        removeNode(tail); // detach tail from DLL
        delete oldTail; // free memory 
        tail = nullptr; // prevent dangling pointer
        length--; // decrement cache size 
    }
}

void LRUCache::put(const std::string& key, const std::string& value) {
    auto it = lookup.find(key);
    if (it != lookup.end()) {
        // key found, so make MRU 
        DLLNode* existingNode = it->second; // the reference is in the value 
        existingNode->value = value; // update with new value
        moveToHead(existingNode); // make most recently used 
    } else {
        // key not found make new node and add to hashmap
        if (length == capacity) {
            evictCache();
        }
        DLLNode* newLRUNode = new DLLNode(key, value);
        addNodeToHead(newLRUNode);
        lookup[key] = newLRUNode;
        length++;
    }   
}

std::variant<std::string, int> LRUCache::get(const std::string& key) {
    auto it = lookup.find(key);
    if (it != lookup.end()) {
        DLLNode* retrievedNode = it->second;
        moveToHead(retrievedNode);
        return retrievedNode->value;
    }
    return -1;
}