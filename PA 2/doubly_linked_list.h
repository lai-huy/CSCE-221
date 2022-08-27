#pragma once

#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <utility>

using std::out_of_range;
using std::cout;

template <typename Object>
struct Node {
    Object _value;
    Node<Object>* _next;
    Node<Object>* _prev;

    Node() : _value{Object()}, _next{nullptr}, _prev{nullptr} {}
    Node(const Node& rhs) : _value{rhs._value}, _next{nullptr}, _prev{nullptr} {}
    Node(const Object& obj) : _value{obj}, _next{nullptr}, _prev{nullptr} {}
    Node& operator=(const Node& rhs) {
        if (this != rhs)
            this->_value = rhs._value;
        return *this;
    }
};

template <typename Object>
class DoublyLinkedList {
private:
    size_t _size;
    Node<Object>* _head;
    Node<Object>* _tail;

    void clear() {
        if (this->_size) {
            this->_size = 0;
            Node<Object>* node = this->_head;
            while (node->_next) {
                node = node->_next;
                delete node->_prev;
            }

            delete this->_tail;
            this->_head = nullptr;
            this->_tail = nullptr;
        }
    }

    void copy(const DoublyLinkedList<Object> rhs) {
        const Node<Object>* node = rhs._head;
        while (node) {
            this->insert(this->_size, node->_value);
            node = node->_next;
        }
    }

public:
    DoublyLinkedList() : _size{0}, _head{nullptr}, _tail{nullptr} {}
    DoublyLinkedList(const DoublyLinkedList& rhs) : _size{rhs._size}, _head{nullptr}, _tail{nullptr} {
        this->copy(rhs);
    }

    ~DoublyLinkedList() {
        this->clear();
    }

    DoublyLinkedList& operator=(const DoublyLinkedList& rhs) {
        if (this != &rhs) {
            this->clear();
            this->copy(rhs);
        }

        return *this;
    }

    size_t size() const {
        return this->_size;
    }

    Object& operator[](size_t index) {
        if (index >= this->_size)
            throw out_of_range("Index out of bounds");

        Node<Object>* node = this->_head;

        for (size_t i = 0; i < this->_size; ++i)
            node = node->_next;

        return node->_value;
    }

    void insert(size_t index, const Object& obj) {
        if (index > this->_size)
            throw out_of_range("Index out of bounds");

        cout << "list.insert(" << std::to_string(index) << ", " << std::to_string(obj) << ");\n";

        Node<Object>* node = new Node(obj);
        if (!this->_head) {
            this->_head = node;
            this->_tail = node;
        } else if (!index) {
            node->_next = this->_head;
            this->_head->_prev = node;
            this->_head = node;
        } else if (index == this->_size) {
            node->_prev = this->_tail;
            this->_tail->_next = node;
            this->_tail = this->_tail->_next;
        } else {
            Node<Object>* curr = this->_head;
            for (size_t i = 0; i < index - 1; ++i)
                curr = curr->_next;

            node->_next = curr->_next;
            node->_prev = curr;
            curr->_next->_prev = node;
            curr->_next = node;
        }

        ++this->_size;
        return;
    }

    void remove(size_t index) {
        if (index >= this->_size)
            throw out_of_range("Index out of bounds");

        if (!index) {
            this->_head = this->_head->_next;
            delete this->_head->_prev;
            this->_head->_prev = nullptr;
        } else if (index == this->_size) {
            this->_tail = this->_tail->_prev;
            delete this->_tail->_next;
            this->_tail->_next = nullptr;
            return;
        } else {
            Node<Object>* node = this->_head;
            for (size_t i = 0; i < index; ++i)
                node = node->_next;

            node->_prev->_next = node->_next;
            node->_next->_prev = node->_prev;
            delete node;
        }
    }

    const Node<Object>* head() const {
        return this->_head;
    }

    //OPTIONAL
    // DoublyLinkedList(DoublyLinkedList&& rhs) : _size{rhs._size}, _head{rhs._head} {}
    // DoublyLinkedList& operator=(DoublyLinkedList&&);
    // iterator begin();
    // const_iterator begin() const;
    // iterator end();
    // const_iterator end() const;
};
