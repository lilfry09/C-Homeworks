#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
 struct TreeNode{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x): val(x),left(nullptr),right(nullptr){}
};

TreeNode* createBinaryTree(int n){//create tree
    vector<TreeNode*> nodeVec(n);//节点

    for(int i=0;i<n;i++){
        nodeVec[i]=new TreeNode(i+1);//create node
    }

    for(int i=0;i<n;i++){
        int leftval,rightval;
        cin>>leftval>>rightval;
        if(leftval==0) nodeVec[i]->left=nullptr;
        else{
            nodeVec[i]->left=nodeVec[leftval-1];
        }
        if(rightval==0) nodeVec[i]->right=nullptr;
        else{
            nodeVec[i]->right=nodeVec[rightval-1];
        }
    }
    return nodeVec[0];
}

// 前序遍历
// void preorderTraversal(TreeNode* root) {
//     if (root == nullptr) {
//         return;
//     }
//     cout << root->val << " ";
//     preorderTraversal(root->left);
//     preorderTraversal(root->right);
// }

TreeNode* findNode(TreeNode* root, int a) {
    // 递归终止条件：当前节点为空时返回nullptr
    if (root == nullptr) {
        return nullptr;
    }
    
    // 找到目标值时返回当前节点
    if (root->val == a) {
        return root;//找到值是a的那个点
    }
    
    // 递归搜索左子树
    TreeNode* left = findNode(root->left, a);
    if (left != nullptr) {
        return left; // 左子树找到后直接返回，不再搜索右子树
    }
    
    // 左子树未找到时继续搜索右子树
    return findNode(root->right, a);
}

TreeNode* PublicAncestor(TreeNode* root,TreeNode* a,TreeNode* b){
    if(root==nullptr) return nullptr;
    
    if(root==a||root==b){
        return root;
    }

    TreeNode* left=PublicAncestor(root->left,a,b);
    TreeNode* right=PublicAncestor(root->right,a,b);

    if(left&&right) return root;
    
    else if(left) return left;
    else if(right) return right;
    
    else return nullptr;
    
}




int main(){

    int n;
    cin>>n;
    int a,b;
    cin>>a>>b;
    TreeNode* root=createBinaryTree(n);

    TreeNode* p=findNode(root,a);
    TreeNode* q=findNode(root,b);
    TreeNode* ans=PublicAncestor(root,p,q);

    cout<<ans->val<<endl;
   
    // preorderTraversal(root);

    return 0;
}