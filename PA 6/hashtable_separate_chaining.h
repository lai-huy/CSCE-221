#pragma once

#include <functional>
#include <iostream>
#include <list>
#include <sstream>
#include <stdexcept>
#include <vector>

using std::ostream, std::cout;

template <class Key, class Hash = std::hash<Key>>
class HashTable {
public:
    HashTable();
    explicit HashTable(size_t size);

    bool is_empty() const;
    size_t size() const;

    void make_empty();
    bool insert(const Key& key);
    size_t remove(const Key& key);

    bool contains(const Key& key) const;

    size_t bucket_count() const;
    size_t bucket_size(size_t index) const;
    size_t bucket(const Key& key) const;

    float load_factor() const;
    float max_load_factor() const;
    void max_load_factor(float) const;
    void rehash(size_t);

    void print_table(ostream& os=cout) const;

    HashTable(const HashTable& rhs);
    HashTable(HashTable&& rhs);
    ~HashTable();
    HashTable& operator=(const HashTable& rhs);
    HashTable& operator=(HashTable && rhs);
    void insert(Key&& key);
};
