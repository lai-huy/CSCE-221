#pragma once

#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <utility>
#include "doubly_linked_list.h"

template <typename Object>
class Stack {
private:
   DoublyLinkedList<Object> _data;

public:
   Stack();
   Stack(const Stack& rhs);
   ~Stack();
   Stack& operator=(const Stack& rhs);

   void push(const Object& obj);
   void pop();
   Object& top();

   //OPTIONAL
   //Stack(Stack&& rhs);
   //Stack& operator=(Stack&& rhs);
   //void push(Object&& obj);
   //const Object& top() const;
   size_t size() const {
      return this->_data.size();
   }
};
