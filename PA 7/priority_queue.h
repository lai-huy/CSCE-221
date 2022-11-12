#pragma once

#include <functional>
#include <deque>
#include <initializer_list>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include "heap.h"

using std::ostream, std::cout;
using std::vector, std::less;
using std::swap, std::move;

/**
 * @brief Priority Queue
 *
 * @tparam Comparable data type the overloads the compairison operators
 * @tparam Container container type that allows random access
 * @tparam less<typename Container::value_type> comparator function, std::less by default
 */
template <class Comparable, class Container = vector<Comparable>, class Compare = less<typename Container::value_type>>
class PriorityQueue {
    /**
     * @brief Comparator function
     */
    Compare _compare;

    /**
     * @brief Container of comparables
     */
    Container _container;

    /**
     * @brief the number of elements in the priority queue
     */
    size_t _size;

public:
    /**
     * @brief Construct a new Priority Queue object
     */
    PriorityQueue() : PriorityQueue(Compare(), Container()) {}

    /**
     * @brief Construct a new Priority Queue object
     *
     * @param compare comparator function
     */
    explicit PriorityQueue(const Compare& compare) : PriorityQueue(compare, Container()) {}

    /**
     * @brief Construct a new Priority Queue object
     *
     * @param container container of values
     */
    explicit PriorityQueue(const Container& container) : PriorityQueue(Compare(), container) {}

    /**
     * @brief Construct a new Priority Queue object
     *
     * @param compare comparator function
     * @param container container of values
     */
    PriorityQueue(const Compare& compare, const Container& container) : _compare{compare}, _container{container}, _size{container.size()} { heapify(this->_container, this->_compare); }

    /**
     * @brief Retreives the first element of the priority queue
     *
     * @return Container::const_reference the first element of the priority queue
     */
    typename Container::const_reference top() const {
        if (!this->_size)
            throw invalid_argument("Priority Queue is empty");
        return heap_get_min(this->_container);
    }

    /**
     * @brief Determine if the priority queue is empty
     *
     * @return true if this is empty
     * @return false otherwise
     */
    bool empty() const { return !this->_size; }

    /**
     * @brief Determine the size of the priority queue
     *
     * @return size_t the number of elements in the priority queue
     */
    size_t size() const { return this->_size; }

    /**
     * @brief Removes all elements from the priority queue
     */
    void make_empty() { this->_container.erase(this->_container.begin() + 1, this->_container.end()); this->_size = 0; }

    /**
     * @brief Pushes a value to the priority queue
     *
     * @param val value to add
     */
    void push(const typename Container::value_type& val) { heap_insert(this->_container, val, this->_compare); ++this->_size; }

    /**
     * @brief Removes the top value from the priority queue
     */
    void pop() {
        if (!this->_size)
            throw invalid_argument("Priority Queue is empty");
        heap_delete_min(this->_container, this->_compare);
        --this->_size;
    }

    /**
     * @brief Print the priority queue
     *
     * @param os ostream to print to, std::cout by default
     */
    void print_queue(ostream& os = cout) const {
        if (this->_size) {
            for (size_t i = 1; i < this->_container.size(); ++i) {
                os << this->_container[i];
                if (i != this->_container.size() - 1)
                    os << ", ";
            }
        } else
            os << "<empty>\n";
    }

    // ----------------------- Optional ----------------------- //
    /**
     * @brief Construct a new Priority Queue object
     *
     * @param rhs Priority queue to copy from
     */
    PriorityQueue(const PriorityQueue& rhs) : PriorityQueue(rhs._compare, rhs._container) {}

    /**
     * @brief Destroy the Priority Queue object
     */
    ~PriorityQueue() { this->make_empty(); }

    /**
     * @brief copy assignment operator
     *
     * @param rhs priority queue to copy from
     * @return PriorityQueue& *this
     */
    PriorityQueue& operator=(const PriorityQueue& rhs) {
        if (this != &rhs) {
            this->make_empty();
            this->_compare = rhs._compare;
            this->_container.resize(rhs._container.size());
            std::copy(rhs._container.begin(), rhs._container.end(), this->_container.begin());
            this->_size = rhs._size;
        }

        return *this;
    }

    /**
     * @brief Construct a new Priority Queue object
     *
     * @param rhs Priority queue to move from
     */
    PriorityQueue(PriorityQueue&& rhs) : _compare{move(rhs._compare)}, _container{move(rhs._container)}, _size{move(rhs._size)} {
        heapify(this->_container, this->_compare);
    }

    /**
     * @brief Move assignment operator
     *
     * @param rhs Priority queue to move from
     * @return PriorityQueue& *this
     */
    PriorityQueue& operator=(PriorityQueue&& rhs) {
        if (this != &rhs) {
            this->make_empty();
            this->_compare = rhs._compare;
            this->_container.resize(rhs._container.size());
            std::swap_ranges(rhs._container.begin(), rhs._container.end(), this->_container.begin());
            swap(this->_size, rhs._size);
        }

        return *this;
    }

    /**
     * @brief Move push a value to the priority queue
     *
     * @param val value to move from
     */
    void push(typename Container::value_type&& val) {
        typename Container::value_type v{};
        swap(v, val);
        this->push(v);
    }
};
