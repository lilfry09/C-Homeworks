#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <functional>
#include <iostream>
#include <queue>
#include <stack>
#include <unordered_set>
#include <vector>

using namespace std;

template <class T, T NULL_VALUE> class BinaryTree;
template <class T, T NULL_VALUE> class Node {
  friend class BinaryTree<T, NULL_VALUE>; // 允许访问私有成员

private:
  T data;
  Node *left, *right;
  // 以下两个flag供线索二叉树中序遍历使用，将在后续介绍
  int leftFlag; // 用于标识是否线索，0时left为左孩子结点，1时为前驱线索
  int rightFlag; // 用于标识是否线索，0时right为右孩子结点，1时为后继线索

public:
  Node() : left(nullptr), right(nullptr), leftFlag(0), rightFlag(0) {}
  Node(const T &e, Node *L = nullptr, Node *R = nullptr)
      : data(e), left(L), right(R), leftFlag(0), rightFlag(0) {}
};

template <class T, T NULL_VALUE> class BinaryTree {
private:
  Node<T, NULL_VALUE> *root;
  int _size(Node<T, NULL_VALUE> *t); // 求以t为根的二叉树的结点个数。
  int _height(Node<T, NULL_VALUE> *t); // 求以t为根的二叉树的高度。
  void _del_tree(Node<T, NULL_VALUE> *t); // 删除以t为根的二叉树

  // 按前序遍历输出以t为根的二叉树的结点的数据值
  void _pre_order(Node<T, NULL_VALUE> *t);
  // 按中序遍历输出以t为根的二叉树的结点的数据值
  void _in_order(Node<T, NULL_VALUE> *t);
  // 按后序遍历输出以t为根的二叉树的结点的数据值
  void _post_order(Node<T, NULL_VALUE> *t);

public:
  BinaryTree() : root(nullptr) {}
  BinaryTree(const std::vector<T> &v);         // 由vector构造二叉树
  BinaryTree(const BinaryTree &t) = delete;    // 禁用拷贝构造函数
  BinaryTree(BinaryTree &&t);                  // 移动构造函数
  ~BinaryTree() { delTree(); }                 // 析构函数
  bool isEmpty() { return (root == nullptr); } // 二叉树为空返回true
  Node<T, NULL_VALUE> *getRoot() { return root; }

  int size();        // 求二叉树的结点个数。
  int height();      // 求二叉树的高度。
  void delTree();    // 删除二叉树
  void preOrder();   // 按前序遍历输出二叉树的结点的数据值
  void inOrder();    // 按中序遍历输出二叉树的结点的数据值
  void postOrder();  // 按后序遍历输出二叉树的结点的数据值
  void levelOrder(); // 按层次遍历输出二叉树的结点的数据值

  void buildTreePreIn(const std::vector<T> &pre, const std::vector<T> &in);
};

template <class T, T NULL_VALUE>
BinaryTree<T, NULL_VALUE>::BinaryTree(const std::vector<T> &v) {
  // 若vector为空，返回空二叉树
  if (v.empty()) {
    root = nullptr;
    return;
  }

  // 使用队列来逐节点构造二叉树
  queue<Node<T, NULL_VALUE> *> q;
  root = new Node<T, NULL_VALUE>(v[0]);
  q.push(root);

  for (int i = 1; i < v.size(); i += 2) {
    // 获取队首当前操作节点
    Node<T, NULL_VALUE> *p = q.front();
    q.pop();

    // 查看输入数据是否为空值，若不是则构造左右孩子结点
    if (v[i] != NULL_VALUE) {
      p->left = new Node<T, NULL_VALUE>(v[i]);
      q.push(p->left);
    }
    // 注意输入可能没有末尾的NULL_VALUE，所以需要判断是否越界
    if (i + 1 < v.size() && v[i + 1] != NULL_VALUE) {
      p->right = new Node<T, NULL_VALUE>(v[i + 1]);
      q.push(p->right);
    }
  }
}

