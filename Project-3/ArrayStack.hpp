#pragma once
#include <iostream>
#include "StackInterface.hpp"
using namespace std;

template <class ItemType>
class ArrayStack : public StackInterface<ItemType> {
   private:
    static const int DEFAULT_CAPACITY = 50;
    ItemType items[DEFAULT_CAPACITY];  // Array of stock items
    int top;                           // Index of top of stack

   public:
    ArrayStack();
    bool isEmpty() const;
    bool push(const ItemType& newEntry);
    bool pop();
    ItemType peek() const;
};

#include "../src/ArrayStack.tpp"
