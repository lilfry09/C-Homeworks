#include <iostream>
#include <vector>
#include <string>
using namespace std;

// 存储每个字符在中序遍历（inord）中的位置
int charPosition[256];

// 递归地生成先序遍历字符串
// levelNodes：当前这棵子树的层序遍历结果
// inLeft, inRight：当前这棵子树中序遍历的左右区间
string getPreOrder(const vector<char>& levelNodes, int inLeft, int inRight) {
    // 如果这个区间没有节点了，返回空字符串
    if (inLeft > inRight || levelNodes.empty())
        return "";

    // 1. 找到这个区间里的“根”
    // 根的特征是：在当前levelNodes里，是第一个落在inLeft~inRight范围中的字符
    char root = 0;
    int rootIndex = -1; // 它在inord（中序）里的下标
    for (int i = 0; i < levelNodes.size(); i++) {
        char c = levelNodes[i];
        int p = charPosition[(unsigned char)c];
        if (p >= inLeft && p <= inRight) {
            root = c;
            rootIndex = p;
            break;
        }
    }

    // 2. 把levelNodes分成左子树和右子树的节点
    vector<char> leftNodes, rightNodes;
    for (int i = 0; i < levelNodes.size(); i++) {
        char c = levelNodes[i];
        if (c == root)
            continue;
        int pos = charPosition[(unsigned char)c];
        if (pos < rootIndex)
            leftNodes.push_back(c);
        else
            rightNodes.push_back(c);
    }

    // 3. 递归求左子树和右子树的先序遍历
    string leftPre = getPreOrder(leftNodes, inLeft, rootIndex - 1);
    string rightPre = getPreOrder(rightNodes, rootIndex + 1, inRight);

    // 4. 先序遍历: 根，左，右
    return string(1, root) + leftPre + rightPre;
}

int main() {
    string inord, level;
    cin >> inord >> level;

    // 记录每个字符在inord里的位置
    for (int i = 0; i < inord.size(); i++) {
        charPosition[(unsigned char)inord[i]] = i;
    }

    // 把level字符串变成字符数组
    vector<char> levelNodes(level.begin(), level.end());

    // 调用递归函数，从整棵树开始
    string preorder = getPreOrder(levelNodes, 0, inord.size()-1);

    cout << preorder << endl;
    return 0;
}

//这算法真的无敌了。。。