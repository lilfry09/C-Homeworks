#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

class Graph {
private:
    int V; // 顶点数
    vector<list<int>> adj; // 邻接表
public:
    Graph(int vertices) {
        V = vertices;
        adj.resize(V);
    }

    void addEdge(int v1, int v2) {
        adj[v1].push_back(v2);
        adj[v2].push_back(v1); // 无向图
    }

    vector<int> distance; // 记录每个顶点到起点的距离
    vector<int> parent; // 记录每个顶点的父节点

    void bfs(int start) {
        distance.assign(V, -1);
        parent.assign(V, -1);
        vector<bool> visited(V, false);

        list<int> queue;
        distance[start] = 0;
        parent[start] = -1;
        visited[start] = true;
        queue.push_back(start);

        while (!queue.empty()) {
            int current = queue.front();
            queue.pop_front();
            for (int neighbor : adj[current]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    parent[neighbor] = current;
                    distance[neighbor] = distance[current] + 1;
                    queue.push_back(neighbor);
                }
            }
        }
    }

    vector<int> getShortestPath(int start, int end) {
        vector<int> path;
        if (distance[end] == -1) return path; // 不可达
        for (int v = end; v != -1; v = parent[v]) {
            path.push_back(v);
        }
        reverse(path.begin(), path.end());
        return path;
    }

    int maxCommonEdges(int o, int a, int b) {
        vector<int> pathA = getShortestPath(o, a);
        vector<int> pathB = getShortestPath(o, b);

        if (pathA.empty() || pathB.empty()) return 0; // 不可达

        int maxCommon = 0;
        int minLen = min(pathA.size(), pathB.size());
        for (int i = 1; i < minLen-1; i++) { // i=1 开始，跳过起点 O
            if (pathA[i] == pathB[i]) {// 检查下一个节点是否相同,保证边相同
                maxCommon++;
            } else {
                break;
            }
        }
        return maxCommon;
    }
};

int main() {
    int n, m, o, a, b;
    cin >> n >> m >> o >> a >> b;

    Graph g(n + 1); // 顶点从 1 开始编号
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }

    g.bfs(o);
    int maxCommon = g.maxCommonEdges(o, a, b);
    cout << maxCommon << endl;

    return 0;
}
