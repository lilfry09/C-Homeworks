#include <iostream>
#include <vector>
#include <list>
using namespace std;

class Graph {
private:
    int V;  // 顶点数
    vector<list<int>> adj;  // 邻接表

public:
    // 构造函数
    Graph(int vertices) {
        V = vertices;
        adj.resize(V);
    }

    // 添加边
    void addEdge(int v1, int v2) {
        adj[v1].push_back(v2);
        // 如果是无向图，需要添加下面这行
        // adj[v2].push_back(v1);
    }

    // 打印图
    void printGraph() {
        for (int i = 0; i < V; i++) {
            cout <<"顶点"<< i <<"的邻接表:";
            for (auto x : adj[i]) {
                cout << "->" << x;
            }
            cout << endl;
        }
    }
};

int main() {
    // 创建一个有4个顶点的图
    Graph g(4);

    // 添加边
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 3);

    // 打印图
    g.printGraph();

    return 0;
}