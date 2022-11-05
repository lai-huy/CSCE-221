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
 * @brief
 *
 * @tparam Container
 * @tparam less<typename Container::value_type>
 * @param container
 * @param compare
 */
template <class Container, class Compare = less<typename Container::value_type>>
void heapify(Container* container, Compare compare = less<typename Container::value_type>{}) {
    reverse(container->begin(), container->end());
    make_heap(container->begin(), container->end(), compare);
    reverse(container->begin(), container->end());
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
    reverse(container->begin(), container->end());
    container->push_back(value);
    push_heap(container->begin(), container->end(), compare);
    reverse(container->begin(), container->end());
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
