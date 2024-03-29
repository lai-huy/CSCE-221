#pragma once

#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <utility>

using std::out_of_range;
using std::cout;
using std::swap;

/**
 * @brief A Doubly Linked List
 *
 * @tparam Object type of element this is holding
 */
template <typename Object>
class DoublyLinkedList {
public:
    /**
     * @brief indivudual node for the linked list
     */
    struct Node {
        /**
         * @brief Objected stored in the node
         */
        Object _value;

        /**
         * @brief a pointer to the next node in the linked list
         */
        Node* _next;

        /**
         * @brief a pointer to the previous node in the linked list
         */
        Node* _prev;

        /**
         * @brief Construct a new Node object
         */
        Node() : _value{Object{}}, _next{nullptr}, _prev{nullptr} {}

        /**
         * @brief Construct a new Node object
         *
         * @param obj object to set as the value
         */
        Node(const Object& obj) : _value{obj}, _next{nullptr}, _prev{nullptr} {}

        /**
         * @brief Construct a new Node object
         *
         * @param rhs node to copy from
         */
        Node(const Node& rhs) : Node(rhs._value) {}

        /**
         * @brief Destroy the Node object
         */
        ~Node() {}

        /**
         * @brief Copy assignment operator
         *
         * @param rhs node to copy from
         * @return Node& *this
         */
        Node& operator=(const Node& rhs) {
            if (this != &rhs)
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

        this->_size = rhs._size;
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
    DoublyLinkedList(const DoublyLinkedList& rhs) : _size{0}, _head{nullptr}, _tail{nullptr} { this->copy(rhs); }

    /**
     * @brief Destroy the Doubly Linked List object
     */
    ~DoublyLinkedList() { this->clear(); }

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
    size_t size() const { return this->_size; }

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
     * @brief return this head pointer of this list
     *
     * @return const Node* this->_head;
     */
    const Node* head() const { return this->_head; }

    /**
     * @brief return this tail point of this list
     *
     * @return const Node* this->_tail
     */
    const Node* tail() const { return this->_tail; }

    // ----------------------- Optional ----------------------- //
    class const_iterator {
        Node* const _node;
    public:
        const_iterator() : const_iterator(nullptr) {}
        const_iterator(const Node* node) : _node{node} {}
        const_iterator(const const_iterator& rhs) : const_iterator(rhs._node) {}
        ~const_iterator() { this->_node = nullptr; }

        const Object& operator*() { return this->_node->_value; }

        const Object* operator->() { return &this->_node->_value; }

        const_iterator& operator=(Node* const& node) {
            this->_node = node;
            return *this;
        }

        const_iterator& operator=(const const_iterator& rhs) {
            if (this != &rhs)
                this->_node = rhs._node;
            return *this;
        }

        const_iterator& operator++() {
            if (this->_node)
                this->_node = this->_node->_next;
            return *this;
        }

        const_iterator operator++(int) {
            const_iterator it = *this;
            ++(*this);
            return it;
        }

        friend bool operator==(const const_iterator& rhs, const const_iterator& lhs) { return rhs._node == lhs._node; }
        friend bool operator!=(const const_iterator& rhs, const const_iterator& lhs) { return rhs._node != lhs._node; }
    };


    class iterator {
        Node* _node;
    public:
        iterator() : iterator(nullptr) {}
        iterator(Node* node) : _node{node} {}
        iterator(const iterator& rhs) : iterator(rhs._node) {}
        ~iterator() { this->_node = nullptr; }

        Object& operator*() { return this->_node->_value; }

        Object* operator->() { return &this->_node->_value; }

        iterator& operator=(Node* const& node) {
            this->_node = node;
            return *this;
        }

        iterator& operator=(const iterator& rhs) {
            if (this != &rhs)
                this->_node = rhs._node;
            return *this;
        }

        iterator& operator++() {
            if (this->_node)
                this->_node = this->_node->_next;
            return *this;
        }

        iterator operator++(int) {
            iterator it = *this;
            ++(*this);
            return it;
        }

        friend bool operator==(const iterator& lhs, const iterator& rhs) { return lhs._node == rhs._node; }

        friend bool operator!=(const iterator& lhs, const iterator& rhs) { return lhs._node != rhs._node; }
    };

    DoublyLinkedList(DoublyLinkedList&& rhs) : DoublyLinkedList() {
        swap(this->_size, rhs._size);
        swap(this->_head, rhs._head);
        swap(this->_tail, rhs._tail);
    }

    DoublyLinkedList& operator=(DoublyLinkedList&& rhs) {
        if (this != &rhs) {
            this->clear();
            swap(this->_size, rhs._size);
            swap(this->_head, rhs._head);
            swap(this->_tail, rhs._tail);
        }

        return *this;
    }

    void insert(size_t index, Object&& value) {
        Object o{};
        swap(o, value);
        this->insert(index, o);
    }

    iterator begin() { return iterator(this->_head); }

    const_iterator begin() const { return const_iterator(this->_head); }

    iterator end() { return iterator(nullptr); }

    const_iterator end() const { return const_iterator(nullptr); }
};
