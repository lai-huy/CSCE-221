#pragma once

#include <cstddef>
#include <stdexcept>
#include <iostream>

using std::cout;

/**
 * @brief An Abstract Data Type that holds a collection of items
 *
 * @tparam Object data type this collection will hold
 */
template <typename Object>
class Collection {
public:
    /**
     * @brief size of this collecition
     */
    size_t _size;

    /**
     * @brief The current capacity of the underlying dynamic array
     */
    size_t _capacity;

    /**
     * @brief The underlying dynamic array holding all the elements
     */
    Object* _data;

    /**
     * @brief Construct a new Collection object
     */
    Collection() : _size{0}, _capacity{1}, _data{nullptr} {}

    /**
     * @brief Destroy the Collection object
     */
    ~Collection() {
        this->make_empty();
    }

    /**
     * @brief Construct a new Collection object
     *
     * @param rhs Collection to copy from
     */
    Collection(const Collection& rhs) : _size{rhs._size}, _capacity{rhs._capacity}, _data{nullptr} {
        this->_data = new Object[this->_capacity];
        for (size_t i = 0; i < this->_capacity; ++i)
            this->_data[i] = i < this->_size ? rhs._data[i] : 0;
    }

    /**
     * @brief Copy assignment operator
     *
     * @param rhs Collection to copy from
     * @return Collection& *this
     */
    Collection& operator=(const Collection& rhs) {
        if (this != &rhs) {
            this->make_empty();

            this->_data = new Object[this->_capacity];
            for (size_t i = 0; i < this->_capacity; ++i)
                this->_data[i] = i < this->_size ? rhs._data[i] : 0;
        }

        return *this;
    }

    /**
     * @brief determines the size of this collection
     *
     * @return size_t size of the collection
     */
    size_t size() const {
        return this->_size;
    }

    /**
     * @brief Determines if this collection is empty
     *
     * @return true if this collection is empty
     * @return false otherwise
     */
    bool is_empty() const {
        return !this->_size;
    }

    /**
     * @brief Empties the collection of contents
     */
    void make_empty() {
        if (this->_data)
            delete[] this->_data;

        this->_size = 0;
        this->_capacity = 1;
        this->_data = nullptr;
    }

    /**
     * @brief Inserts an object at the end of the collection
     *
     * @param obj Object to insert
     */
    void insert(const Object& obj) {
        // cout << "list.insert(" << std::to_string(obj) << ");\n";

        if (this->_size + 1 > this->_capacity) {
            int* temp = this->_data;
            this->_capacity *= 2;
            this->_data = new Object[this->_capacity];

            for (size_t i = 0; i < this->_capacity; ++i)
                this->_data[i] = i < this->_size ? temp[i] : 0;

            delete[] temp;
        }

        if (!this->_data)
            this->_data = new Object[this->_capacity];
        this->_data[this->_size++] = obj;
    }

    /**
     * @brief Removes an object from the collection
     *
     * @param obj object to remove
     */
    void remove(const Object& obj) {
        // cout << "list.remove(" << std::to_string(obj) << ");\n";

        size_t index = static_cast<size_t>(-1);
        for (size_t i = 0; i < this->_size; ++i)
            if (this->_data[i] == obj) {
                index = i;
                break;
            }

        if (index == static_cast<size_t>(-1))
            return;

        --this->_size;
        for (size_t i = index; i < this->_size; ++i)
            this->_data[i] = this->_data[i + 1];
    }

    /**
     * @brief Determines if this collection contains an object
     *
     * @param obj object to find
     * @return true is this collection contains the object
     * @return false otherwise
     */
    bool contains(const Object& obj) const {
        // cout << "list.contains(" << std::to_string(obj) << ");\n";

        for (size_t i = 0; i < this->_size; ++i) {
            if (this->_data[i] == obj)
                return true;
        }

        return false;
    }
};
