#pragma once

#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <utility>

using std::out_of_range;
using std::cout;

/**
 * @brief A Doubly Linked List
 *
 * @tparam Object type of element this is holding
 */
template <typename Object>
class DoublyLinkedList {
public:
    struct Node {
        Object _value;
        Node* _next;
        Node* _prev;

        Node() : _value{Object()}, _next{nullptr}, _prev{nullptr} {}
        Node(const Node& rhs) : _value{rhs._value}, _next{nullptr}, _prev{nullptr} {}
        Node(const Object& obj) : _value{obj}, _next{nullptr}, _prev{nullptr} {}
        Node& operator=(const Node& rhs) {
            if (this != rhs)
                this->_value = rhs._value;
            return *this;
        }
    };

private:
    /**
     * @brief size of the linked list
     */
    size_t _size;

    /**
     * @brief Pointer to the first element in the list
     */
    Node* _head;

    /**
     * @brief Pointer to the last element in the list
     */
    Node* _tail;

public:
    /**
     * @brief clear the list
     */
    void clear() {
        if (this->_head) {
            Node* node = this->_head;
            while (node->_next) {
                node = node->_next;
                delete node->_prev;
            }

            delete this->_tail;
        }

        this->_size = 0;
        this->_head = nullptr;
        this->_tail = nullptr;
    }

    /**
     * @brief Copy a list into this list
     *
     * @param rhs DoublyLinkedList to copy from
     */
    void copy(const DoublyLinkedList& rhs) {
        const Node* head = rhs.head();
        if (!head)
            return;

        this->_head = new Node(head->_value);

        Node* curr = this->_head;
        Node* next = head->_next;
        Node* prev = this->_head;

        while (next) {
            curr->_next = new Node(next->_value);
            prev = curr;
            curr = curr->_next;
            curr->_prev = prev;
            next = next->_next;
        }

        this->_size = rhs.size();
        this->_tail = curr;
        this->_tail->_prev = prev;
    }

    /**
     * @brief Construct a new Doubly Linked List object
     */
    DoublyLinkedList() : _size{0}, _head{nullptr}, _tail{nullptr} {}

    /**
     * @brief Construct a new Doubly Linked List object
     *
     * @param rhs DoublyLinkedList to copy from
     */
    DoublyLinkedList(const DoublyLinkedList& rhs) : _size{0}, _head{nullptr}, _tail{nullptr} {
        this->copy(rhs);
    }

    /**
     * @brief Destroy the Doubly Linked List object
     */
    ~DoublyLinkedList() {
        this->clear();
    }

    /**
     * @brief Copy assignment operator
     *
     * @param rhs DoublyLinkedList to copy from
     * @return DoublyLinkedList& *this
     */
    DoublyLinkedList& operator=(const DoublyLinkedList& rhs) {
        if (this != &rhs) {
            this->clear();
            this->copy(rhs);
        }

        return *this;
    }

    /**
     * @brief Determine the current size of this list
     *
     * @return size_t this->_size;
     */
    size_t size() const {
        return this->_size;
    }

    /**
     * @brief Access a current element at a specified index
     *
     * @param index index to access
     * @return Object& reference to the element
     */
    Object& operator[](size_t index) {
        if (index >= this->_size)
            throw out_of_range("Index out of bounds");

        Node* node = this->_head;

        for (size_t i = 0; i < index; ++i)
            node = node->_next;

        return node->_value;
    }

    /**
     * @brief Insert an object
     *
     * @param index
     * @param obj
     */
    void insert(size_t index, const Object& obj) {
        // cout << "list.insert(" << std::to_string(index) << ", " << std::to_string(obj) << ");\n";

        if (index > this->_size)
            throw out_of_range("Index out of bounds");

        Node* node = new Node(obj);
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
            Node* curr = this->_head;
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

    /**
     * @brief Remove an element from the list
     *
     * @param index index to remove
     */
    void remove(size_t index) {
        // cout << "list.remove(" << std::to_string(index) << ");\n";

        if (index >= this->_size)
            throw out_of_range("Index out of bounds");

        if (this->_size == 1) {
            delete this->_head;
            this->_head = nullptr;
            this->_tail = nullptr;
        } else if (!index) {
            this->_head = this->_head->_next;
            delete this->_head->_prev;
            this->_head->_prev = nullptr;
        } else if (index == this->_size - 1) {
            this->_tail = this->_tail->_prev;
            delete this->_tail->_next;
            this->_tail->_next = nullptr;
        } else {
            Node* node = this->_head;
            for (size_t i = 0; i < index; ++i)
                node = node->_next;

            node->_prev->_next = node->_next;
            node->_next->_prev = node->_prev;
            delete node;
        }

        --this->_size;
    }

    /**
     * @brief return this head pointer of htis list
     *
     * @return const Node* this->_head;
     */
    const Node* head() const {
        return this->_head;
    }

    const Node* tail() const {
        return this->_tail;
    }

    class iterator {
        const Node* _node;
    public:
        iterator() : _node{DoublyLinkedList::_head} {}
        iterator(const Node* node) : _node{node} {}

        iterator& operator=(const Node* node) {
            this->_node = node;
            return *this;
        }

        iterator& operator++() {
            if (this->_node)
                this->_node = this->_node->_next;
            return *this;
        }

        iterator operator++(int) {
            iterator it = *this;
            ++* this;
            return it;
        }

        iterator& operator--() {
            if (this->_node)
                this->_node = this->_node->_prev;
            return *this;
        }

        iterator operator--(int) {
            iterator it = *this;
            --* this;
            return it;
        }

        bool operator!=(const iterator& rhs) {
            return this->_node != rhs._node;
        }

        bool operator==(const iterator& rhs) {
            return this->_node == rhs._node;
        }

        Object operator*() {
            return this->_node->_value;
        }
    };

    //OPTIONAL
    // DoublyLinkedList(DoublyLinkedList&& rhs) : _size{rhs._size}, _head{rhs._head}, _tail{rhs._tail} {
    //     rhs._size = 0;
    //     rhs._head = nullptr;
    //     rhs._tail = nullptr;
    // }

    // DoublyLinkedList& operator=(DoublyLinkedList&& rhs) {
    //     if (this != &rhs) {
    //         this->clear();
    //         this->copy(rhs);
    //     }

    //     return *this;
    // }

    // iterator begin() {
    //     return iterator(this->_head);
    // }

    // const iterator begin() const {
    //     return iterator(this->_head);
    // }

    // iterator end() {
    //     return iterator(this->_tail);
    // }

    // const iterator end() const {
    //     return iterator(this->_tail);
    // }
};
