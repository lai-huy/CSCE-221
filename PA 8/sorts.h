#pragma once

#include <functional>
#include <iostream>
#include <vector>
#include <utility>
#include "heap.h"

using std::cout, std::ostream;
using std::vector;
using std::string;
using std::swap, std::move;
using std::begin, std::end;
using std::max_element;

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
    cout << container << "\n";

    if (container.empty())
        return;

    for (size_t index = 0; index < container.size() - 1; ++index) {
        size_t index_min = index;
        for (size_t i = index + 1; i < container.size(); ++i)
            if (container[i] < container[index_min])
                index_min = i;
        swap(container[index], container[index_min]);

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
    for (size_t gap = n >> 1; gap > 0; gap >>= 1) {
        for (size_t i = gap; i < n; ++i) {
            Comparable temp = move(values[i]);
            size_t j;
            for (j = i; j >= gap && temp < values[j - gap]; j -= gap)
                values[j] = move(values[j - gap]);
            values[j] = move(temp);
        }
        cout << values << "\n";
    }
}

template <class Comparable>
void heap_sort(vector<Comparable>& values) {
    cout << values << "\n";

    if (values.empty())
        return;

    vector<Comparable> heap(values.begin(), values.end());
    heapify(&heap);
    cout << heap << "\n";
    values.clear();
    while (heap.size() != 1) {
        values.push_back(heap_get_min(heap));
        heap_delete_min(&heap);
        cout << heap << "\n" << values << "\n";
    }
}

template <class Comparable>
void merge(vector<Comparable>& values, vector<Comparable>& tmpArray, size_t leftPos, size_t rightPos, size_t rightEnd) {
    size_t leftEnd = rightPos - 1, tmpPos = leftPos, numElements = rightEnd - leftPos + 1;
    while (leftPos <= leftEnd && rightPos <= rightEnd)
        tmpArray[tmpPos++] = move(values[leftPos] <= values[rightPos] ? values[leftPos++] : values[rightPos++]);

    while (leftPos <= leftEnd)
        tmpArray[tmpPos++] = move(values[leftPos++]);

    while (rightPos <= rightEnd)
        tmpArray[tmpPos++] = move(values[rightPos++]);

    for (size_t i = 0; i < numElements; ++i, --rightEnd)
        values[rightEnd] = move(tmpArray[rightEnd]);
}

template <class Comparable>
void merge_sort(vector<Comparable>& values, vector<Comparable>& temp, size_t begin, size_t end) {
    if (begin < end) {
        size_t center = begin + ((end - begin) >> 1);
        merge_sort(values, temp, begin, center);
        merge_sort(values, temp, center + 1, end);
        merge(values, temp, begin, center + 1, end);
        cout << values << "\n";
    }
}

template <class Comparable>
void merge_sort(vector<Comparable>& values) {
    cout << values << "\n";

    if (values.empty())
        return;

    vector<Comparable> temp(values.size(), Comparable{});
    merge_sort(values, temp, 0, values.size() - 1);
}

template <class Comparable>
void quick_sort(vector<Comparable>& values) {
    cout << values << "\n";

    if (values.empty())
        return;

    vector<Comparable> smaller{}, same{}, larger{};
    const Comparable& partition = values[values.size() >> 1];
    for (const Comparable& item : values)
        if (item < partition)
            smaller.push_back(move(item));
        else if (item > partition)
            larger.push_back(move(item));
        else
            same.push_back(move(item));

    quick_sort(smaller);
    quick_sort(larger);
    move(begin(smaller), end(smaller), begin(values));
    move(begin(same), end(same), begin(values) + smaller.size());
    move(begin(larger), end(larger), begin(values) + smaller.size() + same.size());
    cout << values << "\n";
}

void bucket_sort(vector<unsigned>& values) {
    cout << values << "\n";

    if (values.empty())
        return;

    vector<size_t> counts(*max_element(values.begin(), values.end()) + 1);
    for (const unsigned& index : values)
        ++counts[index];
    counts.shrink_to_fit();
    cout << counts << "\n";

    values.clear();
    for (size_t i = 0; i < counts.size(); ++i) {
        if (!counts[i])
            continue;
        for (size_t j = 0; j < counts[i]; ++j)
            values.push_back(i);
        cout << values << "\n";
    }
}

template <class Comparable>
void radix_sort(vector<Comparable>& values) {
    cout << values << "\n";

    if (values.empty())
        return;

    // const Comparable& val = std::max_element(values.begin(), values.end());
    std::sort(values.begin(), values.end());
    cout << values << "\n";
}
