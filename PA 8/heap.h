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

template <class Container, class Compare = less<typename Container::value_type>>
void build(Container* container, const size_t& heap_size, const size_t& parent, Compare compare = less<typename Container::value_type>{}) {
    size_t left = parent << 1, right = left + 1;
    size_t index = parent;

    if (left < heap_size && compare(container->at(left), container->at(parent)))
        index = left;
    if (right < heap_size && compare(container->at(right), container->at(index)))
        index = right;
    if (index != parent) {
        swap(container->at(parent), container->at(index));
        build(container, heap_size, index, compare);
    }
}

size_t parent(const size_t& root) { return root >> 1; }

template <class Container, class Compare = less<typename Container::value_type>>
typename Container::const_reference replaceChild(size_t root, const Container& container, Compare compare = less<typename Container::value_type>{}) {
    size_t left = root << 1, right = left + 1;
    if (right > container.size())
        return left;
    return compare(container[left], container[right]) ? left : right;
}

/**
 * @brief
 *
 * @tparam Container
 * @tparam less<typename Container::value_type>
 * @param container
 * @param compare
 */
template <class Container, class Compare = less<typename Container::value_type>>
void heapify(Container* container, Compare compare = less<typename Container::value_type>{}) {
    container->insert(container->begin(), typename Container::value_type());
    size_t heap_size = container->size() - 1;
    for (size_t i = (heap_size >> 1); i >= 1; --i)
        build(container, heap_size, i, compare);
    container->erase(container->begin());
}

/**
 * @brief
 *
 * @tparam Container
 * @tparam less<typename Container::value_type>
 * @param container
 * @param value
 * @param compare
 */
template <class Container, class Compare = less<typename Container::value_type>>
void heap_insert(Container* container, const typename Container::value_type& value, Compare compare = less<typename Container::value_type>{}) {
    container->insert(container->begin(), typename Container::value_type());
    size_t index = container->size();
    container->push_back(value);
    size_t p = parent(index);
    while (index >> 1) {
        if (compare(container->at(index), container->at(p)))
            swap(container->at(index), container->at(p));
        index >>= 1;
        p = parent(index);
    }
    container->erase(container->begin());
}

/**
 * @brief
 *
 * @tparam Container
 * @param container
 * @return const Container::value_type&
 */
template <class Container>
typename Container::const_reference heap_get_min(const Container& container) {
    if (!container.size())
        throw invalid_argument("Heap is empty");
    return *container.begin();
}

/**
 * @brief
 *
 * @tparam Container
 * @tparam less<typename Container::value_type>
 * @param container
 * @param compare
 */
template <class Container, class Compare = less<typename Container::value_type>>
void heap_delete_min(Container* container, Compare compare = less<typename Container::value_type>{}) {
    if (!container->size())
        throw invalid_argument("Heap is empty");
    reverse(container->begin(), container->end());
    container->pop_back();
    reverse(container->begin(), container->end());
    heapify(container, compare);
}


// ----------------------- Optional ----------------------- //
template <class Container, class Compare = less<typename Container::value_type>>
void heapify(Container& container, Compare compare = less<typename Container::value_type>{}) { heapify(&container, compare); }

template <class Container, class Compare = less<typename Container::value_type>>
void heap_insert(Container& container, const typename Container::value_type& value, Compare compare = less<typename Container::value_type>{}) { heap_insert(&container, value, compare); }

template <class Container, class Compare = less<typename Container::value_type>>
void heap_delete_min(Container& container, Compare compare = less<typename Container::value_type>{}) { heap_delete_min(&container, compare); }