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

template <class Comparable, class Container = vector<Comparable>, class Compare = less<typename Container::value_type>>
class PriorityQueue {
    Compare _compare;
    Container _container;

public:
    PriorityQueue() : PriorityQueue(Compare(), Container()) {}
    explicit PriorityQueue(const Compare& compare) : PriorityQueue(compare, Container()) {}
    explicit PriorityQueue(const Container& container) : PriorityQueue(Compare(), container) {}
    PriorityQueue(const Compare& compare, const Container& container) : _compare{Compare(compare)}, _container{Container(container)} { heapify(this->_container, this->_compare); }

    typename Container::const_reference top() const { return heap_get_min(this->_container); }

    bool empty() const { return this->_container.empty(); }
    size_t size() const { return this->_container.size(); }

    void make_empty() { this->_container.clear(); }
    void push(const typename Container::value_type& val) { heap_insert(this->_container, val, this->_compare); }
    void pop() { heap_delete_min(this->_container, this->_compare); }

    void print_queue(ostream& os = cout) const {
        if (this->_container.size()) {
            for (size_t i = 0; i < this->_container.size(); ++i) {
                os << this->_container[i];
                if (i != this->_container.size() - 1)
                    os << ", ";
            }
        } else
            os << "<empty>\n";
    }

    // ----------------------- Optional ----------------------- //
    PriorityQueue(const PriorityQueue&) = default;
    ~PriorityQueue() = default;
    PriorityQueue& operator=(const PriorityQueue& rhs) = default;

    // PriorityQueue(const Compare& compare, Container&& container);
    // PriorityQueue(PriorityQueue&& rhs);
    // PriorityQueue& operator=(PriorityQueue&& rhs);
    // void push(typename Container::value_type&& val);
};
