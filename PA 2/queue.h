#pragma once

#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <utility>
#include "doubly_linked_list.h"

using std::move, std::swap;

/**
 * @brief First in First out
 *
 * @tparam Object data type stored in the queue
 */
template <typename Object>
class Queue {
private:
    /**
     * @brief Internal structure of the queue.
     */
    DoublyLinkedList<Object> _data;
public:
    /**
     * @brief Construct a new Queue object
     */
    Queue() : _data{DoublyLinkedList<Object>()} {}

    /**
     * @brief Construct a new Queue object
     *
     * @param rhs Queue to copy from
     */
    Queue(const Queue& rhs) : _data{DoublyLinkedList<Object>(rhs._data)} {}

    /**
     * @brief Destroy the Queue object
     */
    ~Queue() { this->_data.clear(); }

    /**
     * @brief Copy assignment operator
     *
     * @param rhs queue to copy from
     * @return Queue& *this
     */
    Queue& operator=(const Queue& rhs) {
        if (this != &rhs) {
            this->_data.clear();
            this->_data.copy(rhs._data);
        }

        return *this;
    }

    /**
     * @brief Add an object to the back of the queue
     *
     * @param obj Object to add
     */
    void enqueue(const Object& obj) { this->_data.insert(this->_data.size(), obj); }

    /**
     * @brief Remove and return the Object at the front of the queue
     *
     * @return Object at the front of the queue
     */
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

    /**
     * @brief Retreives the object at the front of the queue
     *
     * @return Object& at the front of the queue
     */
    Object& front() {
        try {
            return this->_data[0];
        } catch (const out_of_range& err) {
            throw out_of_range("Queue is empty");
        }
    }

    // ----------------------- Optional ----------------------- //
    /**
     * @brief Construct a new Queue object
     *
     * @param rhs queue to move from
     */
    Queue(Queue&& rhs) : _data{DoublyLinkedList(move(rhs._data))} {}

    /**
     * @brief move assignment operator
     *
     * @param rhs queue to move from
     * @return Queue& *this
     */
    Queue& operator=(Queue&& rhs) {
        if (this != &rhs) {
            this->_data.clear();
            this->_data = move(rhs._data);
        }

        return *this;
    }

    /**
     * @brief move enqueue an object
     *
     * @param value Object to enqueue
     */
    void enqueue(Object&& value) {
        Object o{};
        swap(o, value);
        this->_data.insert(this->_data.size(), o);
    }

    /**
     * @brief Reterives the object at the front of the queue
     *
     * @return const Object& at the front of the queue
     */
    const Object& front() const {
        try {
            return this->_data[0];
        } catch (const out_of_range& err) {
            throw out_of_range("Queue is empty");
        }
    }

    /**
     * @brief returns the size of the queue
     *
     * @return size_t size of the queue
     */
    size_t size() const { return this->_data.size(); }
};
