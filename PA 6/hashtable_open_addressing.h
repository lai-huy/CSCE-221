#pragma once

#include <functional>
#include <iostream>
#include <list>
#include <sstream>
#include <stdexcept>
#include <vector>

using std::ostream, std::cout;
using std::hash, std::swap;
using std::vector;
using std::find;

template <class Key, class Hash = hash<Key>>
class HashTable {
public:
    enum State { INACTIVE, ACTIVE, DELETE };
    struct Cell {
        Key _value;
        State _state;
        Cell() : Cell(Key(), State::INACTIVE) {}
        Cell(const Key& key) : Cell(key, State::ACTIVE) {}
        Cell(const Key& key, const State& state) : _value{Key(key)}, _state{state} {}
        Cell(const Cell& rhs) : Cell(rhs._value, rhs._state) {}

        Cell& operator=(const Cell& rhs) {
            if (this != &rhs) {
                this->_value = rhs._value;
                this->_state = rhs._state;
            }

            return *this;
        }

        friend ostream& operator<<(ostream& os, const Cell& cell) { return os << cell._value; }
    };
private:
    vector<Cell> _table;
    size_t _size;
    size_t _bucket;

    /**
     * @brief Primality Test. Source: https://en.wikipedia.org/wiki/Primality_test#C,_C++,_C#_&_D
     *
     * @param num
     * @return true
     * @return false
     */
    bool isPrime(const size_t& num) const {
        if (num < 2)
            return false;
        if (num < 4)
            return true;
        if (!(num % 2))
            return false;
        if (!(num % 3))
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

    void rehash() {
        this->_bucket = this->nextPrime(2 * this->_bucket + 1);
        vector<Key> temp;
        for (const Cell& cell : this->_table) {
            if (cell._state != State::ACTIVE)
                continue;
            temp.push_back(cell._value);
        }

        this->make_empty();
        for (const Key& key : temp)
            this->insert(key);
    }

public:
    HashTable() : HashTable(11) {}
    explicit HashTable(size_t buckets) : _table{vector<Cell>(buckets)}, _size{0}, _bucket{buckets} {}

    bool is_empty() const { return !this->_size; }
    size_t size() const { return this->_size; }
    size_t table_size() const { return this->_bucket; }

    void make_empty() {
        this->_table.clear();
        this->_size = 0;
        this->_table.resize(this->_bucket);
    }

    bool insert(const Key& key) {
        if (this->contains(key))
            return false;
        Cell& cell = this->_table.at(this->position(key));
        cell._state = State::ACTIVE;
        cell._value = key;
        ++this->_size;
        if (this->_size / static_cast<float>(this->_bucket) > 0.5f)
            this->rehash();
        return true;
    }

    size_t remove(const Key& key) {
        for (typename vector<Cell>::iterator it = this->_table.begin(); it != this->_table.end(); ++it) {
            switch (it->_state) {
            case State::DELETE:
            case State::INACTIVE:
                continue;
            default:
                if (it->_value == key) {
                    it->_state = State::DELETE;
                    --this->_size;
                    return 1;
                }
            }
        }

        return 0;
    }

    bool contains(const Key& key) const {
        for (typename vector<Cell>::const_iterator it = this->_table.begin(); it != this->_table.end(); ++it) {
            switch (it->_state) {
            case State::INACTIVE:
            case State::DELETE:
                continue;
            default:
                if (it->_value == key)
                    return true;
                break;
            }
        }
        return false;
    }

    size_t position(const Key& key) const {
        size_t index = Hash()(key) % this->_table.size();
        size_t i = 1;
        Cell cell = this->_table.at(index);
        while (cell._state != State::INACTIVE) {
            if (cell._state == State::DELETE && cell._value == key)
                break;
            index = (Hash()(key) + i * i) % this->_table.size();
            cell = this->_table.at(index);
            ++i;
        }

        return index;
    }

    void print_table(ostream& os = cout) const {
        if (this->_size) {
            for (size_t i = 0; i < this->_table.size(); ++i) {
                const Cell& cell = this->_table.at(i);
                if (cell._state != State::ACTIVE)
                    continue;
                os << i << ": " << cell._value << "\n";
            }
        } else
            os << "<empty>\n";
    }

    // ----------------------- Optional ----------------------- //
    HashTable(const HashTable& rhs) : _table{rhs._table}, _size{rhs._size}, _bucket{rhs._bucket} {}

    HashTable(HashTable&& rhs) : HashTable() {
        this->_table.swap(rhs._table);
        swap(this->_size, rhs._size);
        swap(this->_bucket, rhs._bucket);
    }

    ~HashTable() { this->make_empty(); }

    HashTable& operator=(const HashTable& rhs) {
        if (this != &rhs) {
            this->make_empty();
            this->_table = rhs._table;
            this->_size = rhs._size;
            this->_bucket = rhs._bucket;
        }

        return *this;
    }

    HashTable& operator=(HashTable&& rhs) {
        if (this != &rhs) {
            this->make_empty();
            this->_table.swap(rhs._table);
            swap(this->_size, rhs._size);
            swap(this->_bucket, rhs._bucket);
        }

        return *this;
    }

    bool insert(Key&& key) {
        Key k{};
        swap(k, key);
        return this->insert(k);
    }
};
