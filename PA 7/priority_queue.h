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

template <class Comparable, class Container = vector<Comparable>, class Compare = less<typename Container::value_type>>
class PriorityQueue {
    Compare _compare;
    Container _container;
    size_t _size;

public:
    PriorityQueue() : PriorityQueue(Compare(), Container()) {}
    explicit PriorityQueue(const Compare& compare) : PriorityQueue(compare, Container()) {}
    explicit PriorityQueue(const Container& container) : PriorityQueue(Compare(), container) {}
    PriorityQueue(const Compare& compare, const Container& container) : _compare{compare}, _container{container}, _size{container.size()} { heapify(this->_container, this->_compare); }

    typename Container::const_reference top() const { return heap_get_min(this->_container); }

    bool empty() const { return !this->_size; }
    size_t size() const { return this->_size; }

    void make_empty() { this->_container.erase(this->_container.begin() + 1, this->_container.end()); this->_size = 0; }
    void push(const typename Container::value_type& val) { heap_insert(this->_container, val, this->_compare); ++this->_size; }
    void pop() { heap_delete_min(this->_container, this->_compare); --this->_size; }

    void print_queue(ostream& os = cout) const {
        if (this->_size) {
            for (typename Container::const_iterator iter = this->_container.begin() + 1; iter != this->_container.end(); ++iter) {
                os << *iter;
                if (iter != this->_container.end() - 1)
                    os << ", ";
            }
        } else
            os << "<empty>\n";
    }

    // ----------------------- Optional ----------------------- //
    PriorityQueue(const PriorityQueue& rhs) : PriorityQueue(rhs._compare, rhs._container) {}
    ~PriorityQueue() { this->make_empty(); }
    PriorityQueue& operator=(const PriorityQueue& rhs) {
        if (this != &rhs) {
            this->make_empty();
            this->_compare = rhs._compare;
            std::copy(rhs._container.begin(), rhs._container.end(), this->_container.begin());
            this->_size = rhs._size;
        }

        return *this;
    }

    PriorityQueue(const Compare& compare, Container&& container) : _compare{compare}, _container{Container()}, _size{container.size()} {
        swap(this->_container, container);
        heapify(this->_container, this->_compare);
    }

    PriorityQueue(PriorityQueue&& rhs) : _compare{move(rhs._compare)}, _container{move(rhs._container)}, _size{move(rhs._size)} {
        heapify(this->_container, this->_compare);
    }

    PriorityQueue& operator=(PriorityQueue&& rhs) {
        if (this != &rhs) {
            this->make_empty();
            this->_compare = rhs._compare;
            swap(this->_container, rhs._container);
            swap(this->_size, rhs._size);
        }

        return *this;
    }

    void push(typename Container::value_type&& val) {
        typename Container::value_type v{};
        swap(v, val);
        this->push(v);
    }
};
