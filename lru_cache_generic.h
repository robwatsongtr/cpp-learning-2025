#ifndef LRUCACHEGENERIC_H
#define LRUCACHEGENERIC_H

#include <iostream>
#include <unordered_map>
#include <string>
#include <cassert>

template<typename Key, typename Value>
class LRUCacheGeneric {
public:
    // LRU Cache constructor
    LRUCacheGeneric(size_t cap) :
        capacity(cap), length(0), head(nullptr), tail(nullptr) {}

    // LRU Cache destructor. Free all linked list memory.
    ~LRUCacheGeneric() {
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

    void put(const Key& key, const Value& value) {
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

    Value get(const Key& key) {
        auto it = lookup.find(key);
        if (it != lookup.end()) {
            DLLNode* retrievedNode = it->second;
            moveToHead(retrievedNode);
            return retrievedNode->value;
        }
        return "not found";
    }

    // free memory in cache eviction
    void evictCache() {
        if (tail) {
            lookup.erase(tail->key); // remove from hashmap
            DLLNode* oldTail = tail; // copy pointer to tail
            removeNode(tail); // detach tail from DLL
            delete oldTail; // free memory
            tail = nullptr; // prevent dangling pointer
            length--; // decrement cache size
        }
    }

    void print() {
        DLLNode* curr = head;
        while (curr != nullptr) {
            std::cout << "Key: " << curr->key << " Value: " << curr->value << std::endl;
            curr = curr->next;
        }
    }

    static void runTestsGenericCache() {
        std::cout << "-----Tests on Generic Cache-----" << std::endl;

        // Test 1: Request two missing keys of different types for a string-string cache
        LRUCacheGeneric<std::string, std::string> cache1(3);
        assert(cache1.get("a") == "not found"); // string key
        assert(cache1.get("b") == "not found"); // string key

        // Test 2: Insert key-value pairs of string-string type
        cache1.put("a", "Rob loves C++. Kind of.");
        assert(cache1.get("a") == "Rob loves C++. Kind of.");
        cache1.put("b", "C++ is awesome");
        assert(cache1.get("b") == "C++ is awesome");

        // Test 3: Fill up cache to capacity and print
        cache1.put("c", "Cache capacity reached");
        std::cout << "Initial state (after inserting 3 items):" << std::endl;
        cache1.print(); // Should print "c", "b", "a" if cache is full
        std::cout << std::endl;

        // Test 4: Access 'key b' to move it to the head
        std::string getBData = cache1.get("b");
        std::cout << "Data requested for 'b': " << getBData << std::endl;
        std::cout << "'b' moved to head" << std::endl;
        cache1.print(); // Should print "b", "c", "a"
        std::cout << std::endl;

        // Test 5: Insert "dog" to evict "a" off the tail
        cache1.put("dog", "Brand new data so important");
        std::cout << "Inserted new key 'dog', evicted 'a', added 'dog' to head:" << std::endl;
        cache1.print(); // Should print "dog", "b", "c"
        assert(cache1.get("a") == "not found"); // Ensure "a" was evicted
        std::cout << std::endl;

        // Test 6: Try getting a missing key
        std::cout << "Getting a key that doesn't exist (key 'l'):" << std::endl;
        std::string getLData = cache1.get("l");
        std::cout << "Data requested: " << getLData << std::endl;
        assert(getLData == "not found");

        // Now testing a cache with different types
        std::cout << "\nTesting cache with int-key and bool-value:" << std::endl;
        LRUCacheGeneric<int, bool> cache2(2);
        cache2.put(1, true);
        cache2.put(2, false);
        assert(cache2.get(1) == true);
        assert(cache2.get(2) == false);

        // Fill to capacity and test eviction
        cache2.put(3, true); // This should evict key 2
        std::cout << "After inserting 3, evicting 2:" << std::endl;
        cache2.print(); // Should print "3", "1"
        std::cout << std::endl;

        // Test with float key and string value
        std::cout << "Testing cache with float-key and string-value:" << std::endl;
        LRUCacheGeneric<float, std::string> cache3(2);
        cache3.put(1.1f, "One");
        cache3.put(2.2f, "Two");
        assert(cache3.get(1.1f) == "One");
        cache3.put(3.3f, "Three"); // This should evict 2.2f
        std::cout << "After inserting 3.3f, evicting 2.2f:" << std::endl;
        cache3.print(); // Should print "3.3", "1.1"
        std::cout << std::endl;

        // Final message
        std::cout << "🎉 All Generic LRU Cache tests passed!" << std::endl;
    }

private:
    struct DLLNode {
        Key key;
        Value value;
        DLLNode* prev;
        DLLNode* next;

        DLLNode(const Key& k, const Value& v) :
            key(k), value(v), prev(nullptr), next(nullptr) {}
    };

    std::unordered_map<Key, DLLNode*> lookup;
    DLLNode* head; // most recently used
    DLLNode* tail; // least recently used
    size_t capacity;
    size_t length;

    void addNodeToHead(DLLNode* node) {
        if (head == nullptr) {
            head = node;
            tail = node;
        } else {
            node->next = head;
            head->prev = node;
            head = node;
        }
    }

    void removeNode(DLLNode* node) {
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
    void moveToHead(DLLNode* node) {
        if (node == head) return; // Already MRU
        removeNode(node);
        addNodeToHead(node);
    }
};

#endif