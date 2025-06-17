#include<iostream>
#include<vector>

using namespace std;

int main(){


    vector<vector<int>> adj;
    int E,V;

    for (int i = 0; i < E; ++i) {
        int u, v; // 边的两个顶点
        cin >> u >> v;

    
        if (u >= 0 && u < V && v >= 0 && v < V) {
            adj[u].push_back(v); // 将 v 添加到 u 的邻居列表
            adj[v].push_back(u); // 将 u 添加到 v 的邻居列表 (无向图特有)
        } else {
            std::cout << "警告: 无效的顶点编号 (" << u << ", " << v << "). 请确保顶点在 0 到 " << V-1 << " 之间。" << std::endl;
        }

        // 如果是 **有向图 (directed graph)**，则只需要：
        // adj[u].push_back(v); // 表示从 u 到 v 有一条边
    }
}