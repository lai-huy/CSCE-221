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
    PriorityQueue(const Compare& compare, const Container& container) : _compare{Compare(compare)}, _container{Container(container)} {}

    typename Container::const_reference top() const;

    bool empty() const;
    size_t size() const;

    void make_empty();
    void push(const typename Container::value_type& val);
    void pop();

    void print_queue(ostream& os = cout) const;

    // ----------------------- Optional ----------------------- //
    PriorityQueue(const PriorityQueue&) = default;
    ~PriorityQueue() = default;
    PriorityQueue& operator=(const PriorityQueue& rhs) = default;

    // PriorityQueue(const Compare& compare, Container&& container);
    // PriorityQueue(PriorityQueue&& rhs);
    // PriorityQueue& operator=(PriorityQueue&& rhs);
    // void push(typename Container::value_type&&);
};
