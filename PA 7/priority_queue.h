#pragma once

#include <functional>
#include <vector>
#include "heap.h"

template <class Comparable, class Container=std::vector<Comparable>, class Compare=std::less<typename Container::value_type>>
class PriorityQueue {
    Compare compare;
    Container container;

    // TODO(student): implement PriorityQueue
};
