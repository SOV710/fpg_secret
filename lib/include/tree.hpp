#pragma once

#include "node.hpp"
#include "util.hpp"
#include <algorithm>
#include <initializer_list>
#include <string>

namespace TREE {

//-------------------------------------------------------------------------------
//                              Binary Search Trees
//-------------------------------------------------------------------------------

template <KeyComparble Key> class BinarySearchTree {
protected:
  using NodeT = BSTNode<Key>;
  NodeT *root;

  virtual NodeT *insertNode(NodeT *node, int key, NodeT *parent);
  NodeT *searchNode(NodeT *node, int key);
  void transplant(NodeT *u, NodeT *v);
  virtual NodeT *deleteNode(NodeT *root, NodeT *node);
  NodeT *minimumNode(NodeT *node);
  NodeT *maximumNode(NodeT *node);
  NodeT *successorNode(NodeT *node);

  NodeT *rotateLeft(NodeT *z);
  NodeT *rotateRight(NodeT *z);

public:
  virtual ~BinarySearchTree() = default;

  // Constructor
  BinarySearchTree();
  BinarySearchTree(std::initializer_list<int> list);
  virtual BinarySearchTree &operator=(std::initializer_list<int> list);

  NodeT *getRoot();
  virtual void insert(int key);
  virtual NodeT *search(int key);
  virtual void remove(int key);
  NodeT *minimum();
  NodeT *maximum();
  NodeT *successor(int key);
  void printWithoutPrefix(NodeT *node);
  void printWithPrefix(const std::string &prefix, NodeT *node);

  int getHeight(NodeT *node);
  int getBalance(NodeT *node);
  void updateHeight(NodeT *node);
};

//-------------------------------------------------------------------------------
//                                   AVL Trees
//-------------------------------------------------------------------------------

template <KeyComparble Key> class AVLTree : public BinarySearchTree<Key> {
protected:
  using NodeT = BSTNode<Key>;
  NodeT *balance(NodeT *node, int key);

  NodeT *insertNode(NodeT *node, int key, NodeT *parent) override;
  NodeT *deleteNode(NodeT *root, NodeT *node) override;

public:
  AVLTree();
  AVLTree(std::initializer_list<int> list);
  AVLTree &operator=(std::initializer_list<int> list) override;

  void insert(int key) override;
  NodeT *search(int key) override;
  void remove(int key) override;
};

//-------------------------------------------------------------------------------
//                        BinarySearchTree Implementation
//-------------------------------------------------------------------------------

template <KeyComparble Key>
BinarySearchTree<Key>::BinarySearchTree() : root(nullptr) {}

template <KeyComparble Key>
BinarySearchTree<Key>::BinarySearchTree(std::initializer_list<int> list) {
  root = nullptr;
  for (int key : list) {
    BinarySearchTree::insert(key);
  }
}

template <KeyComparble Key>
BinarySearchTree<Key> &
BinarySearchTree<Key>::operator=(std::initializer_list<int> list) {
  for (int key : list) {
    BinarySearchTree::insert(key);
  }

  return *this;
}

template <KeyComparble Key>
BSTNode<Key> *BinarySearchTree<Key>::insertNode(NodeT *node, int key,
                                                NodeT *parent) {
  if (node == nullptr) { // check value, if not exist, create it
    NodeT *newNode = new NodeT(key);
    newNode->parent = parent;
    if (!root)
      root = newNode; // maintain the root
    return newNode;
  }

  // recursively search for appropriate place
  if (key < node->key) {
    node->left = insertNode(node->left, key, node);
    node->left->parent = node;
  } else {
    node->right = insertNode(node->right, key, node);
    node->right->parent = node;
  }
  return node; // return parent node, recursively return root
}

template <KeyComparble Key>
BSTNode<Key> *BinarySearchTree<Key>::searchNode(NodeT *node, int key) {
  if (node == nullptr || node->key == key) { // check value
    return node;
  }
  if (key < node->key) // search left subtree
    return searchNode(node->left, key);
  else // search right subtree
    return searchNode(node->right, key);
}

template <KeyComparble Key>
void BinarySearchTree<Key>::transplant(NodeT *u,
                                       NodeT *v) { // used to replace u with v
  if (u->parent == nullptr)
    // if u is the root
    this->root = v;
  else if (u == u->parent->left)
    // if u is parent's left child,replace u with v directly
    u->parent->left = v;
  else
    u->parent->right = v;

  if (v != nullptr) { // replace v's parent with u's parent
    v->parent = u->parent;
  }
}

template <KeyComparble Key>
BSTNode<Key> *BinarySearchTree<Key>::deleteNode(NodeT *root, NodeT *node) {
  if (root == nullptr) // nothing to delete
    return root;

  if (node->left == nullptr)
    // cases on node doesn't have left subtrees
    transplant(node, node->right);
  else if (node->right == nullptr)
    // cases on node doesn't have right subtrees
    transplant(node, node->left);
  else {
    // cases on node both have left and right child
    NodeT *sec = minimumNode(node->right); // successor
    if (sec->parent != node) {
      transplant(sec, sec->right);
      sec->right = node->right;
      sec->right->parent = sec;
    }
    transplant(node, sec);
    sec->left = node->left;
    sec->left->parent = sec;
  }
  return root;
}

template <KeyComparble Key>
BSTNode<Key> *BinarySearchTree<Key>::minimumNode(NodeT *node) {
  while (node->left != nullptr)
    node = node->left;
  return node;
}

template <KeyComparble Key>
BSTNode<Key> *BinarySearchTree<Key>::maximumNode(NodeT *node) {
  while (node->right != nullptr)
    node = node->right;
  return node;
}

template <KeyComparble Key>
BSTNode<Key> *BinarySearchTree<Key>::successorNode(NodeT *node) {
  if (node == nullptr)
    return nullptr;

  if (node->right != nullptr)
    return minimumNode(node->right);

  NodeT *originNode = node; // prepared for nullptr protection

  NodeT *parent = node->parent;
  while (parent != nullptr && parent->right == node) {
    node = parent;
    parent = parent->parent;
  }
  if (parent == nullptr) // nullptr protection
    return originNode;
  return parent;
}

template <KeyComparble Key>
BSTNode<Key> *BinarySearchTree<Key>::rotateLeft(NodeT *z) {
  NodeT *y = z->right;
  NodeT *T2 = y->left;

  // Perform rotation
  z->right = T2;

  // Update parents
  z->parent = y;
  if (T2)
    T2->parent = z;

  // Update parent's pointer to this subtree
  if (y->parent == nullptr) {
    this->root = y;
  } else if (y->parent->left == z) {
    y->parent->left = y;
  } else {
    y->parent->right = y;
  }

  // Update heights
  updateHeight(z);
  updateHeight(y);

  return y; // y becomes the new root of the subtree
}

template <KeyComparble Key>
BSTNode<Key> *BinarySearchTree<Key>::rotateRight(NodeT *z) {
  NodeT *y = z->left;
  NodeT *T3 = y->right;

  // Perform rotation
  z->left = T3;

  // Update parents
  z->parent = y;
  if (T3)
    T3->parent = z;

  // Update parent's pointer to this subtree
  if (y->parent == nullptr) {
    this->root = y;
  } else if (y->parent->left == z) {
    y->parent->left = y;
  } else {
    y->parent->right = y;
  }

  // Update heights
  updateHeight(z);
  updateHeight(y);

  return y; // y becomes the new root of the subtree
}

template <KeyComparble Key> BSTNode<Key> *BinarySearchTree<Key>::getRoot() {
  return root;
}

template <KeyComparble Key> void BinarySearchTree<Key>::insert(int key) {
  root = insertNode(root, key, nullptr);
}

template <KeyComparble Key>
BSTNode<Key> *BinarySearchTree<Key>::search(int key) {
  return searchNode(root, key);
}

template <KeyComparble Key> void BinarySearchTree<Key>::remove(int key) {
  deleteNode(root, searchNode(root, key));
}

template <KeyComparble Key> BSTNode<Key> *BinarySearchTree<Key>::minimum() {
  return minimumNode(root);
}

template <KeyComparble Key> BSTNode<Key> *BinarySearchTree<Key>::maximum() {
  return maximumNode(root);
}

template <KeyComparble Key>
BSTNode<Key> *BinarySearchTree<Key>::successor(int key) {
  NodeT *node = search(key);
  return successorNode(node);
}

template <KeyComparble Key>
void BinarySearchTree<Key>::printWithoutPrefix(NodeT *node) {
  printTree("", node, false);
}

template <KeyComparble Key>
void BinarySearchTree<Key>::printWithPrefix(const std::string &string,
                                            NodeT *node) {
  printTree(string, node, false);
}

template <KeyComparble Key> int BinarySearchTree<Key>::getHeight(NodeT *node) {
  return node ? node->height : 0;
}

template <KeyComparble Key> int BinarySearchTree<Key>::getBalance(NodeT *node) {
  return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

template <KeyComparble Key>
void BinarySearchTree<Key>::updateHeight(NodeT *node) {
  if (!node)
    return;
  node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
}

//-------------------------------------------------------------------------------
//                            AVLTree Implementation
//-------------------------------------------------------------------------------

template <KeyComparble Key> AVLTree<Key>::AVLTree() { this->root = nullptr; }

template <KeyComparble Key>
AVLTree<Key>::AVLTree(std::initializer_list<int> list) {
  this->root = nullptr;
  for (auto key : list)
    AVLTree::insert(key);
}

template <KeyComparble Key>
AVLTree<Key> &AVLTree<Key>::operator=(std::initializer_list<int> list) {
  for (auto key : list)
    AVLTree::insert(key);

  return *this;
}

template <KeyComparble Key>
BSTNode<Key> *AVLTree<Key>::balance(NodeT *node, int key) {
  int balance = this->getBalance(node);

  // LL case： left tree is higher. and the insertion point is on the left side
  // of the left subtree
  if (balance > 1 && key < node->left->key) {
    return this->rotateRight(node);
  }

  // RR case： right subtree is higher, and insertion point is on the right side
  // of the right subtree
  if (balance < -1 && key < node->right->key) {
    return this->rotateLeft(node);
  }

  // LR case： left subtree is higher, but insertion point is on the right of
  // the left subtree
  if (balance > 1 && key > node->left->key) {
    node->left = this->rotateLeft(node->left);
    return this->rotateRight(node);
  }

  // RL case： right subtree is higher, but insertion point is on the left side
  // of the right subtree
  if (balance < -1 && key < node->right->key) {
    node->right = this->rotateRight(node->right);
    return this->rotateLeft(node);
  }

  return node;
}

template <KeyComparble Key>
BSTNode<Key> *AVLTree<Key>::insertNode(NodeT *node, int key, NodeT *parent) {
  if (node == nullptr) { // check value, if not exist, create it
    NodeT *newNode = new NodeT(key);
    newNode->parent = parent;
    if (this->root == nullptr)
      this->root = newNode; // maintain the root
    return newNode;
  }

  // recursively search for appropriate place
  if (key < node->key) {
    node->left = insertNode(node->left, key, node);
    node->left->parent = node;
  } else if (key > node->key) {
    node->right = insertNode(node->right, key, node);
    node->right->parent = node;
  } else
    return node;

  this->updateHeight(node);

  return balance(node, key);
}

template <KeyComparble Key>
BSTNode<Key> *AVLTree<Key>::deleteNode(NodeT *root, NodeT *node) {
  if (node == nullptr) {
    // Node to be deleted not found, just return root
    return root;
  }

  NodeT *parent =
      node->parent; // keep track of the parent for later rebalancing
  NodeT *rebalanceStart = nullptr; // the node from which we start rebalancing

  // Standard BST Deletion
  if (node->left == nullptr && node->right == nullptr) {
    // No children
    rebalanceStart = node->parent;
    this->transplant(node, nullptr);
    delete node;
  } else if (node->left == nullptr) {
    // One child (right)
    rebalanceStart = node->right; // after deletion, we will start rebalancing
                                  // from here or its parent
    this->transplant(node, node->right);
    delete node;
  } else if (node->right == nullptr) {
    // One child (left)
    rebalanceStart = node->left;
    this->transplant(node, node->left);
    delete node;
  } else {
    // Two children
    NodeT *sec = this->minimumNode(node->right); // successor
    // We'll rebalance from successor or its parent after re-linking
    if (sec->parent != node) {
      // If successor is not the direct child of node
      rebalanceStart = sec->parent;
      this->transplant(sec, sec->right);
      sec->right = node->right;
      if (sec->right)
        sec->right->parent = sec;
    } else {
      // Successor is the direct right child of node
      rebalanceStart = sec; // since we are reattaching sec to node's position
    }
    this->transplant(node, sec);
    sec->left = node->left;
    if (sec->left)
      sec->left->parent = sec;

    delete node;
  }

  // Now rebalance the tree starting from rebalanceStart and moving upwards
  // If rebalanceStart is nullptr, use parent (this can happen if we deleted the
  // root)
  NodeT *cur = (rebalanceStart) ? rebalanceStart : parent;

  while (cur != nullptr) {
    this->updateHeight(cur);
    // Use cur->key as the reference key for balancing
    cur = balance(cur, cur->key);
    if (cur->parent == nullptr) {
      // If this is now the root after balancing, update the class's root
      // pointer
      this->root = cur;
    }
    cur = cur->parent;
  }

  return this->root; // Return the (possibly new) root of this subtree
}

template <KeyComparble Key> void AVLTree<Key>::insert(int key) {
  this->root = insertNode(this->root, key, nullptr);
}

template <KeyComparble Key> BSTNode<Key> *AVLTree<Key>::search(int key) {
  return this->searchNode(this->root, key);
}

template <KeyComparble Key> void AVLTree<Key>::remove(int key) {
  deleteNode(this->root, this->searchNode(this->root, key));
}

} // namespace TREE
