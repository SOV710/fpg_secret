#pragma once
#include <concepts>

template <typename Key>
concept KeyComparble = std::totally_ordered<Key>;

template <KeyComparble Key> struct BSTNode {
  using key_type = Key;

  key_type key;
  BSTNode *left{nullptr};
  BSTNode *right{nullptr};
  BSTNode *parent{nullptr};
  int height{1};

  explicit BSTNode(const key_type &k) noexcept : key(k) {}

  BSTNode(const BSTNode &) = delete;
  BSTNode &operator=(const BSTNode &) = delete;
  BSTNode(BSTNode &&) noexcept = default;
  BSTNode &operator=(BSTNode &&) noexcept = default;

  ~BSTNode() = default;
};

template <KeyComparble Key> struct RBTNode {
  using key_type = Key;

  enum Color { RED, BLACK };

  key_type key;
  RBTNode *left{nullptr};
  RBTNode *right{nullptr};
  RBTNode *parent{nullptr};
  Color color{RED}; // New node default red

  explicit RBTNode(const key_type &k) noexcept : key(k) {}

  RBTNode(const RBTNode &) = delete;
  RBTNode &operator=(const RBTNode &) = delete;
  RBTNode(RBTNode &&) noexcept = default;
  RBTNode &operator=(RBTNode &&) noexcept = default;

  ~RBTNode() = default;
};
