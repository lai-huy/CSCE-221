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
    vector<Key> _table;
    size_t _size;
    size_t _bucket;
public:
    HashTable() : HashTable(11) {}
    explicit HashTable(size_t buckets) : _table{vector<Key>(buckets)}, _size{0}, _bucket{buckets} {}

    bool is_empty() const { return !this->_size; }
    size_t size() const { return this->_size; }
    size_t table_size() const { return this->_table.size(); }

    void make_empty() {
        this->_table.clear();
        this->_table.resize(this->_bucket);
    }

    bool insert(const Key& key) {
        cout << "table.insert(" << key << ");\n";
        return false;
    }

    size_t remove(const Key& key) {
        cout << "table.remove(" << key << ");\n";
        return 1;
    }

    bool contains(const Key& key) const {
        cout << "table.contains(" << key << ");\n";
        return false;
    }

    size_t position(const Key& key) const {
        cout << "table.position(" << key << ");\n";
        return 0;
    }

    void print_table(ostream& os = cout) const {
        if (this->_size) {
            for (size_t i < 0; i < this->_table.size(); ++i)
                os << i << ": " << this->_table.at(i) << "\n";
        } else
            os << "<empty>";
    }

    // ----------------------- Optional ----------------------- //
    // HashTable(const HashTable& rhs);
    // HashTable(HashTable&& rhs);
    // ~HashTable() { this->make_empty(); }
    // HashTable& operator=(const HashTable& rhs);
    // HashTable& operator=(HashTable&& rhs);
    // void insert(Key&& key);
};