template <class T, T NULL_VALUE>
BinaryTree<T, NULL_VALUE>::BinaryTree(BinaryTree &&t) {
  root = t.root; // 移动构造函数，直接将t的根节点指针赋值给当前对象
  root = nullptr; // 将t的根节点置空，避免析构时重复释放内存
}

template <class T, T NULL_VALUE>
int BinaryTree<T, NULL_VALUE>::_size(Node<T, NULL_VALUE> *t) {
  if (t == nullptr) // 遍历到空结点，返回0
    return 0;
  return 1 + _size(t->left) + _size(t->right); // 递归求解
}

template <class T, T NULL_VALUE>
int BinaryTree<T, NULL_VALUE>::_height(Node<T, NULL_VALUE> *t) {
  if (t == nullptr) // 遍历到空结点，返回0
    return 0;
  int hl = _height(t->left);              // 递归求解左子树高度
  int hr = _height(t->right);             // 递归求解右子树高度
  return (hl > hr) ? (hl + 1) : (hr + 1); // 返回左右子树高度的最大值加1
}

template <class T, T NULL_VALUE>
void BinaryTree<T, NULL_VALUE>::_del_tree(Node<T, NULL_VALUE> *t) {
  if (t == nullptr) // 递归终止条件，遍历到空结点
    return;

  _del_tree(t->left);  // 递归删除左子树
  _del_tree(t->right); // 递归删除右子树
  delete t;            // 删除当前结点
}

template <class T, T NULL_VALUE>
void BinaryTree<T, NULL_VALUE>::_pre_order(Node<T, NULL_VALUE> *t) {
  // 初始化前序遍历栈
  stack<Node<T, NULL_VALUE> *> s;
  s.push(t);

  // 开始前序遍历
  while (!s.empty()) {
    // 获取栈顶元素并弹出
    Node<T, NULL_VALUE> *p = s.top();
    s.pop();
    cout << p->data << " ";

    if (p->right != nullptr) // 右节点存在则入栈
      s.push(p->right);
    if (p->left != nullptr) // 左节点存在则入栈
      s.push(p->left);
  }
}

template <class T, T NULL_VALUE>
void BinaryTree<T, NULL_VALUE>::_in_order(Node<T, NULL_VALUE> *t) {
  // 初始化中序遍历栈
  stack<Node<T, NULL_VALUE> *> s;
  stack<int> flag; // 标记是第几次访问
  auto push_node = [&s, &flag](Node<T, NULL_VALUE> *p, int f) {
    s.push(p);    // 当前节点入栈
    flag.push(f); // 标记入栈
  };
  push_node(t, 0); // 根节点入栈，设置标志位为0

  // 开始中序遍历
  while (!s.empty()) {
    Node<T, NULL_VALUE> *p = s.top();
    int f = flag.top();
    s.pop();
    flag.pop();

    if (f == 0) {             // 如果当前是第一次访问
      push_node(p, 1);        // 标记为第二次访问
      if (p->left != nullptr) // 若左节点存在则入栈
        push_node(p->left, 0);
    } else {                   // 如果当前是第二次访问
      cout << p->data << " ";  // 输出当前节点
      if (p->right != nullptr) // 若右节点存在则入栈
        push_node(p->right, 0);
    }
  }
}

template <class T, T NULL_VALUE>
void BinaryTree<T, NULL_VALUE>::_post_order(Node<T, NULL_VALUE> *t) {
  // 初始化后序遍历栈
  stack<Node<T, NULL_VALUE> *> s;
  stack<int> flag; // 标记是第几次访问
  auto push_node = [&s, &flag](Node<T, NULL_VALUE> *p, int f) {
    s.push(p);    // 当前节点入栈
    flag.push(f); // 标记入栈
  };
  push_node(t, 0); // 根节点入栈，设置标志位为0

  // 开始后序遍历
  while (!s.empty()) {
    Node<T, NULL_VALUE> *p = s.top();
    int f = flag.top();
    s.pop();
    flag.pop();

    if (f == 0) {             // 如果当前是第一次访问
      push_node(p, 1);        // 标记为已访问一次
      if (p->left != nullptr) // 若左节点存在则入栈
        push_node(p->left, 0);
    } else if (f == 1) {       // 如果当前是第二次访问
      push_node(p, 2);         // 标记为已访问两次
      if (p->right != nullptr) // 若右节点存在则入栈
        push_node(p->right, 0);
    } else                    // 如果当前是第三次访问
      cout << p->data << " "; // 输出当前节点
  }
}

