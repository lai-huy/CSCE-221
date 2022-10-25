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
    enum State { EMPTY, ACTIVE, DELETED };

    vector<Key> _table;
    size_t _size;
public:
    HashTable() : HashTable(11) {}
    explicit HashTable(size_t buckets) : _table{vector<Key>(buckets)} {}

    bool is_empty() const { return !this->_size; }
    size_t size() const { return this->_size; }
    size_t table_size() const { return this->_table.size(); }

    void make_empty() {
    }
    bool insert(const Key& key);
    size_t remove(const Key& key);

    bool contains(const Key& key) const;
    size_t position(const Key& key) const;

    void print_table(ostream& os = cout) const {
        if (!this->_size) {
            os << "<empty>";
            return;
        }
    }

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
