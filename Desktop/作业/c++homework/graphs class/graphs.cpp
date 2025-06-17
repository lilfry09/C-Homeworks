#include <vector>
#include <queue>
#include <iostream>
#include <stdexcept>
using namespace std;

template <typename verType, typename edgeType>
class Graph {
public:
    Graph(int vSize, const verType d[]);
    void insert(int u, int v, edgeType w);
    void remove(int u, int v);
    bool exist(int u, int v) const;
    ~Graph();
    void printGraph() const;
    void DFS(int start) const;      // 非递归DFS
    void DFS() const;               // 递归DFS，处理非连通图
    void BFS(int start) const;
    void BFS() const;
private:
    struct edgeNode { // 边节点
        int end;
        edgeType weight;
        edgeNode *next;
        edgeNode(int e, edgeType w, edgeNode *n = nullptr) {
            end = e;
            weight = w;
            next = n;
        }
    };
    struct verNode { // 顶点节点
        verType data;
        edgeNode *firstEdge;
        verNode(edgeNode *f = nullptr) {
            firstEdge = f;
        }
    };
    verNode *verList;
    int verNum, edgeNum;//顶点数和边数

    void DFS(int start, bool visited[]) const; // 递归DFS
    void BFS(int start, bool visited[]) const; // BFS辅助
};

// 构造函数
template <typename verType, typename edgeType>
Graph<verType, edgeType>::Graph(int vSize, const verType d[]) {
    verNum = vSize;
    edgeNum = 0;
    verList = new verNode[vSize];
    for (int i = 0; i < vSize; i++) {
        verList[i].data = d[i];
        verList[i].firstEdge = nullptr;
    }
}

// 插入边
template <typename verType, typename edgeType>
void Graph<verType, edgeType>::insert(int u, int v, edgeType w) {
    if (u < 0 || u >= verNum || v < 0 || v >= verNum)
        throw out_of_range("vertex index out of range");
    edgeNode *p = verList[u].firstEdge;
    while (p) {
        if (p->end == v) return; // 已存在
        p = p->next;
    }
    verList[u].firstEdge = new edgeNode(v, w, verList[u].firstEdge);
    ++edgeNum;
}

// 删除边
template <typename verType, typename edgeType>
void Graph<verType, edgeType>::remove(int u, int v) {
    if (u < 0 || u >= verNum || v < 0 || v >= verNum)
        throw out_of_range("vertex index out of range");
    edgeNode *p = verList[u].firstEdge, *q = nullptr;
    while (p && p->end != v) {
        q = p;
        p = p->next;
    }
    if (!p) return; // 没有这条边
    if (!q) verList[u].firstEdge = p->next;
    else q->next = p->next;
    delete p;
    --edgeNum;
}

// 判断边是否存在
template <typename verType, typename edgeType>
bool Graph<verType, edgeType>::exist(int u, int v) const {
    if (u < 0 || u >= verNum || v < 0 || v >= verNum)
        throw out_of_range("vertex index out of range");
    edgeNode *p = verList[u].firstEdge;
    while (p) {
        if (p->end == v) return true;
        p = p->next;
    }
    return false;
}

// 析构函数
template <typename verType, typename edgeType>
Graph<verType, edgeType>::~Graph() {
    for (int i = 0; i < verNum; ++i) {
        edgeNode *p = verList[i].firstEdge;
        while (p) {
            edgeNode *tmp = p;
            p = p->next;
            delete tmp;
        }
    }
    delete[] verList;
}

// 打印邻接表
template <typename verType, typename edgeType>
void Graph<verType, edgeType>::printGraph() const {
    for (int i = 0; i < verNum; ++i) {
        cout << verList[i].data << ":";
        edgeNode *p = verList[i].firstEdge;
        while (p) {
            cout << " -> (" << verList[p->end].data << ", " << p->weight << ")";
            p = p->next;
        }
        cout << endl;
    }
}

// 递归DFS
template <typename verType, typename edgeType>
void Graph<verType, edgeType>::DFS(int start, bool visited[]) const {
    edgeNode *p;
    cout << verList[start].data << " ";
    visited[start] = true;
    p = verList[start].firstEdge;
    while (p != nullptr) {
        if (!visited[p->end]) DFS(p->end, visited);
        p = p->next;
    }
}

// 递归DFS入口，处理非连通图
template <typename verType, typename edgeType>
void Graph<verType, edgeType>::DFS() const {
    bool *visited = new bool[verNum];
    if (!visited) throw out_of_range("visited is null");
    for (int i = 0; i < verNum; i++) visited[i] = false;
    for (int i = 0; i < verNum; i++) {
        if (!visited[i]) {
            DFS(i, visited);
            cout << endl;
        }
    }
    delete[] visited;
}

// 非递归DFS
template <typename verType, typename edgeType>
void Graph<verType, edgeType>::DFS(int start) const {
    bool *visited = new bool[verNum];
    for (int i = 0; i < verNum; ++i) visited[i] = false;
    vector<int> stack;
    stack.push_back(start);
    while (!stack.empty()) {
        int v = stack.back();
        stack.pop_back();
        if (!visited[v]) {
            cout << verList[v].data << " ";
            visited[v] = true;
            edgeNode *p = verList[v].firstEdge;
            vector<int> temp;
            while (p) {
                if (!visited[p->end]) temp.push_back(p->end);
                p = p->next;
            }
            for (auto it = temp.rbegin(); it != temp.rend(); ++it)
                stack.push_back(*it);
        }
    }
    cout << endl;
    delete[] visited;
}

// BFS辅助
template <typename verType, typename edgeType>
void Graph<verType, edgeType>::BFS(int start, bool visited[]) const {
    queue<int> q;
    q.push(start);
    visited[start] = true;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        cout << verList[v].data << " ";
        edgeNode *p = verList[v].firstEdge;
        while (p != nullptr) {
            if (!visited[p->end]) {
                q.push(p->end);
                visited[p->end] = true;
            }
            p = p->next;
        }
    }
}

// BFS入口，处理非连通图
template <typename verType, typename edgeType>
void Graph<verType, edgeType>::BFS() const {
    bool *visited = new bool[verNum];
    if (!visited) throw out_of_range("visited is null");
    for (int i = 0; i < verNum; i++) visited[i] = false;
    for (int i = 0; i < verNum; i++) {
        if (!visited[i]) {
            BFS(i, visited);
        }
    }
    cout << endl;
    delete[] visited;
}

// 单点BFS
template <typename verType, typename edgeType>
void Graph<verType, edgeType>::BFS(int start) const {
    bool *visited = new bool[verNum];
    for (int i = 0; i < verNum; ++i) visited[i] = false;
    BFS(start, visited);
    cout << endl;
    delete[] visited;
}

// ================== 测试代码示例 ==================
/*
int main() {
    char v[] = {'A', 'B', 'C', 'D', 'E'};
    Graph<char, int> g(5, v);
    g.insert(0, 1, 1);
    g.insert(0, 2, 1);
    g.insert(1, 2, 1);
    g.insert(1, 3, 1);
    g.insert(2, 4, 1);
    g.printGraph();
    cout << "DFS递归:" << endl;
    g.DFS();
    cout << "DFS非递归从A:" << endl;
    g.DFS(0);
    cout << "BFS:" << endl;
    g.BFS();
    return 0;
}
*/


