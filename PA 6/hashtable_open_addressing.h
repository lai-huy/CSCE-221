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

/**
 * @brief Hash Table implementation. This resolves hash collisions through linear probing.
 *
 * @tparam Key key type
 * @tparam Hash hashing function
 */
template <class Key, class Hash = hash<Key>>
class HashTable {
public:
    /**
     * @brief State of each cell
     */
    enum State { INACTIVE, ACTIVE, DELETE };

    /**
     * @brief Individual cells in the hash table
     */
    struct Cell {
        /**
         * @brief Key stored in the cell
         */
        Key _value;

        /**
         * @brief State of the cell
         */
        State _state;

        /**
         * @brief Construct a new Cell object
         */
        Cell() : Cell(Key{}, State::INACTIVE) {}

        /**
         * @brief Construct a new Cell object
         *
         * @param key key value to give the cell
         */
        Cell(const Key& key) : Cell(key, State::ACTIVE) {}

        /**
         * @brief Construct a new Cell object
         *
         * @param key key value to give the cell
         * @param state state of the cell
         */
        Cell(const Key& key, const State& state) : _value{Key(key)}, _state{state} {}

        /**
         * @brief Stream intersion operator
         *
         * @param os ostream to insert into
         * @param cell cell to insert from
         * @return ostream& os
         */
        friend ostream& operator<<(ostream& os, const Cell& cell) { return os << cell._value; }
    };
private:
    /**
     * @brief Internal structure for the hash table
     */
    vector<Cell> _table;

    /**
     * @brief Number of elements in the hash table
     */
    size_t _size;

    /**
     * @brief Number of buckets in the hash table
     */
    size_t _bucket;

    /**
     * @brief The number of occupied cells in the hash table
     */
    size_t _occupied;

    /**
     * @brief Hasher object to hash key values
     */
    Hash _hash;

    /**
     * @brief Primality Test. Source: https://en.wikipedia.org/wiki/Primality_test#C,_C++,_C#_&_D
     *
     * @param num number to determine if its prime
     * @return true if the number is prime
     * @return false otherwise
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
            if (!(num % i))
                return false;
            if (!(num % (i + 2)))
                return false;
        }
        return true;
    }

    /**
     * @brief Retreive the next prime from a number
     *
     * @param num number to find the next prime of
     * @return size_t next prime number
     */
    size_t nextPrime(const size_t& num) const {
        size_t b = (num << 1);
        if (b % 6) {
            b += (6 - (b % 6));
            if (this->isPrime(b - 1))
                return b - 1;
        }

        while (true) {
            if (this->isPrime(b + 1))
                return b + 1;
            if (this->isPrime(b - 1))
                return b - 1;
            b += 6;
        }
        return b;
    }

    /**
     * @brief Rehash the hash table
     */
    void rehash() {
        vector<Key> temp;
        for (const Cell& cell : this->_table)
            if (cell._state == State::ACTIVE)
                temp.emplace_back(cell._value);

        this->make_empty();
        this->_bucket = this->nextPrime(this->_bucket);
        this->_table.resize(this->_bucket, Cell{});
        for (const Key& key : temp)
            this->insert(key);
    }

public:
    /**
     * @brief Construct a new Hash Table object
     */
    HashTable() : HashTable(11) {}

    /**
     * @brief Construct a new Hash Table object
     *
     * @param buckets The number of buckets to construct the table with
     */
    explicit HashTable(size_t buckets) : _table{vector<Cell>(buckets)}, _size{0}, _bucket{buckets}, _occupied{0}, _hash{Hash{}} {}

    /**
     * @brief Determine if the table is empty
     *
     * @return true if the table is empty
     * @return false otherwise
     */
    bool is_empty() const { return !this->_size; }

    /**
     * @brief Determine the number of elements in the hash table
     *
     * @return size_t the number of elemetns in the hash table
     */
    size_t size() const { return this->_size; }

    /**
     * @brief Determine the number of buckets in the hash table
     *
     * @return size_t the number of buckets in the hash table
     */
    size_t table_size() const { return this->_bucket; }

    /**
     * @brief Prevents memory leaks by deallocating the entire table
     */
    void make_empty() {
        this->_table.clear();
        this->_size = 0;
        this->_occupied = 0;
        this->_table.resize(this->_bucket);
    }

