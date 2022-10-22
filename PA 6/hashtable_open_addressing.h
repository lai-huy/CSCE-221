#pragma once

#include <functional>
#include <iostream>
#include <list>
#include <sstream>
#include <stdexcept>
#include <vector>

using std::ostream, std::cout;
using std::hash;
using std::vector;

template <class Key, class Hash = hash<Key>>
class HashTable {
private:
    size_t _size;
public:
    HashTable();
    explicit HashTable(size_t buckets);

    bool is_empty() const { return !this->_size; }
    size_t size() const { return this->_size; }
    size_t table_size() const;

    void make_empty();
    bool insert(const Key& key);
    size_t remove(const Key& key);

    bool contains(const Key& key) const;
    size_t position(const Key& key) const;

    void print_table(ostream& os = cout) const;

    // ----------------------- Optional ----------------------- //
    // HashTable(const HashTable& rhs);
    // HashTable(HashTable&& rhs);

    ~HashTable() {
        this->make_empty();
    }

    // HashTable& operator=(const HashTable& rhs);
    // HashTable& operator=(HashTable&& rhs);
    // void insert(Key&& key);
};
