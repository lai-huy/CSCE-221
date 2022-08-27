#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <utility>

using std::out_of_range;

template <typename Object>
class ArrayList {
private:
    size_t _size;
    size_t _capacity;
public:
    Object* _data;

    ArrayList() : _size{0}, _capacity{1}, _data{new Object[1]} {}

    explicit ArrayList(size_t size) : _size{size}, _capacity{1}, _data{nullptr} {
        while (this->_size > this->_capacity)
            this->_capacity *= 2;

        this->_data = new Object[this->_capacity]{};
    }

    ArrayList(const ArrayList& rhs) : _size{rhs._size}, _capacity{rhs._capacity}, _data{nullptr} {
        this->_data = new Object[this->_capacity]{};
        for (size_t i = 0; i < this->_capacity; ++i)
            this->_data[i] = i < this->_size ? rhs._data[i] : Object();
    }

    ~ArrayList() {
        if (this->_data)
            delete[] this->_data;

        this->_size = 0;
        this->_capacity = 1;
        this->_data = nullptr;
    }

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

    size_t size() const {
        return this->_size;
    }

    size_t capacity() const {
        return this->_capacity;
    }

    Object& operator[](size_t index) {
        if (index >= this->_size)
            throw out_of_range("Index out of bounds");

        return this->_data[index];
    }

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

        if (!index) {
            for (size_t i = this->_size - 1; i < this->_size; --i)
                this->_data[i + 1] = this->_data[i];
        } else if (this->_size)
            for (size_t i = this->_size - 1; i >= index; --i)
                this->_data[i + 1] = this->_data[i];

        ++this->_size;
        this->_data[index] = obj;
    }

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

    // OPTIONAL
    // ArrayList(ArrayList&& rhs);
    // ArrayList& operator=(ArrayList&& rhs);
    // void insert(size_t index, Object&& obj);

    // const Object& operator[](size_t index) const {
    //     if (index >= this->_size)
    //         throw out_of_range("Index out of bounds");
    //     return this->_data[index];
    // }

    // Object* begin() {
    //     return this->_size ? &this->_data[0] : nullptr;
    // }

    // const Object* begin() const {
    //     return this->_size ? &this->_data[0] : nullptr;
    // }

    // Object* end() {
    //     return this->_size ? &this->_data[this->_size - 1] : nullptr;
    // }

    // const Object* end() const {
    //     return this->_size ? &this->_data[this->_size - 1] : nullptr;
    // }
};

#endif  // ARRAY_LIST_H