    /**
     * @brief Insert a key into the hash table
     *
     * @param key key to insert
     * @return true if insertion was successful
     * @return false otherwise
     */
    bool insert(const Key& key) {
        if (this->contains(key))
            return false;
        Cell& cell = this->_table[this->position(key)];
        if (cell._state == State::INACTIVE)
            ++this->_occupied;
        ++this->_size;
        cell._value = key;
        cell._state = State::ACTIVE;
        if (this->_occupied / static_cast<float>(this->_bucket) > 0.5f)
            this->rehash();
        return true;
    }

    /**
     * @brief Remove a key from the hash table
     *
     * @param key key to remove
     * @return size_t the number of keys removed from the hash table
     */
    size_t remove(const Key& key) {
        for (Cell& cell : this->_table) {
            switch (cell._state) {
            case State::ACTIVE:
                if (cell._value == key) {
                    cell._state = State::DELETE;
                    --this->_size;
                    return 1;
                }
                break;
            default:
                continue;
            }
        }

        return 0;
    }

    /**
     * @brief Determine if the hash table contains a key
     *
     * @param key key to find
     * @return true if the key exists within the hash table
     * @return false otherwise
     */
    bool contains(const Key& key) const {
        for (const Cell& cell : this->_table) {
            switch (cell._state) {
            case State::ACTIVE:
                if (cell._value == key)
                    return true;
                break;
            default:
                continue;
            }
        }

        return false;
    }

    /**
     * @brief Determine the bucket a key should go into
     *
     * @param key key value
     * @return size_t the bucket the key should go into
     */
    size_t position(const Key& key) const {
        size_t index = this->_hash(key) % this->_bucket;
        for (size_t i = 0; i < this->_bucket; ++i) {
            const Cell& cell = this->_table.at(index);
            if (cell._value == key)
                break;
            else if (cell._state == State::INACTIVE)
                break;
            index = (index + 1) % this->_bucket;
        }

        return index;
    }

    /**
     * @brief Print the hash table to an ostream
     *
     * @param os ostream to print to, cout by default
     */
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
    /**
     * @brief Construct a new Hash Table object
     *
     * @param rhs HashTable to copy from
     */
    HashTable(const HashTable& rhs) : _table{rhs._table}, _size{rhs._size}, _bucket{rhs._bucket}, _occupied{rhs._occupied}, _hash{rhs._hash} {}

    /**
     * @brief Construct a new Hash Table object
     *
     * @param rhs HashTable to move from
     */
    HashTable(HashTable&& rhs) : HashTable() {
        this->_table.swap(rhs._table);
        swap(this->_size, rhs._size);
        swap(this->_bucket, rhs._bucket);
        swap(this->_occupied, rhs._occupied);
        swap(this->_hash, rhs._hash);
    }

    /**
     * @brief Destroy the Hash Table object
     */
    ~HashTable() { this->make_empty(); }

    /**
     * @brief Copy assignment operator
     *
     * @param rhs HashTable to copy from
     * @return HashTable& *this
     */
    HashTable& operator=(const HashTable& rhs) {
        if (this != &rhs) {
            this->make_empty();
            this->_table = rhs._table;
            this->_size = rhs._size;
            this->_bucket = rhs._bucket;
            this->_occupied = rhs._occupied;
            this->_hash = rhs._hash;
        }

        return *this;
    }

    /**
     * @brief Move assignment operator
     *
     * @param rhs HashTable to move from
     * @return HashTable& *this
     */
    HashTable& operator=(HashTable&& rhs) {
        if (this != &rhs) {
            this->make_empty();
            this->_table.swap(rhs._table);
            swap(this->_size, rhs._size);
            swap(this->_bucket, rhs._bucket);
            swap(this->_occupied, rhs._occupied);
            swap(this->_hash, rhs._hash);
        }

        return *this;
    }

    /**
     * @brief Move insert a key
     *
     * @param key key to insert
     * @return true if insertion was successful
     * @return false otherwise
     */
    bool insert(Key&& key) {
        Key k{};
        swap(k, key);
        return this->insert(k);
    }
};
