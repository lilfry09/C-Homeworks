#include<iostream>
#include<vector>
#include<list>


using namespace std;

int main(){

    // 创建并初始化两个链表l1和l2
    list<int> l1 = {1, 2, 3, 4};  // l1包含元素1,2,3
    list<int> l2 = {4, 5, 6};  // l2包含元素4,5,6
    
    // 将l2的所有元素拼接到l1的开头
    // splice操作后l2将变为空链表
    l1.splice(l1.begin(), l2);  
    
    // 遍历并打印l1中的所有元素
    for(auto i: l1){
        cout << i << " ";  // 输出: 4 5 6 1 2 3
    }

    cout<<"你好";
    return 0;
}