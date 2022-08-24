#pragma once

// Pretty printing for vectors of Printable objects (have ostream operator<< defined)
// Be careful: modifications risk failing tests
template <class Printable>
std::ostream& operator<<(std::ostream& os, const std::vector<Printable>& container) {
    os << "[";
    bool first = false;
    for (const Printable& t : container) {
        if (first) {
            os << ", ";
        }
        if (typeid(t) == typeid(std::string)) {
            os << "\"" << t << "\"";
        } else {
            os << t;
        }
        first = true;
    }
    os << "]";
    return os;
}

// Selection sort (example of implementation expectations)
template <class Comparable>
void selection_sort(std::vector<Comparable>& container) {
    // print the initial container
    std::cout << container << std::endl;

    if (container.empty()) {
        return;
    }

    for (size_t index = 0; index < container.size()-1; index++) {
        // do 1 pass of selection sort: find the min and swap it to the front
        size_t index_min = index;
        for (size_t i = index+1; i < container.size(); i++) {
            if (container[i] < container[index_min]) {
                index_min = i;
            }
        }
        Comparable t = container[index];
        container[index] = container[index_min];
        container[index_min] = t;

        // print the container after each pass
        std::cout << container << std::endl;
    }
}

// TODO(student): implement sorts: insertion, shell, heap, merge, quick, bucket, radix
