#include "my_map.h"
#include "my_map.h"
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
    // Map
    {
        Map<std::string,int> map;
        map["two"] = 2;
        const auto [iter, success] = map.insert({"one", 1});
        auto iter2 = map.insert(iter, {"three", 3});
        const auto [iter3, success2] = map.insert(*iter);
        const auto iter4 = map.insert(iter3, *iter2);
        *iter4;  // std::pair
        iter4->first; // key
        iter4->second; // value
        map.contains("four");
        map.at("one");
        auto iter5 = map.find("one");
        map.remove(iter5);
        ++iter5;
        map.size();
        map.is_empty();
        map.print_map();
        map.make_empty();
    }
    
    {
        Map<ComparableValue,int> map;
        map[ComparableValue(2)] = 2;
        const auto [iter, success] = map.insert({ComparableValue(1), 1});
        auto iter2 = map.insert(iter, {ComparableValue(3), 3});
        const auto [iter3, success2] = map.insert(*iter);
        const auto iter4 = map.insert(iter3, *iter2);
        *iter4;  // std::pair
        iter4->first; // key
        iter4->second; // value
        map.contains(ComparableValue(4));
        map.at(ComparableValue(1));
        auto iter5 = map.find(ComparableValue(1));
        map.remove(iter5);
        ++iter5;
        map.size();
        map.is_empty();
        map.print_map();
        map.make_empty();
    }
    
    return 0;
}
