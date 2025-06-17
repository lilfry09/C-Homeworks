#include<iostream>
using namespace std;
class BinarySearchTree{
public:
    struct TreeNode {
        int data;
        TreeNode* left;
        TreeNode* right;
        TreeNode(int val):data(val),left(nullptr),right(nullptr){}

    };

    BinarySearchTree():root(nullptr);

    TreeNode* root;
    bool search(TreeNode* root,int key);

    void insert(int data);
    void remove(int data);

private:
    TreeNode* insertRecursive(TreeNode* node,int data);
    TreeNode* Search(TreeNode* node,int key);

};

void BinarySearchTree::insert(int data){
    root=insertRecursive(root,data);
}

BinarySearchTree::TreeNode* BinarySearchTree::insertRecursive(TreeNode* node,int data){
    if(node==nullptr){
        return new TreeNode(data);
    }
    if(node->data>data){
        node->left=insertRecursive(node->left,data);
    }else{
        node->right=insertRecursive(node->right,data);
    }

    return node;
}

bool BinarySearchTree::search(TreeNode* root,int key){
    return Search(root,key)!=nullptr;
}

BinarySearchTree::TreeNode* BinarySearchTree::Search(TreeNode* node,int data){
    if(node==nullptr) return nullptr;
    if(data>node->data){
        Search(node->right,data);
    }
    else if(data<node->data){
        Search(node->left,data);
    }
    else{
        return node;
    }
}



int main(){
    BinarySearchTree tree;





    return 0;
}