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

template <class Container, class Compare=less<typename Container::value_type>>
void heapify(Container*, Compare=less<typename Container::value_type>{});

template <class Container, class Compare=less<typename Container::value_type>>
void heap_insert(Container*, const typename Container::value_type&, Compare=less<typename Container::value_type>{});

template <class Container>
const typename Container::value_type& heap_get_min(const Container&);

template <class Container, class Compare=less<typename Container::value_type>>
void heap_delete_min(Container*, Compare=less<typename Container::value_type>{});


// OPTIONAL
template <class Container, class Compare=less<typename Container::value_type>>
void heapify(Container&, Compare=less<typename Container::value_type>{});

template <class Container, class Compare=less<typename Container::value_type>>
void heap_insert(Container&, const typename Container::value_type&, Compare=less<typename Container::value_type>{});

template <class Container, class Compare=less<typename Container::value_type>>
void heap_delete_min(Container&, Compare=less<typename Container::value_type>{});
