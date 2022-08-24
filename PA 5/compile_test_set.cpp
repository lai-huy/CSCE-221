#include "my_set.h"
#include "my_set.h"
#include <iostream>

struct ComparableValue {
    int value;
    
    ComparableValue() : value{0} {}
    explicit ComparableValue(int value) : value{value} {}
    
    bool operator<(const ComparableValue& rhs) const { 
        return value < rhs.value; 
    }
    bool operator>(const ComparableValue& rhs) const { 
        return rhs < *this; 
    }
    bool operator>=(const ComparableValue& rhs) const { 
        return !(*this < rhs); 
    }
    bool operator<=(const ComparableValue& rhs) const { 
        return !(*this > rhs); 
    }
    bool operator!=(const ComparableValue& rhs) const { 
        return *this < rhs || *this > rhs; 
    }
    bool operator==(const ComparableValue& rhs) const { 
        return !(*this != rhs); 
    }
};

std::ostream& operator<<(std::ostream& os, const ComparableValue& value) {
    os << "CV" << value.value;
    return os;
}

int main() {
    // Set
    {
        Set<int> set;
        set.insert(2);
        set.insert(1);
        set.insert(3);
        set.contains(4);
        auto iter = set.find(1);
        set.remove(iter);
        ++iter;
        *iter;
        set.size();
        set.is_empty();
        set.print_set();
        set.make_empty();
    }
    
    {
        Set<ComparableValue> set;
        set.insert(ComparableValue(2));
        set.insert(ComparableValue(1));
        set.insert(ComparableValue(3));
        set.contains(ComparableValue(4));
        auto iter = set.find(ComparableValue(1));
        set.remove(iter);
        ++iter;
        *iter;
        set.size();
        set.is_empty();
        set.print_set();
        set.make_empty();
    }
    
    return 0;
}
