#pragma once

#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <utility>
#include "doubly_linked_list.h"

template <typename Object>
class Queue {
private:
    DoublyLinkedList<Object> _data;
public:
    Queue();
    Queue(const Queue& rhs);
    ~Queue();
    Queue& operator=(const Queue& rhs);
    void enqueue(const Object& rhs);
    Object dequeue();
    Object& front();

    //OPTIONAL
    // Queue(Queue&&)
    // Queue& operator=(Queue&&)
    // void enqueue(Object&&)
    // const Object& front() const
    // size_t size() const
};
