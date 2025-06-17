#include <iostream>
#include <queue>
using namespace std;

class BinaryTree{
public:
    struct TreeNode{
        int data;
        TreeNode* left;
        TreeNode* right;
        TreeNode(int val):data(val),left(nullptr),right(nullptr){}
    };

    TreeNode* root;

    BinaryTree();
    ~BinaryTree();
    void insert(int data);
    int height();
    void preorder();
    void inorder();
    void postorder();
    void levelorder();//层序遍历

    private:
    //辅助函数声明为私有

    TreeNode* insertRecursive(TreeNode* node, int data);
    int sizeRecursive(TreeNode* node);
    int heightRecursive(TreeNode* node);
    void preorderRecursive(TreeNode* node);
    void inorderRecursive(TreeNode* node);
    void postorderRecursive(TreeNode* node);
    void destroyTree(TreeNode* node);


};

BinaryTree::BinaryTree():root(nullptr){}

BinaryTree::~BinaryTree(){
    destroyTree(root);
}

void BinaryTree::destroyTree(TreeNode* node){//类型void
    if(node!=nullptr){
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

void BinaryTree::insert(int data){
    root = insertRecursive(root,data);
}

BinaryTree::TreeNode* BinaryTree::insertRecursive(TreeNode* node, int data){
    //返回指向TreeNode的指针
    if(node==nullptr){
        return new TreeNode(data);//返回一个根节点
    }
    if(data>node->data){
        node->left=insertRecursive(node->left,data);
    }
    else if(node->data>data){
        node->right=insertRecursive(node->right,data);
    }

    return node;
}

int BinaryTree::height(){
    return heightRecursive(root);
}

int BinaryTree::heightRecursive(TreeNode* node){
    if(node==nullptr)
        return 0;
    else return(1+max(heightRecursive(node->left),heightRecursive(node->right)));
}

//前序遍历实现
void BinaryTree::preorder(){
    preorderRecursive(root);
    cout<<endl;
}

void BinaryTree::preorderRecursive(TreeNode* node){
    if(node!=nullptr){
        cout<< node->data <<" ";
        preorderRecursive(node->left);
        preorderRecursive(node->right);
    }
}

// 中序遍历实现
void BinaryTree::inorder() {
    inorderRecursive(root);
    cout << endl;
}

void BinaryTree::inorderRecursive(TreeNode* node) {
    if (node != nullptr) {
        inorderRecursive(node->left);
        cout << node->data << " ";
        inorderRecursive(node->right);
    }
}

// 后序遍历实现
void BinaryTree::postorder() {
    postorderRecursive(root);
    cout << endl;
}

void BinaryTree::postorderRecursive(TreeNode* node) {
    if (node != nullptr) {
        postorderRecursive(node->left);
        postorderRecursive(node->right);
        cout << node->data << " ";
    }
}
//需要一个节点队列
void BinaryTree::levelorder(){
    if(root == nullptr) return;

    queue<TreeNode*> q;
    q.push(root);//输入
    
    while(!q.empty()){
        TreeNode* current = q.front();
        q.pop();
        cout<<current->data<<endl;

        if(current->left!=nullptr){
            q.push(current->left);
        }

        if(current->right!=nullptr){
            q.push(current->right);
        }
    }

    cout<<endl;

}

int main() {
    BinaryTree tree;
    
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(2);
    tree.insert(4);
    tree.insert(6);
    tree.insert(8);
    
    cout << "前序遍历: ";
    tree.preorder();
    
    cout << "中序遍历: ";
    tree.inorder();
    
    cout << "后序遍历: ";
    tree.postorder();
    
    cout << "层序遍历: ";
    tree.levelorder();
    
    cout << "树的高度: " << tree.height() << endl;
    
    return 0;
}