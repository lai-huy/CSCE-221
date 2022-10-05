#pragma once

#include <functional>
#include <functional>
#include <deque>
#include <initializer_list>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>

using std::less;

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

}

/**
 * @brief
 *
 * @tparam Container
 * @param container
 * @return const Container::value_type&
 */
template <class Container>
const typename Container::value_type& heap_get_min(const Container& container) {

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

}


// ----------------------- Optional ----------------------- //
template <class Container, class Compare = less<typename Container::value_type>>
void heapify(Container& container, Compare compare = less<typename Container::value_type>{}) { heapify(&container, compare); }

template <class Container, class Compare = less<typename Container::value_type>>
void heap_insert(Container& container, const typename Container::value_type& value, Compare compare = less<typename Container::value_type>{}) { heap_insert(&container, value, compare); }

template <class Container, class Compare = less<typename Container::value_type>>
void heap_delete_min(Container& container, Compare compare = less<typename Container::value_type>{}) { heap_delete_min(container, compare); }
