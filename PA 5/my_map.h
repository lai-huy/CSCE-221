#pragma once

#include <cstddef>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <utility>
#include <tuple>

using std::cout, std::ostream;
using std::pair;
using std::string;

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
    virtual string to_string() const {
        // make a string that represents the state of the iterator
        //   e.g. "<Map::const_iterator -> [key, value]>"
        return "Map::const_iterator -> [key, value]";
    }
};

// TODO(stduent): implement this
template <class Key, class Value>
class Map_iterator : public Map_const_iterator<Key, Value> {
    friend class Map<Key, Value>;

    typedef Map_Node<Key, Value> Node;
    typedef Map_const_iterator<Key, Value> const_iterator;

public:
    string to_string() const override {
        // make a string that represents the state of the iterator
        //   e.g. "<Map::iterator -> [key, value]>"
        return "Map::iterator -> [key, value]";
    }
};

// TODO(stduent): implement this
template <class Key, class Value>
class Map {
    typedef Map_Node<Key, Value> Node;

public:
    typedef Map_const_iterator<Key, Value> const_iterator;
    typedef Map_iterator<Key, Value> iterator;

    Map();
    Map(const Map& rhs);
    ~Map();
    Map& operator=(const Map& rhs);

    Value& at(const Key& key);
    const Value& at(const Key& key) const;
    Value& operator[](const Key& key);
    const Value& operator[](const Key& key) const;

    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;

    bool is_empty() const;
    size_t size() const;

    void make_empty();
    pair<iterator, bool> insert(const pair<const Key, Value>& pair);
    iterator insert(const_iterator hint, const pair<const Key, Value>& pair);
    size_t remove(const Key& key);
    iterator remove(const_iterator iter);

    bool contains(const Key& key) const;
    iterator find(const Key& key);
    const_iterator find(const Key& key) const;

    void print_map(ostream& os = cout) const;

    // ----------------------- Optional ----------------------- //
    // Map(Map&& rhs);
    // Map& operator=(Map&& rhs);
    // pair<iterator, bool> insert(pair<const Key, Value>&& pair);
    // iterator insert(const_iterator hint, pair<const Key, Value>&& pair);
    // void print_tree(ostream& os = cout) const;
};

template <class Key, class Value>
std::ostream& operator<<(ostream& os, const Map_const_iterator<Key, Value>& iter) {
    return os << iter.to_string();
}
