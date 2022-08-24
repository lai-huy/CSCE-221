#include <iostream>
#include "hashtable_separate_chaining.h"
#include "hashtable_separate_chaining.h"

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
    std::cout << "bucket count is " << table.bucket_count() << std::endl;
    std::cout << "size of bucket 0 is " << table.bucket_size(0) << std::endl;
    std::cout << "bucket " << table.bucket(Hashable("where you are and how you feel", 4)) << " is where i would put a Hashable(\"where you are and how you feel\", 4), if I had one" << std::endl;
    std::cout << "load factor is table.load_factor()" << std::endl;
    std::cout << "max load factor is " << table.max_load_factor() << std::endl;
    table.rehash(42);
    table.print_table();
    
    return 0;
}
