#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <utility>

using std::out_of_range;

/**
 * @brief Array List
 *
 * @tparam Object
 */
template <typename Object>
class ArrayList {
private:
    /**
     * @brief The current size of this array list
     */
    size_t _size;

    /**
     * @brief The current capacity of this array list
     */
    size_t _capacity;

public:
    /**
     * @brief Internal pointer to underlying data
     */
    Object* _data;

    /**
     * @brief Construct a new Array List object
     */
    ArrayList() : _size{0}, _capacity{1}, _data{nullptr} {}

    /**
     * @brief Construct a new Array List object
     *
     * @param size size of the array list
     */
    explicit ArrayList(size_t size) : _size{size}, _capacity{1}, _data{nullptr} {
        while (this->_size > this->_capacity)
            this->_capacity *= 2;

        this->_data = new Object[this->_capacity]{};
    }

    /**
     * @brief Construct a new Array List object
     *
     * @param rhs ArrayList to copy from
     */
    ArrayList(const ArrayList& rhs) : _size{rhs._size}, _capacity{rhs._capacity}, _data{nullptr} {
        this->_data = new Object[this->_capacity]{};
        for (size_t i = 0; i < this->_capacity; ++i)
            this->_data[i] = i < this->_size ? rhs._data[i] : Object();
    }

    /**
     * @brief Destroy the Array List object
     */
    ~ArrayList() {
        if (this->_data)
            delete[] this->_data;

        this->_size = 0;
        this->_capacity = 1;
        this->_data = nullptr;
    }

    /**
     * @brief Copy assignment operator
     *
     * @param rhs ArrayList to copy from
     * @return ArrayList& *this
     */
    ArrayList& operator=(const ArrayList& rhs) {
        if (this != &rhs) {
            if (this->_data)
                delete[] this->_data;

            this->_size = rhs.size();
            this->_capacity = rhs.capacity();
            this->_data = new Object[this->_capacity]{};

            for (size_t i = 0; i < this->_capacity; ++i)
                this->_data[i] = i < this->_size ? rhs._data[i] : Object();
        }

        return *this;
    }

    /**
     * @brief Determine the size of the Array List
     *
     * @return size_t this->_size;
     */
    size_t size() const {
        return this->_size;
    }

    /**
     * @brief Determine the capacity of the Array List
     *
     * @return size_t this->_size;
     */
    size_t capacity() const {
        return this->_capacity;
    }

    /**
     * @brief Access a specific element in this array list
     *
     * @param index index into the list
     * @return Object& reference to the element at index
     */
    Object& operator[](size_t index) {
        if (index >= this->_size)
            throw out_of_range("Index out of bounds");

        return this->_data[index];
    }

    /**
     * @brief Insert an element at the specified index
     *
     * @param index where to insert
     * @param obj   what to insert
     */
    void insert(size_t index, const Object& obj) {
        if (index > this->_size)
            throw out_of_range("Index out of bounds");

        if (this->_size + 1 > this->_capacity) {
            this->_capacity *= 2;
            Object* temp = this->_data;
            this->_data = new Object[this->_capacity]{};

            for (size_t i = 0; i < this->_capacity; ++i)
                this->_data[i] = i < this->_size ? temp[i] : Object();

            delete[] temp;
        }

        if (!this->_data)
            this->_data = new Object[this->_capacity]{};

        if (!index) {
            for (size_t i = this->_size - 1; i < this->_size; --i)
                this->_data[i + 1] = this->_data[i];
        } else if (this->_size)
            for (size_t i = this->_size - 1; i >= index; --i)
                this->_data[i + 1] = this->_data[i];

        ++this->_size;
        this->_data[index] = obj;
    }

    /**
     * @brief Remove an element from the list at a specified index
     *
     * @param index where to remove
     */
    void remove(size_t index) {
        if (index >= this->_size)
            throw out_of_range("Index out of bounds");

        if (index == this->_size - 1)
            this->_data[index] = Object();
        else
            for (size_t i = index; i < this->_size; ++i)
                this->_data[i] = this->_data[i + 1];

        --this->_size;
    }

    /**
     * @brief Construct a new Array List object
     *
     * @param rhs ArrayList to copy from
     */
    ArrayList(ArrayList&& rhs) : _size{rhs._size}, _capacity{rhs._capacity}, _data{rhs._data} {
        rhs._size = 0;
        rhs._capacity = 0;
        rhs._data = nullptr;
    }

    /**
     * @brief Move assignment operator
     *
     * @param rhs ArrayList to copy from
     * @return ArrayList& *this
     */
    ArrayList& operator=(ArrayList&& rhs) {
        if (this != &rhs) {
            delete[] this->_data;

            this->_size = rhs._size;
            this->_capacity = rhs._capacity;
            this->_data = rhs._data;

            rhs._size = 0;
            rhs._capacity = 1;
            rhs._data = nullptr;
        }
    }

    /**
     * @brief insert the given (rvalue) object at the specified index
     *
     * @param index index to insert
     * @param obj object to insert
     */
    void insert(size_t index, Object&& obj) {
        if (index > this->_size)
            throw out_of_range("Index out of bounds");

        if (this->_size + 1 > this->_capacity) {
            this->_capacity *= 2;
            Object* temp = this->_data;
            this->_data = new Object[this->_capacity]{};

            for (size_t i = 0; i < this->_capacity; ++i)
                this->_data[i] = i < this->_size ? temp[i] : Object();

            delete[] temp;
        }

        if (!this->_data)
            this->_data = new Object[this->_capacity]{};

        if (!index) {
            for (size_t i = this->_size - 1; i < this->_size; --i)
                this->_data[i + 1] = this->_data[i];
        } else if (this->_size)
            for (size_t i = this->_size - 1; i >= index; --i)
                this->_data[i + 1] = this->_data[i];

        ++this->_size;
        this->_data[index] = obj;
    }

    /**
     * @brief returns a constant reference to the element at the specified index
     *
     * @param index index of the element to return
     * @return const Object& referenced element at the index
     */
    const Object& operator[](size_t index) const {
        if (index >= this->_size)
            throw out_of_range("Index out of bounds");
        return this->_data[index];
    }

    /**
     * @brief returns a pointer to the beginning of the list
     *
     * @return Object* a pointer to the beginning of the list
     */
    Object* begin() {
        return this->_size ? &this->_data[0] : nullptr;
    }

    /**
     * @brief returns a pointer to the beginning of the list
     *
     * @return const Object* returns a pointer to the beginning of the list
     */
    const Object* begin() const {
        return this->_size ? &this->_data[0] : nullptr;
    }

    /**
     * @brief returns a pointer to the end of the list
     *
     * @return Object* a pointer to the beginning of the list
     */
    Object* end() {
        return this->_size ? &this->_data[this->_size - 1] : nullptr;
    }

    /**
     * @brief returns a pointer to the beginning of the list
     *
     * @return const Object* a pointer to the beginning of the list
     */
    const Object* end() const {
        return this->_size ? &this->_data[this->_size - 1] : nullptr;
    }
};

#endif  // ARRAY_LIST_H