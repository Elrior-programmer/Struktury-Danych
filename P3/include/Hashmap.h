#pragma once

#include <iostream>
#include "LinkedList.h"
#include "DynamicArray.h"

template <typename V>
struct Entry {
    std::string key;
    V value;

    Entry() : key(""), value(V{}) {}
    Entry(std::string k, V v) : key(k), value(v) {}
};


template <typename V, typename HashFn>
class HashMap {
public:
    HashMap(int size, HashFn hashFn)
        : size(size), hashFn(hashFn) {
        for (int i = 0; i < size; i++)
            table.add_back(LinkedList<Entry<V>>());
    }

    void insert(const std::string& key, const V& value) {
        int slot = hashFn(key, size);
        Node<Entry<V>>* temp = table[slot].head;
        while (temp != nullptr) {
            if (temp->value.key == key) {
                temp->value.value = value;  
                return;
            }
            temp = temp->next;
        }
        table[slot].add_back(Entry<V>(key, value));  
    }

    V* search(const std::string& key) {
        int slot = hashFn(key, size);
        Node<Entry<V>>* temp = table[slot].head;
        while (temp != nullptr) {
            if (temp->value.key == key)
                return &temp->value.value;
            temp = temp->next;
        }
        return nullptr;
    }

    void remove(const std::string& key) {
        int slot = hashFn(key, size);
        Node<Entry<V>>* temp = table[slot].head;
        int index = 0;
        while (temp != nullptr) {
            if (temp->value.key == key) {
                table[slot].remove_at(index);
                return;
            }
            temp = temp->next;
            index++;
        }
        std::cout << "Key \"" << key << "\" not found\n";
    }

    void print() {
        for (int i = 0; i < size; i++) {
            if (table[i].size > 0) {
                std::cout << "slot " << i << ": ";
                Node<Entry<V>>* temp = table[i].head;
                while (temp != nullptr) {
                    std::cout << "[" << temp->value.key << " -> " << temp->value.value << "] ";
                    temp = temp->next;
                }
                std::cout << "\n";
            }
        }
    }

    private:
    int size;
    HashFn hashFn;
    DynamicArray<LinkedList<Entry<V>>> table;
};