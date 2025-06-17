#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <memory> // Required for std::unique_ptr
using namespace std;

// Using a specific size for alphabet
const int ALPHABET_SIZE = 52; // 26 lowercase + 26 uppercase

// Helper function to map char to an index (0-51)
// 'a'-'z' -> 0-25
// 'A'-'Z' -> 26-51
inline int char_to_index(char c) {
    if (c >= 'a' && c <= 'z') {
        return c - 'a';
    } else {
        return c - 'A' + 26;
    }
}

struct TrieNode {
    // Use unique_ptr for automatic memory management
    array<unique_ptr<TrieNode>, ALPHABET_SIZE> children;
    int prefix_count; // Number of words that have the path to this node as a prefix

    TrieNode() : prefix_count(0) {}
};

class Trie {
public:
    unique_ptr<TrieNode> root; // Root is also managed by unique_ptr

    Trie() {
        root = make_unique<TrieNode>(); // 创建新的子节点
    }

    void insert(const string& word) {
        TrieNode* current_node = root.get(); // Get raw pointer for traversal

        for (char ch : word) {
            int index = char_to_index(ch);
            
            if (current_node->children[index] == nullptr) {
                // If child does not exist, create it
                current_node->children[index] = make_unique<TrieNode>();
            }
            current_node = current_node->children[index].get();
            current_node->prefix_count++; // Increment count for the current prefix
        }

    }

    int query(const string& prefix_word) const { 
        TrieNode* current_node = root.get(); 

        for (char ch : prefix_word) {
            int index = char_to_index(ch);

            if (current_node->children[index] == nullptr) {
                return 0; // The prefix_word is not a prefix of any inserted word
            }
            // Move to the child node
            current_node = current_node->children[index].get();
        }
        return current_node->prefix_count;
    }
};

void solve_test_case() {
    int n, q;
    cin >> n >> q;

    Trie trie; 

    for (int i = 0; i < n; ++i) {
        string pattern_str;
        cin >> pattern_str;
        trie.insert(pattern_str);
    }

    for (int i = 0; i < q; ++i) {
        string query_str;
        cin >> query_str;
        cout << trie.query(query_str) << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    while (T--) {
        solve_test_case();
    }

    return 0;
}

