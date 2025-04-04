#include "lru_cache_basic.h"
#include <iostream>
#include <string>

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


// make most recently used. Doesn't leak memory because reuses the same pointer.
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

std::string LRUCache::get(const std::string& key) {
    auto it = lookup.find(key);
    if (it != lookup.end()) {
        DLLNode* retrievedNode = it->second;
        moveToHead(retrievedNode);
        return retrievedNode->value;
    }
    return "not found";
}

void LRUCache::print() {
    DLLNode* curr = head;
    while (curr != nullptr) {
        std::cout << "Key: " << curr->key << " Value: " << curr->value << std::endl;
        curr = curr->next; 
    }
}

void LRUCache::runTestsBasicCache() {
    // test 1: requeset a missing key
    LRUCache my_cache(3);
    assert(my_cache.get("a") == "not found");

    // test 2: insert key value pair 
    my_cache.put("a", "Rob loves C++. Kind of.");
    assert(my_cache.get("a") == "Rob loves C++. Kind of."); 

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
}