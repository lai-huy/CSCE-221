#include <iostream>
#include "hashtable_open_addressing.h"

class Hashable {
    std::string str;
    int i;

 public:    
    Hashable() : str{}, i{} {}
    Hashable(std::string str, int i) : str{str}, i{i} {}

    bool operator==(const Hashable& rhs) const { return str == rhs.str && i == rhs.i; }         
    bool operator!=(const Hashable& rhs) const { return !(*this == rhs); }
    
    friend std::ostream& operator<<(std::ostream&, const Hashable&);
};

std::ostream& operator<<(std::ostream& os, const Hashable& hashable) {
    os << "{\""<<hashable.str<<"\", "<<hashable.i<<"}";
    return os;
}

struct HashableHash {
    size_t operator()(const Hashable& value) const noexcept {
        return sizeof value;
    }
};

int main() {
    HashTable<Hashable, HashableHash> table(11);    
    HashTable<Hashable, HashableHash> copy = table;
    table = copy;
    std::cout << "is empty is " << std::boolalpha << table.is_empty() << std::endl;
    std::cout << "size is " << table.size() << std::endl;
    table.make_empty();
    table.insert(Hashable("hey there", 3));
    table.remove(Hashable("i know it's hard to feel", 2));
    table.contains(Hashable("like i don't care at all", 7));
    std::cout << "table size is " << table.table_size() << std::endl;
    table.print_table();
    
    return 0;
}
