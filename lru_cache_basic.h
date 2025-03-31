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
 
        DLLNode(const std::string& k, const std::string& v) : key(k), value(v), prev(nullptr), next(nullptr) {}
    };

    std::unordered_map<std::string, DLLNode*> lookup;
    DLLNode* head = nullptr; // most recently used
    DLLNode* tail = nullptr; // least recently used 
    size_t capacity; 

    void addNewNode(const std::string& key, const std::string& value) {
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

public:

    
};

#endif