#include <bits/stdc++.h>
using namespace std;

/* ------------ 快速读入 ------------ */
namespace FastIO {
    const int SZ = 1 << 20;
    char buf[SZ], *p1 = buf, *p2 = buf;
    inline char gc() {
        if (p1 == p2) {
            p2 = (p1 = buf) + fread(buf, 1, SZ, stdin);
            if (p1 == p2) return 0;
        }
        return *p1++;
    }
    inline int readInt() {
        int x = 0, f = 1;  char c = gc();
        while (c < '0' || c > '9') { if (c == '-') f = -1; c = gc(); }
        while (c >= '0' && c <= '9') { x = x * 10 + (c ^ 48); c = gc(); }
        return x * f;
    }
}

/* ------------ 前向星 ------------ */
struct Edge { int to, nxt; };
int  n, m;
vector<Edge> pool;
vector<int> head;        // size n+1
void addEdge(int u, int v) {
    pool.push_back({v, head[u]});
    head[u] = (int)pool.size() - 1;
}

/* ------------ 主程序 ------------ */
int main() {
    using FastIO::readInt;
    n = readInt();  m = readInt();

    pool.reserve(2 * (size_t)m + 5);
    head.assign(n + 1, -1);
    vector<pair<int,int>> E;   E.reserve(m);

    for (int i = 0; i < m; ++i) {
        int a = readInt(), b = readInt();
        E.emplace_back(a, b);
        addEdge(a, b);
        addEdge(b, a);
    }

    /* ---------- 1. BFS 求层数 ---------- */
    const int INF = 0x3f3f3f3f;
    vector<int> dist(n + 1, INF);
    vector<int> que(n);          // 手写队列
    int qh = 0, qt = 0;
    dist[1] = 0;
    que[qt++] = 1;
    while (qh < qt) {
        int u = que[qh++];
        for (int i = head[u]; i != -1; i = pool[i].nxt) {
            int v = pool[i].to;
            if (dist[v] == INF) {
                dist[v] = dist[u] + 1;
                que[qt++] = v;
            }
        }
    }

    /* ---------- 2. 统计 preCnt / sameCnt ---------- */
    vector<int> preCnt(n + 1, 0);
    vector<int> sameCnt(n + 1, 0);
    for (auto &[u, v] : E) {
        if (dist[u] == INF || dist[v] == INF) continue;   // 跟 1 号不连通
        if (dist[u] == dist[v]) {
            ++sameCnt[u];  ++sameCnt[v];
        } else if (dist[u] + 1 == dist[v]) {
            ++preCnt[v];
        } else if (dist[v] + 1 == dist[u]) {
            ++preCnt[u];
        }
        /* 其余情况（差>1）在可达子图里不会出现 */
    }

    /* ---------- 3. 判断每条边 ---------- */
    long long ans = 0;
    for (auto &[u, v] : E) {
        if (dist[u] == INF || dist[v] == INF) {   // 至少一端本就不可达
            ++ans;  continue;
        }
        if (dist[u] == dist[v]) {                 // 同层边
            ++ans;  continue;
        }
        if (dist[u] + 1 == dist[v]) {             // v 更深
            if (preCnt[v] >= 2 || sameCnt[v] >= 1) ++ans;
        } else if (dist[v] + 1 == dist[u]) {      // u 更深
            if (preCnt[u] >= 2 || sameCnt[u] >= 1) ++ans;
        } else {
            /* 差距>1，在可达部分不会出现 */
            ++ans;   // 保险起见也可算进
        }
    }

    /* ---------- 输出 ---------- */
    printf("%lld\n", ans);
    return 0;
}
