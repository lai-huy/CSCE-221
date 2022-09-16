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
   Stack() : _data{DoublyLinkedList<Object>()} {}

   Stack(const Stack& rhs) : _data{DoublyLinkedList<Object>(rhs._data)} {}

   ~Stack() {
      this->_data.clear();
   }

   Stack& operator=(const Stack& rhs) {
      if (this != &rhs) {
         this->_data.clear();
         this->_data.copy(rhs._data);
      }

      return *this;
   }

   void push(const Object& obj) {
      this->_data.insert(0, obj);
   }

   void pop() {
      try {
         this->_data.remove(0);
      } catch (const out_of_range& err) {
         throw out_of_range("Stack underflow");
      }
   }

   Object& top() {
      try {
         return this->_data[0];
      } catch (const out_of_range& err) {
         throw out_of_range("Stack is empty");
      }
   }

   // ----------------------- Optional ----------------------- //

   //Stack(Stack&& rhs);
   //Stack& operator=(Stack&& rhs);
   //void push(Object&& obj);
   //const Object& top() const;

   size_t size() const {
      return this->_data.size();
   }
};
