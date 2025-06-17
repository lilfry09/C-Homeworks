#include "binary_tree.h"

int main() {
  // construct a binary tree with the following data
  static const vector<int> binary_tree_data = {0, 1, 2, 3, -1, 4, 5};
  BinaryTree<int, -1> binary_tree(binary_tree_data);

  // print the binary tree in pre-order, in-order, post-order, and level-order
  binary_tree.preOrder();
  binary_tree.inOrder();
  binary_tree.postOrder();
  binary_tree.levelOrder();
  cout << endl;

  // construct a binary tree use Pre-order and In-order traversal
  static const vector<int> pre_order = {0, 1, 3, 2, 4, 5};
  static const vector<int> in_order = {3, 1, 0, 4, 2, 5};
  binary_tree.buildTreePreIn(pre_order, in_order);

  // print the binary tree in pre-order, in-order, post-order, and level-order
  binary_tree.preOrder();
  binary_tree.inOrder();
  binary_tree.postOrder();
  binary_tree.levelOrder();

  return 0;
}
