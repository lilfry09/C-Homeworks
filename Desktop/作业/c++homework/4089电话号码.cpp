#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <memory> // For unique_ptr

using namespace std;

struct TrieNode {
    array<unique_ptr<TrieNode>, 10> children; // 0-9，所以是10个
    bool is_end_of_word; // 标记是否是一个完整电话号码的结尾
    bool has_children;   // 标记当前节点是否有子节点

    TrieNode() : is_end_of_word(false), has_children(false) {}
};

class Trie {
public:
    unique_ptr<TrieNode> root;

    Trie() {
        root = make_unique<TrieNode>(); 
    }
    bool insert(const string &x) { 
        TrieNode* current_node = root.get();

        for (char ch : x) {
            int index = ch - '0';
            
            // 路径上的任何一个前缀是否已经是一个完整号码
            if (current_node->is_end_of_word) {
                return false; // 当前号码是之前某个号码的扩展，所以不一致
            }

            // 标记当前节点有子节点（因为我们要沿着它继续创建或遍历）
            current_node->has_children = true; 

            if (current_node->children[index] == nullptr) {
                current_node->children[index] = make_unique<TrieNode>();
            }
            current_node = current_node->children[index].get();
        }

        // 遍历完整个号码x后，到达x的末尾节点
        // 如果x本身是某个已存在号码的前缀 (即x的末尾节点已经有子节点)
            if (current_node->has_children) {
                return false; // x 是其他号码的前缀，所以不一致
            }
            
            current_node->is_end_of_word = true; 
        
            return true; 
    }

    
};

int main() {
    ios_base::sync_with_stdio(false); // 加速I/O
    cin.tie(NULL); // 解除cin与cout的绑定

    int t;
    cin >> t; // 读取测试用例的数目

    while (t--) { // 循环 t 次
        Trie tree; // 每个测试用例创建一个新的 Trie
        int n;
        cin >> n; // 读取电话号码的数量

        bool is_consistent = true; // 假设当前测试用例是一致的

        for (int j = 0; j < n; ++j) {
            string a;
            cin >> a;
            if (is_consistent) { // 只有当前仍然是一致的情况下才尝试插入
                if (!tree.insert(a)) { // 如果插入过程中发现不一致
                    is_consistent = false; // 标记为不一致
                }
            }
        }

        if (is_consistent) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }

    return 0;
}
