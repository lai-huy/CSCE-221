#pragma once

#include <functional>
#include <deque>
#include <initializer_list>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>

using std::less, std::swap;
using std::cout;
using std::invalid_argument;
using std::make_heap, std::push_heap, std::pop_heap;
using std::reverse;

/**
 * @brief Pushes the value at the specicified index down the heap according to the specified comparator
 *
 * @tparam Container container class
 * @tparam less<typename Container::value_type> comparator
 * @param container pointer to the container to edit
 * @param heap_size size of the heap
 * @param parent index to push down
 * @param compare comparator function
 */
template <class Container, class Compare = less<typename Container::value_type>>
void pushDown(Container* container, const size_t& heap_size, const size_t& parent, Compare compare = less<typename Container::value_type>{}) {
    size_t left = parent << 1, right = left + 1, index = parent;

    if (left < heap_size && compare(container->at(left), container->at(parent)))
        index = left;
    if (right < heap_size && compare(container->at(right), container->at(index)))
        index = right;
    if (index != parent) {
        swap(container->at(parent), container->at(index));
        pushDown(container, heap_size, index, compare);
    }
}

/**
 * @brief converts a container into a heap according to the comparitor
 *
 * @tparam Container container class
 * @tparam less<typename Container::value_type> comparitor class
 * @param container a pointer to the container to heapify
 * @param compare comparator to use to construct the heap
 */
template <class Container, class Compare = less<typename Container::value_type>>
void heapify(Container* container, Compare compare = less<typename Container::value_type>{}) {
    container->insert(container->begin(), typename Container::value_type());
    size_t heap_size = container->size() - 1;
    for (size_t i = (heap_size >> 1); i >= 1; --i)
        pushDown(container, heap_size, i, compare);
}

/**
 * @brief inserts a value into a container according to a comparitor
 *
 * @tparam Container container class
 * @tparam less<typename Container::value_type> comparitor class
 * @param container a pointer to the container to insert into
 * @param value value to insert
 * @param compare comparator
 */
template <class Container, class Compare = less<typename Container::value_type>>
void heap_insert(Container* container, const typename Container::value_type& value, Compare compare = less<typename Container::value_type>{}) {
    size_t index = container->size();
    container->push_back(value);
    size_t parent = index >> 1;
    while (parent) {
        if (compare(container->at(index), container->at(parent)))
            swap(container->at(index), container->at(parent));
        index >>= 1;
        parent >>= 1;
    }
}

/**
 * @brief retreives the first value in the heap
 *
 * @tparam Container container class
 * @param container container to get the first value from
 * @return const Container::value_type& first value in the heap
 */
template <class Container>
typename Container::const_reference heap_get_min(const Container& container) {
    if (container.size() < 2)
        throw invalid_argument("Heap is empty");
    return container[1];
}

/**
 * @brief deletes the minimum value from the heap according to a comparator
 *
 * @tparam Container container class
 * @tparam less<typename Container::value_type> comparator class
 * @param container container to remove from
 * @param compare comparator to determine the min
 */
template <class Container, class Compare = less<typename Container::value_type>>
void heap_delete_min(Container* container, Compare compare = less<typename Container::value_type>{}) {
    size_t size = container->size();
    if (size < 2)
        throw invalid_argument("Heap is empty");
    swap(container->at(1), container->back());
    container->pop_back();
    pushDown(container, size - 1, 1, compare);
}


// ----------------------- Optional ----------------------- //
/**
 * @brief heapity a container using a comparator function
 *
 * @tparam Container container class
 * @tparam less<typename Container::value_type> comparator function
 * @param container reference to the container
 * @param compare comparator function
 */
template <class Container, class Compare = less<typename Container::value_type>>
void heapify(Container& container, Compare compare = less<typename Container::value_type>{}) { heapify(&container, compare); }

/**
 * @brief Insert a value into the heap
 *
 * @tparam Container container class
 * @tparam less<typename Container::value_type> comparator class
 * @param container reference to the container
 * @param value value to insert
 * @param compare comparator function
 */
template <class Container, class Compare = less<typename Container::value_type>>
void heap_insert(Container& container, const typename Container::value_type& value, Compare compare = less<typename Container::value_type>{}) { heap_insert(&container, value, compare); }


/**
 * @brief Delete the minimum value from the heap according to the comparator
 *
 * @tparam Container container class
 * @tparam less<typename Container::value_type> comparator function
 * @param container container to remove from
 * @param compare comparator function
 */
template <class Container, class Compare = less<typename Container::value_type>>
void heap_delete_min(Container& container, Compare compare = less<typename Container::value_type>{}) { heap_delete_min(&container, compare); }
