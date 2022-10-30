#pragma once

#include <functional>
#include <iostream>
#include <vector>
#include <utility>

using std::cout, std::ostream;
using std::vector;
using std::string;
using std::swap;

// Pretty printing for vectors of Printable objects (have ostream operator<< defined)
// Be careful: modifications risk failing tests
template <class Printable>
ostream& operator<<(ostream& os, const vector<Printable>& container) {
    os << "[";
    bool first = false;
    for (const Printable& t : container) {
        if (first)
            os << ", ";
        if (typeid(t) == typeid(string))
            os << "\"" << t << "\"";
        else
            os << t;
        first = true;
    }
    os << "]";
    return os;
}

// Selection sort (example of implementation expectations)
template <class Comparable>
void selection_sort(vector<Comparable>& container) {
    // print the initial container
    cout << container << "\n";

    if (container.empty())
        return;

    for (size_t index = 0; index < container.size() - 1; ++index) {
        // do 1 pass of selection sort: find the min and swap it to the front
        size_t index_min = index;
        for (size_t i = index + 1; i < container.size(); ++i)
            if (container[i] < container[index_min])
                index_min = i;
        swap(container[index], container[index_min]);

        // print the container after each pass
        cout << container << "\n";
    }
}

template <class Comparable>
void insertion_sort(vector<Comparable>& values);

template <class Comparable>
void shell_sort(vector<Comparable>& values);

template <class Comparable>
void heap_sort(vector<Comparable>& values);

template <class Comparable>
void merge_sort(vector<Comparable>& values);

template <class Comparable>
void quick_sort(vector<Comparable>& values);

void bucket_sort(vector<unsigned>& values);

template <class Comparable>
void radix_sort(vector<Comparable>& values);
