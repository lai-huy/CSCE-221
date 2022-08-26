#include <stdexcept>
#include <iostream>
#include "collection.h"

using std::cout;

int main() {
    Collection<int> list;
    list.insert(0);
    list.insert(1);
    list.remove(0);
    list.remove(0);
    list.insert(2);
    list.insert(3);
    list.remove(4);
    list.is_empty();

    // Collection<Collection<int>> list;
    // Collection<int> a, b, c, d;
    // list.insert(a);
    // list.insert(b);
    // list.insert(c);
    // list.insert(d);

    return 0;
}