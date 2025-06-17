struct NAryTree
{
    int val;
    vector<NAryTree*> children;
} node;

struct BinaryTree
{
    int val;
    BinaryTree *lson, *rson;//左右儿子
    BinaryTree(const int k) { val = k, lson = rson = NULL; }
} node;

// n-ary tree to binary tree: "transform.cpp"
#ifndef NAryTree_To_BinaryTree
#define NAryTree_To_BinaryTree

#include "tree.hpp"

BinaryTree* Transform(const NAryTree *node)
{
    if(!node) return nullptr;
    
    BinaryTree *root = new BinaryTree(node->val);
    BinaryTree *current = nullptr;
    
    for(auto &nchild : node->children){
        BinaryTree *newchild = Transform(nchild);
        
        if(current!=nullptr) 
            root->lson = newchild;  // 第一个子节点作为左孩子
        else 
            current->rson = newchild;  // 其他子节点作为右兄弟
        
        current = newchild;  // 移动当前指针
    }
    return root;
}


#endif