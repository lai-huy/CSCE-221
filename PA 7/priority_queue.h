#pragma once

#include <functional>
#include <vector>
#include <iostream>
#include "heap.h"

using std::ostream, std::cout;

template <class Comparable, class Container = std::vector<Comparable>, class Compare = std::less<typename Container::value_type>>
class PriorityQueue {
    Compare compare;
    Container container;

public:
    PriorityQueue();
    explicit PriorityQueue(const Compare& compare);
    explicit PriorityQueue(const Container& container);
    PriorityQueue(const Compare& compare, const Container& container);

    typename Container::const_reference top() const;

    bool empty() const;
    size_t size() const;

    void make_empty();
    void push(const typename Container::value_type& val);

    void print_queue(ostream& os = cout) cosnt;

    // ----------------------- Optional ----------------------- //
    // PriorityQueue(const PriorityQueue&);
    // ~PriorityQueue();
    // PriorityQueue& operator=(const PriorityQueue& rhs);

    // PriorityQueue(const Compare& compare, Container&& container);
    // PriorityQueue(PriorityQueue&& rhs);
    // PriorityQueue& operator=(PriorityQueue&& rhs);
    // void push(typename Container::value_type&&);
};
