#pragma once

#include <functional>
#include <iostream>
#include <list>
#include <sstream>
#include <stdexcept>
#include <vector>

using std::ostream, std::cout;
using std::hash;
using std::vector, std::list;

template <class Key, class Hash = hash<Key>>
class HashTable {
private:
    vector<list<Key>> _data;
    size_t _size;
public:
    HashTable() : HashTable(11) {}
    explicit HashTable(size_t size) : _data{vector<list<Key>>(size)} {}

    bool is_empty() const { return this->_size; }
    size_t size() const { return this->_size; }

    void make_empty();
    bool insert(const Key& key) {
        size_t index = Hash(key) % this->_data.size();
        this->_data.at(index).push_back(key);
    }

    size_t remove(const Key& key) {
        size_t index = Hash(key) & this->_data.size();
        this->_data.at(index).remove(key);
    }

    bool contains(const Key& key) const {
        list<Key> list = this->_data.at(Hash(key) % this->_data.size());
        return std::find(list.begin(), list.end(), key);
    }

    size_t bucket_count() const;
    size_t bucket_size(size_t index) const;
    size_t bucket(const Key& key) const;

    float load_factor() const { return this->_size / this->_data.size() }
    float max_load_factor() const;
    void max_load_factor(float) const;
    void rehash(size_t);

    void print_table(ostream& os = cout) const;

    // ----------------------- Optional ----------------------- //
    // HashTable(const HashTable& rhs);
    // HashTable(HashTable&& rhs);
    // ~HashTable();
    // HashTable& operator=(const HashTable& rhs);
    // HashTable& operator=(HashTable&& rhs);
    // void insert(Key&& key);
};
