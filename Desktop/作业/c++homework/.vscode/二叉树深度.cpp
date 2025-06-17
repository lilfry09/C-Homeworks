#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


// 直接计算深度的函数
int calculateDepth(const vector<pair<int, int>>& tree, int node) {
    if (node == 0) {
        return 0;  // 空节点深度为0
    }
    
    // 获取左右子树的深度
    int leftDepth = calculateDepth(tree, tree[node-1].first);//递归
    int rightDepth = calculateDepth(tree, tree[node-1].second);
    
    // 返回左右子树深度的最大值加1
    return max(leftDepth, rightDepth) + 1;
}

int main() {
    int n;
    cin >> n;
    
    // 存储每个节点的左右子节点编号
    vector<pair<int, int>> tree(n);
    for (int i = 0; i < n; i++) {
        cin >> tree[i].first >> tree[i].second;
    }
    
    // 计算树的深度（根节点编号为1）
    int depth = calculateDepth(tree, 1);
    
    cout << depth << endl;
    
    return 0;
}