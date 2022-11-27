#pragma once

#include <functional>
#include <iostream>
#include <list>
#include <sstream>
#include <stdexcept>
#include <vector>

using std::ostream, std::cout;
using std::hash, std::find, std::swap;
using std::vector, std::list;
using std::out_of_range, std::invalid_argument;
using std::numeric_limits;

/**
 * @brief Hash Table implementation. This resolves hash collisions through seperate chaining.
 *
 * @tparam Key key type
 * @tparam Hash hashing function
 */
template <class Key, class Hash = hash<Key>>
class HashTable {
private:
    /**
     * @brief Internal structure for the hash table
     */
    vector<list<Key>> _table;

    /**
     * @brief The number of elements in the table
     */
    size_t _size;

    /**
     * @brief Number of buckets in the hash table
     */
    size_t _bucket;

    /**
     * @brief Max load factor
     */
    float _mlf;

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
            if (num % i == 0)
                return false;
            if (num % (i + 2) == 0)
                return false;
        }
        return true;
    }

    /**
     * @brief Determine the next prime from a number
     *
     * @param num number to find the next prime of
     * @return size_t the next prime
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
     * @brief Copy from another HashTable
     *
     * @param rhs HashTable to copy from
     */
    void copy(const HashTable& rhs) {
        this->_table.resize(rhs._table.size());
        for (size_t i = 0; i < this->_table.size(); ++i)
            this->_table.at(i) = list(rhs._table.at(i).begin(), rhs._table.at(i).end());
        this->_size = rhs._size;
        this->_bucket = rhs._bucket;
        this->_mlf = rhs._mlf;
        this->_hash = rhs._hash;
    }

public:
    /**
     * @brief Construct a new Hash Table object
     */
    HashTable() : HashTable(11) {}

    /**
     * @brief Construct a new Hash Table object
     *
     * @param size the number of buckets
     */
    explicit HashTable(size_t size) : _table{vector<list<Key>>(size)}, _size{0}, _bucket{size}, _mlf{1.0f}, _hash{Hash{}} {
        if (!size)
            throw invalid_argument("Initial size of table canont be zero.");
    }

    /**
     * @brief Determine if the HashTable is empty
     *
     * @return true if the table is empty
     * @return false otherwise
     */
    bool is_empty() const { return !this->_size; }

    /**
     * @brief Determine the number of elemnts in the hash table
     *
     * @return size_t the number of elements in the hash table
     */
    size_t size() const { return this->_size; }

    /**
     * @brief Prevents memory leaks by deallocating the entire hash table
     */
    void make_empty() {
        for (list<Key>& list : this->_table)
            list.clear();
        this->_table.clear();
        this->_table.resize(this->_bucket);
        this->_size = 0;
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
        size_t bucket = this->bucket(key);
        this->_table.at(bucket).push_back(key);
        ++this->_size;
        if (this->load_factor() > this->max_load_factor()) {
            size_t size = this->nextPrime(this->_bucket);
            this->rehash(size);
        }
        return true;
    }

    /**
     * @brief Remove a key from the hash table
     *
     * @param key key to remove
     * @return size_t the number of keys removed from the hash table
     */
    size_t remove(const Key& key) {
        if (!this->contains(key))
            return 0;
        size_t index = this->bucket(key);
        this->_table.at(index).remove(key);
        --this->_size;
        return 1;
    }

    /**
     * @brief Determine if the hash table contains a key
     *
     * @param key key to find
     * @return true if the key exists within the hash table
     * @return false otherwise
     */
    bool contains(const Key& key) const {
        list<Key> list = this->_table.at(this->bucket(key));
        return find(list.begin(), list.end(), key) != list.end();
    }

    /**
     * @brief Determine the number of buckets the hash table has
     *
     * @return size_t the number of buckets the hash table has
     */
    size_t bucket_count() const { return this->_bucket; }

    /**
     * @brief Determines the number of elements in a specified bucket
     *
     * @param index bucket
     * @return size_t the number of elements in a specified bucket
     */
    size_t bucket_size(size_t index) const {
        if (index >= this->_bucket)
            throw out_of_range("Invalid bucket");
        return this->_table.at(index).size();
    }

    /**
     * @brief Determines which bucket a key will go into
     *
     * @param key key value
     * @return size_t the bucket the key goes into
     */
    size_t bucket(const Key& key) const { return this->_hash(key) % this->_bucket; }

    /**
     * @brief Determine the load factor of the table
     *
     * @return float load factor of the table
     */
    float load_factor() const { return this->_size / static_cast<float>(this->_bucket); }

    /**
     * @brief Determine the max load factor of the table
     *
     * @return float the max load factor of the table
     */
    float max_load_factor() const { return this->_mlf; }

    /**
     * @brief Set the max load a factor and cause a rehash if needed
     *
     * @param lf new max load factor
     */
    void max_load_factor(float lf) {
        if (lf <= .0f)
            throw invalid_argument("new max load factor is negative");
        if (lf != lf)
            throw invalid_argument("new max load factor is not a number");
        if (lf == numeric_limits<float>::infinity())
            throw invalid_argument("new max load factor is infinite");
        this->_mlf = lf;
        if (this->load_factor() > this->_mlf)
            this->rehash(this->nextPrime(static_cast<size_t>(this->_size / this->_mlf) >> 1));
    }

    /**
     * @brief Rehash the hash table to the specified number of buckets
     *
     * @param bucket the number of buckets to rehash to
     */
    void rehash(size_t bucket) {
        if (bucket != this->_bucket) {
            this->_bucket = this->_size / static_cast<float>(bucket) > this->_mlf ? this->nextPrime(static_cast<size_t>(this->_size / this->_mlf) >> 1) : bucket;
            vector<Key> temp;
            for (const list<Key>& l : this->_table)
                temp.insert(temp.end(), l.cbegin(), l.cend());
            this->make_empty();
            for (const Key& key : temp)
                this->insert(key);
        }
    }

    /**
     * @brief Print the table
     *
     * @param os ostream to print to, cout by default
     */
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
            os << "<empty>\n";
    }

    // ----------------------- Optional ----------------------- //
    /**
     * @brief Construct a new Hash Table object
     *
     * @param rhs HashTable to copy form
     */
    HashTable(const HashTable& rhs) : HashTable() { this->copy(rhs); }

    /**
     * @brief Construct a new Hash Table object
     *
     * @param rhs HashTable to move from
     */
    HashTable(HashTable&& rhs) : HashTable() {
        this->_table.swap(rhs._table);
        swap(this->_size, rhs._size);
        swap(this->_bucket, rhs._bucket);
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
            this->copy(rhs);
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
            swap(this->_hash, rhs._hash);
        }

        return *this;
    }

    /**
     * @brief Move insert
     *
     * @param key key to insert
     * @return true if insertion was successful
     * @return false otherwise
     */
    bool insert(Key&& key) {
        Key k;
        swap(k, key);
        return this->insert(k);
    }
};
