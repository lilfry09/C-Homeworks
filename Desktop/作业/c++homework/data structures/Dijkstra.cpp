#include <iostream>
#include <vector>       // For vector (adjacency list, distance array)
#include <queue>        // For priority_queue
#include <limits>       // For numeric_limits (used for infinity)
#include <utility>      // For pair

// 引入整个 std 命名空间
using namespace std; 

const int INF = numeric_limits<int>::max(); 

/**
 * @brief 使用 Dijkstra 算法计算从源点到图中所有其他顶点的最短路径。
 * 
 * @param num_vertices 图中顶点的数量 (0 到 num_vertices-1)
 * @param adj 邻接表，表示图的结构。
 *            adj[u] 存储一个 pair 列表 {v, weight}，表示从 u 到 v 有一条权重为 weight 的边。
 *            注意：此算法要求所有边的权重是非负数。
 * @param start_node 源顶点的索引
 * @return vector<int> 一个向量，其中 dist[i] 表示从 start_node 到顶点 i 的最短距离。
 *                            如果顶点 i 不可达，则 dist[i] 为 INF。
 */
vector<int> dijkstra(int num_vertices, 
                          const vector<vector<pair<int, int>>>& adj, 
                          int start_node) {
    
    // 1. 初始化距离数组
    // dist[i] 存储从 start_node 到顶点 i 的最短距离
    vector<int> dist(num_vertices, INF); 
    dist[start_node] = 0; // 源点到自身的距离为 0

    // 2. 优先队列
    // 存储 pair<int, int>，第一个元素是距离，第二个元素是顶点
    // priority_queue 默认是大顶堆，这里使用 greater 来实现小顶堆
    priority_queue<pair<int, int>, 
                        vector<pair<int, int>>, 
                        greater<pair<int, int>>> pq;
    
    // 将源点及距离放入优先队列
    pq.push({0, start_node}); // {distance, vertex}

    // 3. Dijkstra 算法主循环
    while (!pq.empty()) {
        // 取出当前距离最小的顶点
        int d = pq.top().first;  // 当前顶点的距离
        int u = pq.top().second; // 当前顶点
        pq.pop();

        // 如果取出的距离比已知的最短距离大，说明这个路径已经不是最优的了（旧的、重复的入队元素）
        // 或者这个顶点已经处理过了（被标记为已访问的等价逻辑），直接跳过
        if (d > dist[u]) {
            continue; 
        }

        // 遍历当前顶点 u 的所有邻居
        for (const auto& edge : adj[u]) {
            int v = edge.first;     // 邻居顶点
            int weight = edge.second; // 从 u 到 v 的边权重

            // 松弛操作：如果通过 u 到 v 的路径比当前已知的到 v 的路径短
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight; // 更新到 v 的最短距离
                pq.push({dist[v], v});      // 将更新后的 v 及其距离加入优先队列
            }
        }
    }

    // 返回最终的最短距离数组
    return dist;
}


int main() {
    int num_vertices = 5; // 0, 1, 2, 3, 4
    
    // 使用邻接表表示图
    // adj[u] 存储 {v, weight}
    vector<vector<pair<int, int>>> adj(num_vertices);

    // 添加边 (顶点u, 顶点v, 权重w)
    adj[0].push_back({1, 10});
    adj[0].push_back({2, 3});
    adj[1].push_back({2, 1});
    adj[1].push_back({3, 2});
    adj[2].push_back({1, 4});
    adj[2].push_back({3, 8});
    adj[2].push_back({4, 2});
    adj[3].push_back({4, 7});
    adj[4].push_back({3, 9});

    int start_node = 0; // 从顶点0开始

    // 调用 Dijkstra 算法
    vector<int> shortest_distances = dijkstra(num_vertices, adj, start_node);

    // 打印结果
    cout << "Shortest distances from node " << start_node << ":" << endl;
    for (int i = 0; i < num_vertices; ++i) {
        if (shortest_distances[i] == INF) {
            cout << "To node " << i << ": Not reachable" << endl;
        } else {
            cout << "To node " << i << ": " << shortest_distances[i] << endl;
        }
    }

    return 0;
}
