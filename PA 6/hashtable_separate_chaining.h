#pragma once

#include <functional>
#include <iostream>
#include <list>
#include <sstream>
#include <stdexcept>
#include <vector>

using std::ostream, std::cout;
using std::hash, std::find;
using std::vector, std::list;

template <class Key, class Hash = hash<Key>>
class HashTable {
private:
    vector<list<Key>> _table;
    size_t _size;
    size_t _bucket;

public:
    HashTable() : HashTable(11) {}
    explicit HashTable(size_t size) : _table{vector<list<Key>>(size)}, _size{0}, _bucket{size} {}

    bool is_empty() const { return this->_size; }
    size_t size() const { return this->_size; }

    void make_empty() {
        for (list<Key>& list : this->_table)
            list.clear();
        this->_size = 0;
    }

    bool insert(const Key& key) {
        size_t index = this->bucket(key);
        this->_table.at(index).push_back(key);
        ++this->_size;
    }

    size_t remove(const Key& key) {
        size_t index = this->bucket(key);
        this->_table.at(index).remove(key);
        --this->_size;
    }

    bool contains(const Key& key) const {
        list<Key> list = this->_table.at(this->bucket(key));
        return find(list.begin(), list.end(), key);
    }

    size_t bucket_count() const { return this->_bucket; }
    size_t bucket_size(size_t index) const { return this->_table.at(index).size(); };
    size_t bucket(const Key& key) const { return Hash(key) % this->_bucket; }

    float load_factor() const { return this->_size / this->_bucket; }
    float max_load_factor() const { return 1f; }
    void max_load_factor(float lf) const;
    void rehash(size_t size) {}

    void print_table(ostream& os = cout) const {
        if (!this->_size) {
            os << "<empty>";
            return;
        }

        for (size_t i = 0; i < this->_table.size(); ++i) {
            const list<Key> l = this->_table.at(i);
            if (l.empty())
                continue;
            os << i << ": [";
            for (list<Key>::const_iterator iter(l.begin()); iter != l.end(); ++iter) {
                os << *iter;
                if (*iter != l.back())
                    os << ", ";
            }
            os << "]\n";
        }
    }

    // ----------------------- Optional ----------------------- //
    // HashTable(const HashTable& rhs);
    // HashTable(HashTable&& rhs);
    // ~HashTable();
    // HashTable& operator=(const HashTable& rhs);
    // HashTable& operator=(HashTable&& rhs);
    // void insert(Key&& key);
};
