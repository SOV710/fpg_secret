#pragma once

#include "node.hpp"
#include "util.hpp"
#include <initializer_list>
#include <string>

namespace RBTREE {

//-------------------------------------------------------------------------------
//                              Red-Black Trees
//-------------------------------------------------------------------------------

template <KeyComparble Key> class RedBlackTree {
protected:
  using NodeT = RBTNode<Key>;
  using Color = typename RBTNode<Key>::Color;
  NodeT *root;

  // Basic BST operations
  NodeT *insertNode(NodeT *node, int key, NodeT *parent);
  NodeT *searchNode(NodeT *node, int key);
  NodeT *deleteNode(NodeT *root, NodeT *node);
  NodeT *minimumNode(NodeT *node);
  NodeT *maximumNode(NodeT *node);
  NodeT *successorNode(NodeT *node);
  void transplant(NodeT *u, NodeT *v);

  // Red-Black Tree specific operations
  void fixInsert(NodeT *node);
  void fixDelete(NodeT *node, NodeT *parent);
  NodeT *rotateLeft(NodeT *node);
  NodeT *rotateRight(NodeT *node);

  // Helper functions
  bool isRed(NodeT *node);
  void setColor(NodeT *node, Color color);
  Color getColor(NodeT *node);
  NodeT *getSibling(NodeT *node);

public:
  virtual ~RedBlackTree() = default;

  // Constructor
  RedBlackTree();
  RedBlackTree(std::initializer_list<int> list);
  virtual RedBlackTree &operator=(std::initializer_list<int> list);

  NodeT *getRoot();
  virtual void insert(int key);
  virtual NodeT *search(int key);
  virtual void remove(int key);
  NodeT *minimum();
  NodeT *maximum();
  NodeT *successor(int key);
  void printWithoutPrefix(NodeT *node);
  void printWithPrefix(const std::string &prefix, NodeT *node);
};

//-------------------------------------------------------------------------------
//                        RedBlackTree Implementation
//-------------------------------------------------------------------------------

template <KeyComparble Key> RedBlackTree<Key>::RedBlackTree() : root(nullptr) {}

template <KeyComparble Key>
RedBlackTree<Key>::RedBlackTree(std::initializer_list<int> list) {
  root = nullptr;
  for (int key : list) {
    insert(key);
  }
}

template <KeyComparble Key>
RedBlackTree<Key> &
RedBlackTree<Key>::operator=(std::initializer_list<int> list) {
  for (int key : list) {
    insert(key);
  }
  return *this;
}

template <KeyComparble Key>
RBTNode<Key> *RedBlackTree<Key>::insertNode(NodeT *node, int key,
                                            NodeT *parent) {
  if (node == nullptr) {
    NodeT *newNode = new NodeT(key);
    newNode->parent = parent;
    newNode->color = Color::RED; // New nodes are always red
    return newNode;
  }

  if (key < node->key) {
    node->left = insertNode(node->left, key, node);
  } else if (key > node->key) {
    node->right = insertNode(node->right, key, node);
  }

  return node;
}

template <KeyComparble Key>
RBTNode<Key> *RedBlackTree<Key>::searchNode(NodeT *node, int key) {
  if (node == nullptr || node->key == key) {
    return node;
  }
  if (key < node->key)
    return searchNode(node->left, key);
  else
    return searchNode(node->right, key);
}

template <KeyComparble Key>
void RedBlackTree<Key>::transplant(NodeT *u, NodeT *v) {
  if (u->parent == nullptr) {
    root = v;
  } else if (u == u->parent->left) {
    u->parent->left = v;
  } else {
    u->parent->right = v;
  }

  if (v != nullptr) {
    v->parent = u->parent;
  }
}

template <KeyComparble Key>
RBTNode<Key> *RedBlackTree<Key>::deleteNode(NodeT *root, NodeT *node) {
  if (node == nullptr) {
    return root;
  }

  NodeT *toDelete = node;
  NodeT *replacement = nullptr;
  Color originalColor = toDelete->color;

  if (node->left == nullptr) {
    replacement = node->right;
    transplant(node, node->right);
    if (originalColor == Color::BLACK && replacement != nullptr) {
      fixDelete(replacement, replacement->parent);
    } else if (originalColor == Color::BLACK && replacement == nullptr) {
      fixDelete(nullptr, node->parent);
    }
  } else if (node->right == nullptr) {
    replacement = node->left;
    transplant(node, node->left);
    if (originalColor == Color::BLACK && replacement != nullptr) {
      fixDelete(replacement, replacement->parent);
    } else if (originalColor == Color::BLACK && replacement == nullptr) {
      fixDelete(nullptr, node->parent);
    }
  } else {
    toDelete = minimumNode(node->right);
    originalColor = toDelete->color;
    replacement = toDelete->right;
    NodeT *replacementParent = toDelete;

    if (toDelete->parent != node) {
      replacementParent = toDelete->parent;
      transplant(toDelete, toDelete->right);
      toDelete->right = node->right;
      toDelete->right->parent = toDelete;
    } else {
      if (replacement != nullptr) {
        replacement->parent = toDelete;
      }
    }

    transplant(node, toDelete);
    toDelete->left = node->left;
    toDelete->left->parent = toDelete;
    toDelete->color = node->color;

    if (originalColor == Color::BLACK) {
      fixDelete(replacement, replacementParent);
    }
  }

  delete node;
  return this->root;
}

template <KeyComparble Key>
RBTNode<Key> *RedBlackTree<Key>::minimumNode(NodeT *node) {
  while (node->left != nullptr)
    node = node->left;
  return node;
}

template <KeyComparble Key>
RBTNode<Key> *RedBlackTree<Key>::maximumNode(NodeT *node) {
  while (node->right != nullptr)
    node = node->right;
  return node;
}

template <KeyComparble Key>
RBTNode<Key> *RedBlackTree<Key>::successorNode(NodeT *node) {
  if (node == nullptr)
    return nullptr;

  if (node->right != nullptr)
    return minimumNode(node->right);

  NodeT *originNode = node;
  NodeT *parent = node->parent;
  while (parent != nullptr && parent->right == node) {
    node = parent;
    parent = parent->parent;
  }
  if (parent == nullptr)
    return originNode;
  return parent;
}

template <KeyComparble Key>
RBTNode<Key> *RedBlackTree<Key>::rotateLeft(NodeT *z) {
  NodeT *y = z->right;
  NodeT *T2 = y->left;

  // Perform rotation
  y->left = z;
  z->right = T2;

  // Update parents
  y->parent = z->parent;
  z->parent = y;
  if (T2)
    T2->parent = z;

  // Update parent's pointer to this subtree
  if (y->parent == nullptr) {
    root = y;
  } else if (y->parent->left == z) {
    y->parent->left = y;
  } else {
    y->parent->right = y;
  }

  return y;
}

template <KeyComparble Key>
RBTNode<Key> *RedBlackTree<Key>::rotateRight(NodeT *z) {
  NodeT *y = z->left;
  NodeT *T3 = y->right;

  // Perform rotation
  y->right = z;
  z->left = T3;

  // Update parents
  y->parent = z->parent;
  z->parent = y;
  if (T3)
    T3->parent = z;

  // Update parent's pointer to this subtree
  if (y->parent == nullptr) {
    root = y;
  } else if (y->parent->left == z) {
    y->parent->left = y;
  } else {
    y->parent->right = y;
  }

  return y;
}

template <KeyComparble Key> void RedBlackTree<Key>::fixInsert(NodeT *node) {
  while (node != root && isRed(node->parent)) {
    if (node->parent == node->parent->parent->left) {
      // Parent is left child
      NodeT *uncle = node->parent->parent->right;

      if (isRed(uncle)) {
        // Case 1: Uncle is red - recolor
        setColor(node->parent, Color::BLACK);
        setColor(uncle, Color::BLACK);
        setColor(node->parent->parent, Color::RED);
        node = node->parent->parent;
      } else {
        if (node == node->parent->right) {
          // Case 2: Node is right child - left rotate
          node = node->parent;
          rotateLeft(node);
        }
        // Case 3: Node is left child - right rotate and recolor
        setColor(node->parent, Color::BLACK);
        setColor(node->parent->parent, Color::RED);
        rotateRight(node->parent->parent);
      }
    } else {
      // Parent is right child (mirror cases)
      NodeT *uncle = node->parent->parent->left;

      if (isRed(uncle)) {
        // Case 1: Uncle is red - recolor
        setColor(node->parent, Color::BLACK);
        setColor(uncle, Color::BLACK);
        setColor(node->parent->parent, Color::RED);
        node = node->parent->parent;
      } else {
        if (node == node->parent->left) {
          // Case 2: Node is left child - right rotate
          node = node->parent;
          rotateRight(node);
        }
        // Case 3: Node is right child - left rotate and recolor
        setColor(node->parent, Color::BLACK);
        setColor(node->parent->parent, Color::RED);
        rotateLeft(node->parent->parent);
      }
    }
  }
  setColor(root, Color::BLACK);
}

template <KeyComparble Key>
void RedBlackTree<Key>::fixDelete(NodeT *node, NodeT *parent) {
  while (node != root && getColor(node) == Color::BLACK) {
    if (node == (parent ? parent->left : nullptr)) {
      NodeT *sibling = parent ? parent->right : nullptr;

      if (isRed(sibling)) {
        // Case 1: Sibling is red
        setColor(sibling, Color::BLACK);
        setColor(parent, Color::RED);
        rotateLeft(parent);
        sibling = parent->right;
      }

      if (getColor(sibling ? sibling->left : nullptr) == Color::BLACK &&
          getColor(sibling ? sibling->right : nullptr) == Color::BLACK) {
        // Case 2: Sibling's children are both black
        setColor(sibling, Color::RED);
        node = parent;
        parent = node ? node->parent : nullptr;
      } else {
        if (getColor(sibling ? sibling->right : nullptr) == Color::BLACK) {
          // Case 3: Sibling's right child is black
          setColor(sibling->left, Color::BLACK);
          setColor(sibling, Color::RED);
          rotateRight(sibling);
          sibling = parent->right;
        }
        // Case 4: Sibling's right child is red
        setColor(sibling, getColor(parent));
        setColor(parent, Color::BLACK);
        setColor(sibling->right, Color::BLACK);
        rotateLeft(parent);
        node = root;
        break;
      }
    } else {
      // Mirror cases when node is right child
      NodeT *sibling = parent ? parent->left : nullptr;

      if (isRed(sibling)) {
        setColor(sibling, Color::BLACK);
        setColor(parent, Color::RED);
        rotateRight(parent);
        sibling = parent->left;
      }

      if (getColor(sibling ? sibling->right : nullptr) == Color::BLACK &&
          getColor(sibling ? sibling->left : nullptr) == Color::BLACK) {
        setColor(sibling, Color::RED);
        node = parent;
        parent = node ? node->parent : nullptr;
      } else {
        if (getColor(sibling ? sibling->left : nullptr) == Color::BLACK) {
          setColor(sibling->right, Color::BLACK);
          setColor(sibling, Color::RED);
          rotateLeft(sibling);
          sibling = parent->left;
        }
        setColor(sibling, getColor(parent));
        setColor(parent, Color::BLACK);
        setColor(sibling->left, Color::BLACK);
        rotateRight(parent);
        node = root;
        break;
      }
    }
  }
  setColor(node, Color::BLACK);
}

template <KeyComparble Key> bool RedBlackTree<Key>::isRed(NodeT *node) {
  return node != nullptr && node->color == Color::RED;
}

template <KeyComparble Key>
void RedBlackTree<Key>::setColor(NodeT *node, Color color) {
  if (node != nullptr) {
    node->color = color;
  }
}

template <KeyComparble Key>
typename RedBlackTree<Key>::Color RedBlackTree<Key>::getColor(NodeT *node) {
  return node ? node->color : Color::BLACK;
}

template <KeyComparble Key>
RBTNode<Key> *RedBlackTree<Key>::getSibling(NodeT *node) {
  if (node == nullptr || node->parent == nullptr)
    return nullptr;

  if (node == node->parent->left)
    return node->parent->right;
  else
    return node->parent->left;
}

template <KeyComparble Key> RBTNode<Key> *RedBlackTree<Key>::getRoot() {
  return root;
}

template <KeyComparble Key> void RedBlackTree<Key>::insert(int key) {
  root = insertNode(root, key, nullptr);

  // Find the newly inserted node
  NodeT *newNode = searchNode(root, key);
  if (newNode) {
    fixInsert(newNode);
  }
}

template <KeyComparble Key> RBTNode<Key> *RedBlackTree<Key>::search(int key) {
  return searchNode(root, key);
}

template <KeyComparble Key> void RedBlackTree<Key>::remove(int key) {
  NodeT *node = searchNode(root, key);
  if (node) {
    deleteNode(root, node);
  }
}

template <KeyComparble Key> RBTNode<Key> *RedBlackTree<Key>::minimum() {
  return minimumNode(root);
}

template <KeyComparble Key> RBTNode<Key> *RedBlackTree<Key>::maximum() {
  return maximumNode(root);
}

template <KeyComparble Key>
RBTNode<Key> *RedBlackTree<Key>::successor(int key) {
  NodeT *node = search(key);
  return successorNode(node);
}

template <KeyComparble Key>
void RedBlackTree<Key>::printWithoutPrefix(NodeT *node) {
  printTree("", node, false);
}

template <KeyComparble Key>
void RedBlackTree<Key>::printWithPrefix(const std::string &prefix,
                                        NodeT *node) {
  printTree(prefix, node, false);
}

} // namespace RBTREE
