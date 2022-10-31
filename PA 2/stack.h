#pragma once

#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <utility>
#include "doubly_linked_list.h"

using std::swap, std::move;

/**
 * @brief First in Last Out
 *
 * @tparam Object datatype of the Stack
 */
template <typename Object>
class Stack {
private:
   /**
    * @brief Internal structure of the Stack
    */
   DoublyLinkedList<Object> _data;

public:
   /**
    * @brief Construct a new Stack object
    */
   Stack() : _data{DoublyLinkedList<Object>()} {}

   /**
    * @brief Construct a new Stack object
    *
    * @param rhs Stack to copy from
    */
   Stack(const Stack& rhs) : _data{rhs._data} {}

   /**
    * @brief Destroy the Stack object
    */
   ~Stack() { this->_data.clear(); }

   /**
    * @brief Copy assignment operator
    *
    * @param rhs Stack to copy from
    * @return Stack& *this
    */
   Stack& operator=(const Stack& rhs) {
      if (this != &rhs) {
         this->_data.clear();
         this->_data.copy(rhs._data);
      }

      return *this;
   }

   /**
    * @brief Push an object to the top of the stack
    *
    * @param value obect to push
    */
   void push(const Object& value) { this->_data.insert(0, value); }

   /**
    * @brief Pop the object at the top of the stack
    */
   void pop() {
      try {
         this->_data.remove(0);
      } catch (const out_of_range& err) {
         throw out_of_range("Stack underflow");
      }
   }

   /**
    * @brief Reterives the object at the top of the stack
    *
    * @return Object& at the top of the stack
    */
   Object& top() {
      try {
         return this->_data[0];
      } catch (const out_of_range& err) {
         throw out_of_range("Stack is empty");
      }
   }

   // ----------------------- Optional ----------------------- //
   /**
    * @brief Construct a new Stack object
    *
    * @param rhs stack to move from
    */
   Stack(Stack&& rhs) : _data{move(rhs._data)} {}

   /**
    * @brief Move assignment operator
    *
    * @param rhs Stack to move from
    * @return Stack& *this
    */
   Stack& operator=(Stack&& rhs) {
      if (this != &rhs) {
         this->_data.clear();
         this->_data = move(rhs._data);
      }

      return *this;
   }

   /**
    * @brief Move push an object to the stack
    *
    * @param value Object to push
    */
   void push(Object&& value) {
      Object o{};
      swap(o, value);
      this->_data.insert(0, o);
   }

   /**
    * @brief Reterives the object at the top of the stack
    *
    * @return const Object& at the top of the stack
    */
   const Object& top() const {
      try {
         return this->_data[0];
      } catch (const out_of_range& err) {
         throw out_of_range("Stack is empty");
      }
   }

   /**
    * @brief Determine the size of the stack
    *
    * @return size_t size of the stack
    */
   size_t size() const { return this->_data.size(); }
};
