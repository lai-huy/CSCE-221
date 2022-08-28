#pragma once

#include <iostream>

// forward declarations
template <class K, class V> class Map;
template <class K, class V> class Map_const_iterator;
template <class K, class V> class Map_iterator;

// TODO(stduent): implement this
template <class Key, class Value>
class Map_Node {
    friend class Map<Key, Value>;
    friend class Map_const_iterator<Key, Value>;
    friend class Map_iterator<Key, Value>;
};

// TODO(stduent): implement this
template <class Key, class Value>
class Map_const_iterator {
    friend class Map<Key, Value>;

    typedef Map_Node<Key, Value> Node;
    typedef std::pair<const Key, Value> value_type;

public:
    virtual std::string to_string() const {
        // make a string that represents the state of the iterator
        //   e.g. "<Map::const_iterator -> [key, value]>"
        return "Map::const_iterator";
    }
};

// TODO(stduent): implement this
template <class Key, class Value>
class Map_iterator : public Map_const_iterator<Key, Value> {
    friend class Map<Key, Value>;

    typedef Map_Node<Key, Value> Node;
    typedef Map_const_iterator<Key, Value> const_iterator;

public:
    std::string to_string() const override {
        // make a string that represents the state of the iterator
        //   e.g. "<Map::iterator -> [key, value]>"
        return "Map::iterator";
    }
};

// TODO(stduent): implement this
template <class Key, class Value>
class Map {
    typedef Map_Node<Key, Value> Node;

public:
    typedef Map_const_iterator<Key, Value> const_iterator;
    typedef Map_iterator<Key, Value> iterator;
};

template <class Key, class Value>
std::ostream& operator<<(std::ostream& os, const Map_const_iterator<Key, Value>& iter) {
    return os << iter.to_string();
}
