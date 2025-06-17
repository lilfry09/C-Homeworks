#include <iostream>

using namespace std;

class BST {
private:
    struct TreeNode {
        int data;
        TreeNode* left;
        TreeNode* right;
        int size; 

        TreeNode(int val) : data(val), left(nullptr), right(nullptr), size(1) {}
    };

    TreeNode* root;

    int getNodeSize(TreeNode* node) {
        return node ? node->size : 0;
    }

    TreeNode* insertRecursive(TreeNode* node, int data) {
        if (node == nullptr) {
            return new TreeNode(data);
        }

        if (data < node->data) {
            node->left = insertRecursive(node->left, data);
        } else if (data > node->data) {
            node->right = insertRecursive(node->right, data);
        }
        
        node->size = 1 + getNodeSize(node->left) + getNodeSize(node->right);
        return node;
    }

    int searchRecursive(TreeNode* node, int q) {
        if (node == nullptr) {
            return 0;
        }

        int count = 0;
        if (node->data < q) {
            count++;
            count += getNodeSize(node->left);
            count += searchRecursive(node->right, q);
        } else {
            count += searchRecursive(node->left, q);
        }
        return count;
    }

public:
    BST() : root(nullptr) {}

    void insert(int data) {
        root = insertRecursive(root, data);
    }

    int search(int q) {
        return searchRecursive(root, q);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    BST Tree;

    cin >> n >> m;

    int t;
    for (int i = 0; i < n; i++) {
        cin >> t;
        Tree.insert(t);
    }

    for (int i = 0; i < m; i++) {
        int q;
        cin >> q;
        cout << Tree.search(q) << "\n";
    }

    return 0;
}
