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
using std::out_of_range, std::invalid_argument;

template <class Key, class Hash = hash<Key>>
class HashTable {
private:
    vector<list<Key>> _table;
    size_t _size;
    size_t _bucket;
    float _mlf;

    bool isPrime(const size_t& num) const {
        if (num < 2)
            return false;
        if (num < 4)
            return true;
        if (num % 2 == 0)
            return false;
        if (num % 3 == 0)
            return false;
        for (size_t i = 5; i * i <= num; i += 6) {
            if (num % i == 0)
                return false;
            if (num % (i + 2) == 0)
                return false;
        }
        return true;
    }

    size_t nextPrime(const size_t& num) const {
        size_t i = num;
        while (!this->isPrime(i))
            ++i;
        return i;
    }

public:
    HashTable() : HashTable(11) {}
    explicit HashTable(size_t size) : _table{vector<list<Key>>(size)}, _size{0}, _bucket{size}, _mlf{1.0f} {}

    bool is_empty() const { return !this->_size; }
    size_t size() const { return this->_size; }

    void make_empty() {
        for (list<Key>& list : this->_table)
            list.clear();
        this->_table.clear();
        this->_table.resize(this->_bucket);
        this->_size = 0;
    }

    bool insert(const Key& key) {
        if (this->contains(key))
            return false;
        size_t bucket = this->bucket(key);
        this->_table.at(bucket).push_back(key);
        ++this->_size;
        if (this->load_factor() > this->max_load_factor()) {
            size_t size = this->nextPrime(2 * this->_bucket + 1);
            this->rehash(size);
        }
        return true;
    }

    size_t remove(const Key& key) {
        if (!this->contains(key))
            return 0;
        size_t index = this->bucket(key);
        this->_table.at(index).remove(key);
        --this->_size;
        return 1;
    }

    bool contains(const Key& key) const {
        list<Key> list = this->_table.at(this->bucket(key));
        return find(list.begin(), list.end(), key) != list.end();
    }

    size_t bucket_count() const { return this->_bucket; }

    size_t bucket_size(size_t index) const {
        if (index >= this->_bucket)
            throw out_of_range("Invalid bucket");
        return this->_table.at(index).size();
    };

    size_t bucket(const Key& key) const { return Hash()(key) % this->_bucket; }

    float load_factor() const { return static_cast<float>(this->_size) / this->_bucket; }

    float max_load_factor() const { return this->_mlf; }

    void max_load_factor(float lf) {
        if (lf == .0f)
            throw invalid_argument("new max load factor is 0");
        if (lf != lf)
            throw invalid_argument("new max load factor is not a number");
    }

    void rehash(size_t bucket) {
        if (bucket != this->_bucket) {
            this->_bucket = static_cast<float>(this->_size) / bucket > this->_mlf ? static_cast<size_t>(this->_size / this->_mlf) : bucket;
            vector<Key> temp;
            for (const list<Key>& l : this->_table)
                for (const Key& key : l)
                    temp.push_back(key);
            this->make_empty();
            for (const Key& key : temp)
                this->insert(key);
        }
    }

    void print_table(ostream& os = cout) const {
        if (this->_size) {
            for (size_t i = 0; i < this->_table.size(); ++i) {
                const list<Key> l = this->_table.at(i);
                if (l.empty())
                    continue;
                os << i << ": [";
                for (auto iter(l.begin()); iter != l.end(); ++iter) {
                    os << *iter;
                    if (*iter != l.back())
                        os << ", ";
                }
                os << "]\n";
            }
        } else
            os << "<empty>";
    }

    // ----------------------- Optional ----------------------- //
    // HashTable(const HashTable& rhs) : _table{vector<list<Key>>(rhs._table)} {}
    // HashTable(HashTable&& rhs) : _table{vector<list<Key>>()}, _size{0}, _bucket{0} {
    //     this->_table.swap(rhs._table);
    //     swap(this->_size, rhs._size);
    //     swap(this->_bucket, rhs._bucket);
    // }

    // ~HashTable() { this->make_empty(); }

    // HashTable& operator=(const HashTable& rhs) {
    //     if (this != &rhs) {
    //         this->make_empty();
    //         this->_table = rhs._table;
    //         this->_size = rhs._size;
    //         this->_bucket = rhs._bucket;
    //     }
    // }

    // HashTable& operator=(HashTable&& rhs) {
    //     if (this != &rhs) {
    //         this->make_empty();
    //         swap(this->_table, rhs._table);
    //         swap(this->_size, rhs._size);
    //         swap(this->_bucket, rhs._bucket);
    //     }
    // }

    // void insert(Key&& key) {
    //     Key k;
    //     swap(k, key);
    //     this->insert(k);
    // }
};