template <class T, T NULL_VALUE> int BinaryTree<T, NULL_VALUE>::size() {
  return _size(root); // 调用私有递归函数求二叉树的结点个数
}

template <class T, T NULL_VALUE> int BinaryTree<T, NULL_VALUE>::height() {
  return _height(root); // 调用私有递归函数求二叉树的高度
}

template <class T, T NULL_VALUE> void BinaryTree<T, NULL_VALUE>::delTree() {
  _del_tree(root);
  root = nullptr; // 删除二叉树后，根节点置空
}

template <class T, T NULL_VALUE> void BinaryTree<T, NULL_VALUE>::preOrder() {
  _pre_order(root);
  cout << endl;
}

template <class T, T NULL_VALUE> void BinaryTree<T, NULL_VALUE>::inOrder() {
  _in_order(root);
  cout << endl;
}

template <class T, T NULL_VALUE> void BinaryTree<T, NULL_VALUE>::postOrder() {
  _post_order(root);
  cout << endl;
}

template <class T, T NULL_VALUE> void BinaryTree<T, NULL_VALUE>::levelOrder() {
  // 若根节点为空，直接返回
  if (root == nullptr)
    return;

  // 使用队列来逐层输出二叉树的结点数据值
  queue<Node<T, NULL_VALUE> *> q;
  q.push(root); // 根节点入队

  while (!q.empty()) {
    // 获取队首元素并出队
    auto p = q.front();
    q.pop();

    cout << p->data << " "; // 输出当前结点的数据值
    if (p->left != nullptr) // 左孩子结点入队
      q.push(p->left);
    if (p->right != nullptr) // 右孩子结点入队
      q.push(p->right);
  }

  cout << endl;
}

template <class T, T NULL_VALUE>
void BinaryTree<T, NULL_VALUE>::buildTreePreIn(const std::vector<T> &pre,
                                               const std::vector<T> &in) {
  // 确认输入序列不为空且长度相同
  if (pre.empty() || in.empty() || pre.size() != in.size())
    return;
  // 确认两个序列中元素相同且不出现重复元素
  unordered_set<T> pre_set(pre.begin(), pre.end());
  unordered_set<T> in_set(in.begin(), in.end());
  if (pre_set != in_set || pre_set.size() != pre.size())
    return;

  // 使用前序和中序序列构造二叉树
  // 定义匿名函数用于递归
  function<Node<T, NULL_VALUE> *(int, int, int, int)> build =
      [&](int pre_l, int pre_r, int in_l, int in_r) -> Node<T, NULL_VALUE> * {
    if (pre_l > pre_r || in_l > in_r) // 递归终止条件
      return nullptr;

    // 使用前序序列第一个元素构造根节点
    Node<T, NULL_VALUE> *root = new Node<T, NULL_VALUE>(pre[pre_l]);
    int i = in_l; // 在中序序列中找到根节点的位置
    while (i <= in_r && in[i] != pre[pre_l])
      ++i;
    int left_size = i - in_l; // 左子树的结点个数
    root->left = build(pre_l + 1, pre_l + left_size, in_l, i - 1); // 递归左子
    root->right = build(pre_l + left_size + 1, pre_r, i + 1, in_r); // 递归右子
    return root;
  };

  // 删除原有二叉树并构造新的二叉树
  delTree();
  root = build(0, pre.size() - 1, 0, in.size() - 1);
}

#endif // BINARY_TREE_H
