// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <algorithm>

template<typename T>
class BST {
 public:
  struct Node {
    T       key;
    int     count;
    Node*   left;
    Node*   right;
    explicit Node(const T& value)
        : key(value), count(1), left(nullptr), right(nullptr) {}
  };

  BST() : root(nullptr) {}

  ~BST() { clear(root); }

  void add(const T& value) { root = addNode(root, value); }

  int search(const T& value) const {
    Node* node = searchNode(root, value);
    return node ? node->count : 0;
  }

  int depth() const { return depthNode(root); }

  template<typename Visitor>
  void inorder(Visitor visit) const { inorderNode(root, visit); }

 private:
  Node* root;

  Node* addNode(Node* node, const T& value) {
    if (node == nullptr)
      return new Node(value);
    if (value < node->key)
      node->left = addNode(node->left, value);
    else if (value > node->key)
      node->right = addNode(node->right, value);
    else
      node->count++;
    return node;
  }

  Node* searchNode(Node* node, const T& value) const {
    if (node == nullptr || node->key == value)
      return node;
    if (value < node->key)
      return searchNode(node->left, value);
    return searchNode(node->right, value);
  }

  int depthNode(Node* node) const {
    if (node == nullptr)
      return -1;
    return 1 + std::max(depthNode(node->left), depthNode(node->right));
  }

  template<typename Visitor>
  void inorderNode(Node* node, Visitor& visit) const {
    if (node == nullptr)
      return;
    inorderNode(node->left, visit);
    visit(node->key, node->count);
    inorderNode(node->right, visit);
  }

  void clear(Node* node) {
    if (node == nullptr)
      return;
    clear(node->left);
    clear(node->right);
    delete node;
  }
};

#endif  // INCLUDE_BST_H_
