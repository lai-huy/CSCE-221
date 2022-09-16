#pragma once

#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <utility>
#include "doubly_linked_list.h"

template <typename Object>
class Queue {
private:
    DoublyLinkedList<Object> _data;
public:
    Queue() : _data{DoublyLinkedList<Object>()} {}

    Queue(const Queue& rhs) : _data{DoublyLinkedList<Object>(rhs._data)} {}

    ~Queue() {
        this->_data.clear();
    }

    Queue& operator=(const Queue& rhs) {
        if (this != &rhs) {
            this->_data.clear();
            this->_data.copy(rhs._data);
        }

        return *this;
    }

    void enqueue(const Object& obj) {
        this->_data.insert(this->_data.size(), obj);
    }

    Object dequeue() {
        Object val;
        try {
            val = this->_data[0];
        } catch (const out_of_range& err) {
            throw out_of_range("Queue underflow");
        }

        this->_data.remove(0);
        return val;
    }

    Object& front() {
        try {
            return this->_data[0];
        } catch (const out_of_range& err) {
            throw out_of_range("Queue is empty");
        }
    }

    // ----------------------- Optional ----------------------- //
    // Queue(Queue&&)
    // Queue& operator=(Queue&&)

    void enqueue(Object&& obj) {
        this->_data.insert(obj);
    }

    const Object& front() const {
        try {
            return this->_data[0];
        } catch (const out_of_range& err) {
            throw out_of_range("Queue is empty");
        }
    }

    size_t size() const {
        return this->_data.size();
    }
};
