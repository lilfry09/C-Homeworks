#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <algorithm>

using namespace std;

class Graph {
private:
    int V;                       // 顶点数
    vector<list<int>> adj;       // 邻接表

public:
    Graph(int vertices) : V(vertices), adj(vertices) {}

    void addEdge(int v1, int v2) {          // 无向边
        adj[v1].push_back(v2);
        adj[v2].push_back(v1);
    }

    vector<int> bfsDist(int start) const {
        vector<int> dist(V, -1);
        queue<int> q;
        dist[start] = 0;
        q.push(start);

        while (!q.empty()) {
            int cur = q.front(); q.pop();
            for (int nb : adj[cur]) {
                if (dist[nb] == -1) {
                    dist[nb] = dist[cur] + 1;
                    q.push(nb);
                }
            }
        }
        return dist;
    }

    int maxCommonEdges(int O, int A, int B) {
        vector<int> dO = bfsDist(O);
        vector<int> dA = bfsDist(A);
        vector<int> dB = bfsDist(B);

        if (dO[A] == -1 || dO[B] == -1) return 0;   // A 或 B 不可达

        vector<int> cur{O};      // 当前这一层可能同时出现的顶点集合
        int ans = 0;             // 已经确定可共享的边数

        while (true) {
            vector<int> nxt;     // 下一层的候选集合
            for (int v : cur) {
                for (int u : adj[v]) {
                    if (dO[u] == dO[v] + 1 &&            // 必须沿 O 的最短路方向
                        dO[u] + dA[u] == dO[A] &&        // u 在某条 O→A 最短路上
                        dO[u] + dB[u] == dO[B]) {        // u 在某条 O→B 最短路上
                        nxt.push_back(u);
                    }
                }
            }
            if (nxt.empty()) break;      // 再向下就无法同时满足，公共部分到此为止
            ++ans;                       // 又共同走了一条边
            sort(nxt.begin(), nxt.end());              // 去重
            nxt.erase(unique(nxt.begin(), nxt.end()), nxt.end());
            cur.swap(nxt);
        }
        return ans;                      // 公共前缀的边数
    }
};

int main() {
    int n, m, O, A, B;
    cin >> n >> m >> O >> A >> B;

    Graph g(n + 1);              // 顶点编号 1..n
    for (int i = 0; i < m; ++i) {
        int u, v; cin >> u >> v;
        g.addEdge(u, v);
    }

    cout << g.maxCommonEdges(O, A, B) << endl;
    return 0;
}
