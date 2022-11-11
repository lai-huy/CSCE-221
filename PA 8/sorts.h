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
void insertion_sort(vector<Comparable>& values) {
    cout << values << "\n";

    if (values.empty())
        return;

    for (size_t index = 1; index < values.size(); ++index) {
        Comparable key = values[index];
        size_t j = index - 1;
        while (j < values.size() && values[j] > key) {
            values[j + 1] = values[j];
            --j;
        }
        values[j + 1] = key;

        cout << values << "\n";
    }
}

template <class Comparable>
void shell_sort(vector<Comparable>& values) {
    cout << values << "\n";

    if (values.empty())
        return;

    size_t n = values.size();
    for (size_t gap = n >> 1; gap; gap >>= 1) {
        for (size_t i = gap; i < n; ++i) {
            Comparable temp = values[i];
            size_t j;
            for (j = i; j >= gap && values[j - gap] > temp; j -= gap)
                values[j] = values[j - gap];
            values[j] = temp;
        }

        cout << values << "\n";
    }
}

template <class Comparable>
void heap_sort(vector<Comparable>& values) {
    cout << values << "\n";

    if (values.empty())
        return;

    std::sort(values.begin(), values.end());
}

template <class Comparable>
void merge(vector<Comparable>& values, const size_t& begin, const size_t& mid, const size_t& end) {
    size_t i = 0, j = mid + 1, m = begin;

    while (i < mid && j < end)
        swap(values[m++], values[i] <= values[j] ? values[i++] : values[j++]);
}

template <class Comparable>
void merge_sort(vector<Comparable>& values, const size_t& begin, const size_t& end) {
    if (begin >= end)
        return;

    size_t mid = begin + ((end - begin) >> 1);
    merge_sort(values, begin, mid);
    merge_sort(values, mid + 1, end);
    merge(values, begin, mid, end);
    cout << values << "\n";
}

template <class Comparable>
void merge_sort(vector<Comparable>& values) {
    cout << values << "\n";

    if (values.empty())
        return;

    merge_sort(values, 0, values.size() - 1);
}

template <class Comparable>
void quick_sort(vector<Comparable>& values) {
    cout << values << "\n";

    if (values.empty())
        return;

    std::sort(values.begin(), values.end());
}

void bucket_sort(vector<unsigned>& values) {
    cout << values << "\n";

    if (values.empty())
        return;

    std::sort(values.begin(), values.end());
}

template <class Comparable>
void radix_sort(vector<Comparable>& values) {
    cout << values << "\n";

    if (values.empty())
        return;

    std::sort(values.begin(), values.end());
}
