#include <iostream>
#include <deque>
#include "heap.h"

template <class T>
class MyContainer {
    std::vector<T> array;
    
 public:
    using value_type = T;
    using reference = value_type&;
    using const_reference = const value_type&;
    using size_type = size_t;
    using iterator = typename std::vector<T>::iterator;
    using const_iterator = typename std::vector<T>::const_iterator;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
 
    // Constructors
    MyContainer() : array{} {}
    MyContainer(std::initializer_list<value_type> list) : array{list} {}
    // default rule of 5 should be fine.
    
    // Element Access
    constexpr reference operator[](size_type index) { return at(index); }
    constexpr const_reference operator[](size_type index) const { return at(index); }
    constexpr reference at(size_type index) { return array.at(index); }
    constexpr const_reference at(size_type index) const { return array.at(index); }
    constexpr reference front() { return array.front(); }
    constexpr const_reference front() const { return array.front(); }
    constexpr reference back() { return array.back(); }
    constexpr const_reference back() const { return array.back(); }
    
    // Iterators
    constexpr iterator begin() noexcept { return array.begin(); }
    constexpr const_iterator begin() const noexcept { return array.begin(); }
    constexpr const_iterator cbegin() const noexcept { return array.cbegin(); }
    constexpr iterator end() noexcept { return array.end(); }
    constexpr const_iterator end() const noexcept { return array.end(); }
    constexpr const_iterator cend() const noexcept { return array.cend(); }
    constexpr reverse_iterator rbegin() noexcept { return array.rbegin(); }
    constexpr const_reverse_iterator rbegin() const noexcept { return array.rbegin(); }
    constexpr const_reverse_iterator crbegin() const noexcept { return array.crbegin(); }
    constexpr reverse_iterator rend() noexcept { return array.rend(); }
    constexpr const_reverse_iterator rend() const noexcept { return array.rend(); }
    constexpr const_reverse_iterator crend() const noexcept { return array.crend(); }
    
    // Capacity
    [[nodiscard]] constexpr bool empty() const noexcept { return array.empty(); }
    constexpr size_type size() const noexcept { return array.size(); }
    constexpr size_type max_size() const noexcept { return array.max_size(); }
    constexpr size_type capacity() const noexcept { return array.capacity(); }
    constexpr void resize(size_type sz) { array.resize(sz); }
    constexpr void resize(size_type sz, const T& c) { array.resize(sz, c); }
    constexpr void reserve(size_type n) { array.reserve(n); }
    constexpr void shrink_to_fit() { array.shrink_to_fit(); }
    
    // Modifiers
    constexpr void push_back(const T& x) { array.push_back(x); }
    constexpr void push_back(T&& x) { array.push_back(std::move(x)); }
    constexpr void pop_back() { array.pop_back(); }
    
    constexpr iterator insert(const_iterator position, const T& x) { return array.insert(position, x); }
    constexpr iterator insert(const_iterator position, T&& x) { return array.insert(position, std::move(x)); }
    constexpr iterator insert(const_iterator position, size_type n, const T& x) { return array.insert(position, n, x); }
    template<class InputIt>
    constexpr iterator insert(const_iterator position, InputIt first, InputIt last) { return array.insert(position, first, last); }
    constexpr iterator insert(const_iterator position, std::initializer_list<T> il) { return array.insert(position, il); }
    constexpr iterator erase(const_iterator position) { return array.erase(position); }
    constexpr iterator erase(const_iterator first, const_iterator last) { return array.erase(first, last); }
    constexpr void clear() noexcept { array.clear(); }
    
};

template <class Comparable>
struct GreaterThan {
    constexpr bool operator()(const Comparable& lhs, const Comparable& rhs) const {
        return rhs < lhs;
    }
};

int main() {
    {
        MyContainer<std::string> heap{"one","two","three","four","five"};
        heapify(&heap, GreaterThan<std::string>{});
        heap_delete_min(&heap, GreaterThan<std::string>{});
        heap_insert(&heap, "one", GreaterThan<std::string>{});
        std::cout << heap_get_min(heap) << std::endl;
    }
    
    {
        std::deque<std::string> heap{"one","two","three","four","five"};
        heapify(&heap);
        heap_delete_min(&heap);
        heap_insert(&heap, "one");
        std::cout << heap_get_min(heap) << std::endl;
    }
    
    return 0;
}
