#pragma once

#include <functional>
#include <iostream>
#include <list>
#include <sstream>
#include <stdexcept>
#include <vector>

using std::ostream, std::cout;
using std::hash;

template <class Key, class Hash = hash<Key>>
class HashTable {
public:
    HashTable();
    explicit HashTable(size_t buckets);

    bool is_empty() const;
    size_t size() const;
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
    // ~HashTable();
    // HashTable& operator=(const HashTable& rhs);
    // HashTable& operator=(HashTable&& rhs);
    // void insert(Key&& key);
};
