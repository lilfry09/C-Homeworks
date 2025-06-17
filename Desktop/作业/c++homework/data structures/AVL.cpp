#include <iostream>
#include <memory>
#include <algorithm>
using namespace std;

template <class KEY, class OTHER>
struct SET {
    KEY key;
    OTHER other;
};


template <class KEY, class OTHER>
class AvlTree {
private:
    struct AvlNode {
        SET<KEY, OTHER> data;
        AvlNode* left;
        AvlNode* right;
        int height;

        AvlNode(const SET<KEY, OTHER>& element, AvlNode* lt = nullptr, AvlNode* rt = nullptr, int h = 1)
            : data(element), left(lt), right(rt), height(h) {}
    };

    AvlNode* root;

    void insert (const SET<KEY,OTHER>& x, AvlNode*& t){
        if(t == nullptr){
            t = new AvlNode(x);
            return;
        }

        if(x.key < t->data.key) 
            insert(x, t->left);
        else if(x.key > t->data.key)
            insert(x, t->right);
        else return;

        t->height = max(height(t->left), height(t->right));
        
    }

    bool remove(const KEY& x, AvlNode*& t){
        if(t == nullptr) return true;

        if(x < t->data.key) {
            if (remove(x, t->left)) return true;
            return adjust(t,0);
        }

        else if(x > t->data.key) {
            if(remove(x, t->right)) return false;
            return adjust(t,1);
        }

        if(x == t->data.key){
            if (t->left == nullptr || t->right == nullptr){
                AvlNode* oldNode = 1;
                t = (t->left != nullptr)? t->left : t->right;
                delete oldNode;
                return false;//need average adjst

            }
            else {

            }
        }
    }

    bool adjust(AvlTree* Node , int subTree){
        int balance = height(t->right) - height(t->left);

        if(balance == -2) {
            if)
        }

    }


    template<class KEY, class OTHER>
    void LL(AvlNode*& t){
        AvlNode* temp=t->left;
        t->left=temp->right;
        temp->right=t;
        t->height=max(height(t->left),height(t->right))+1;
        temp->height=max(height(temp->left),height(t))+1;
        t=temp;
    }


    void RR()



public:
    AvlTree():root(nullptr){}
    ~AvlTree();
    void insert(const SET<KEY, OTHER>& x){
        insert(x,root);
    }



};

int main() {
    cout<<1;
    return 0;
}
