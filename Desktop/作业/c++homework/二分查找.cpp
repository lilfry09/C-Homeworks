#include <iostream>
#include <vector>
#include <algorithm> // 引入算法库以使用sort函数
using namespace std;
int main() {
    int n,m;
    cin>>n>>m;
    vector<int> a(n+1),b(m+1);
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    for(int i=0;i<m;i++){
        cin>>b[i]; 
    }

    sort(a.begin(), a.end()); // 先排序，才能二分查找

    for (int i = 0; i < m; i++) {
        auto it = lower_bound(a.begin(), a.end(), b[i]);
        if (it != a.end()) {
            cout << *it << endl;
        } else {
            cout << -1 << endl;
        }
    }
    
    return 0;
}
 