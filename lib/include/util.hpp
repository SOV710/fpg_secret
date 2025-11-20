#pragma once

#include "node.hpp"
#include <string>
#include <iostream>

void swap(int *i, int *j);

void printArray(int arr[], int size);

template <KeyComparble Key>
void printTree(const std::string &prefix, BSTNode<Key> *node, bool isLeft) {
  if (node == nullptr)
    return;
  else {
    std::cout << prefix;
    std::cout << (isLeft ? "├──" : "└──");
    std::cout << node->key << std::endl;

    printTree(prefix + (isLeft ? "│   " : "    "), node->left, true);
    printTree(prefix + (isLeft ? "│   " : "    "), node->right, false);
  }
}
