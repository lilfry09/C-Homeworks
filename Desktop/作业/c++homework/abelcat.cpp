#include <iostream> 
#include <vector> 
#include <utility> 

using ll = long long;


namespace FastIO {
    const int SZ = 1 << 20; // Buffer size for reading input (1MB)
    char buf[SZ], *p1 = buf, *p2 = buf; // Buffer and pointers to current read position

    // Gets the next character from input, refilling buffer if it's empty
    inline char gc() {
        if (p1 == p2) { // If buffer is empty
            p2 = (p1 = buf) + fread(buf, 1, SZ, stdin); // Read more data from stdin
            if (p1 == p2) return 0; // End of file or read error
        }
        return *p1++; // Return current character and advance pointer
    }

    // Reads an integer from input using FastIO
    inline int readInt() {
        int x = 0; bool is_negative = false; char c = gc(); // x: result, is_negative: sign flag, c: current char
        // Skip non-digit characters, check for negative sign
        while (c < '0' || c > '9') { if (c == '-') is_negative = true; c = gc(); }
        // Accumulate digits to form the integer
        while (c >= '0' && c <= '9') { x = x * 10 + (c - '0'); c = gc(); } // (c - '0') is equivalent to (c ^ 48) for ASCII digits
        return is_negative ? -x : x; // Apply sign if necessary
    }
} // namespace FastIO

/* ------------ 前向星 (Adjacency List using Array Simulation) ------------ */
// Structure to represent an edge in the adjacency list
struct EdgeNode { 
    int to;   // Destination vertex of the edge
    int nxt;  // Index in 'edgePool' of the next edge originating from the same source vertex
};

std::vector<EdgeNode> edgePool; // Stores all edges (acts like a memory pool for edge objects)
std::vector<int> head;        // head[u] stores the index in 'edgePool' of the first edge from node u
                              // A value of -1 indicates no outgoing edges from u recorded yet.

// Helper function to add an undirected edge (u, v) to the graph.
// This involves adding two directed edges: u -> v and v -> u.
void addGraphEdge(int u, int v) {
    // Add edge u -> v
    edgePool.push_back({v, head[u]}); // Create new edge, its 'nxt' points to old head[u]
    head[u] = (int)edgePool.size() - 1; // Update head[u] to this new edge
    
    // Add edge v -> u
    edgePool.push_back({u, head[v]}); // Create new edge, its 'nxt' points to old head[v]
    head[v] = (int)edgePool.size() - 1; // Update head[v] to this new edge
}

/* ------------ 主程序 (Main Program) ------------ */
int main() {
    using FastIO::readInt;

    int n_nodes = readInt(); // Number of nodes in the graph
    int m_edges = readInt(); // Number of edges in the graph

    // Pre-allocate memory for graph structures. This can offer a minor performance
    // improvement by avoiding reallocations as elements are added.
    // For edgePool, each original undirected edge (u,v) results in two entries 
    // (u->v and v->u) in our adjacency list. So, reserve space for 2*m_edges.
    // Adding a small constant like +5 is a common competitive programming practice.
    edgePool.reserve(2 * (size_t)m_edges + 5); 
    
    // Initialize the head array. head[i] = -1 signifies that node i currently has no outgoing edges.
    // Nodes are typically 1-indexed in competitive programming problems, so size is n_nodes + 1.
    head.assign(n_nodes + 1, -1); 
    
    // Store the original list of edges. This is useful because we often need to iterate 
    // through the edges multiple times with their original (u,v) pairing.
    std::vector<std::pair<int, int>> originalEdgesList;
    originalEdgesList.reserve(m_edges);

    // Read all edges and build the graph
    for (int i = 0; i < m_edges; ++i) {
        int u = readInt(), v = readInt();
        originalEdgesList.emplace_back(u, v); // Store the original pair
        addGraphEdge(u, v);                   // Add the edge to our adjacency list representation
    }

    /*
     * Part 1: BFS to determine shortest path distances (layers/levels) from node 1
     * -----------------------------------------------------------------------------
     * Purpose: Calculate the minimum number of edges (shortest distance) from a source node
     * (conventionally node 1 in many problems) to all other nodes in the graph. 
     * This BFS effectively partitions the graph nodes into layers based on their distance 
     * from the source. This layering information is fundamental for classifying edges later.
     */
    const int INF_DISTANCE = 0x3f3f3f3f; // A large integer value used to represent infinity (unreachable)
    std::vector<int> dist(n_nodes + 1, INF_DISTANCE); // dist[i] will store the shortest distance from node 1 to node i
    
    // Manual queue implementation for BFS. std::vector is used as the underlying container.
    // This can sometimes be slightly faster than std::queue in competitive programming.
    std::vector<int> bfs_queue(n_nodes + 1); // Max size n_nodes is sufficient if the graph is connected from node 1.
    int q_head = 0, q_tail = 0; // Pointers for the head and tail of the manual queue

    dist[1] = 0; // The distance from the source (node 1) to itself is 0
    bfs_queue[q_tail++] = 1; // Add node 1 to the queue to start the BFS process

    while (q_head < q_tail) { // Continue BFS as long as the queue is not empty
        int u = bfs_queue[q_head++]; // Dequeue a node 'u'
        
        // Iterate through all neighbors 'v' of node 'u'
        for (int edge_idx = head[u]; edge_idx != -1; edge_idx = edgePool[edge_idx].nxt) {
            int v = edgePool[edge_idx].to;
            if (dist[v] == INF_DISTANCE) { // If node 'v' hasn't been visited yet (its distance is still INF)
                dist[v] = dist[u] + 1;    // The shortest distance to 'v' is dist[u] + 1
                bfs_queue[q_tail++] = v;  // Enqueue 'v' for further exploration
            }
        }
    }

    /*
     * Part 2: Calculate `preCnt` and `sameCnt` for each node based on BFS levels
     * ---------------------------------------------------------------------------
     * These counts help characterize the local connectivity of each node with respect to the BFS levels.
     * - preCnt[i]: For a node 'i', this counts how many of its neighbors are in the BFS level
     *              *immediately above* 'i' (i.e., dist[neighbor] == dist[i] - 1).
     *              These neighbors are potential "parents" of 'i' in a shortest path tree from node 1.
     * - sameCnt[i]: For a node 'i', this counts how many of its neighbors are at the *same* BFS level
     *               as 'i' (i.e., dist[neighbor] == dist[i]). These edges are often called "cross-edges".
     */
    std::vector<int> preCnt(n_nodes + 1, 0);  // Stores count of "parent-level" neighbors for each node
    std::vector<int> sameCnt(n_nodes + 1, 0); // Stores count of "same-level" neighbors for each node

    // Iterate through the original list of edges (u,v)
    for (const auto& edge_pair : originalEdgesList) { // Using structured binding for convenience
        int u = edge_pair.first;
        int v = edge_pair.second;

        // Skip processing for this edge if either of its endpoints is unreachable from node 1
        // (as their dist would be INF_DISTANCE).
        if (dist[u] == INF_DISTANCE || dist[v] == INF_DISTANCE) {
            continue;
        }

        if (dist[u] == dist[v]) {
            // The edge (u,v) connects two nodes at the same BFS level.
            // Increment sameCnt for both u and v.
            ++sameCnt[u];
            ++sameCnt[v];
        } else if (dist[u] + 1 == dist[v]) {
            // Node u is in the level immediately above node v (u is a potential parent of v).
            // Increment preCnt for the child node v.
            ++preCnt[v];
        } else if (dist[v] + 1 == dist[u]) {
            // Node v is in the level immediately above node u (v is a potential parent of u).
            // Increment preCnt for the child node u.
            ++preCnt[u];
        }
        // Note: For any edge (x,y) in an unweighted graph, if both x and y are reachable
        // from a source node, the BFS algorithm ensures that their shortest distances
        // (dist[x] and dist[y]) can differ by at most 1. That is, |dist[x] - dist[y]| <= 1.
        // So, one of the three conditions above (dist[u]==dist[v], dist[u]+1==dist[v], or dist[v]+1==dist[u])
        // must be true if both u and v are reachable from node 1.
    }

    /*
     * Part 3: Classify each original edge and sum up "non-critical" ones
     * --------------------------------------------------------------------
     * The variable `ans` will accumulate the count of edges that are considered "non-critical"
     * according to the specific logic defined by this problem. An edge is generally considered
     * non-critical if its removal is assumed not to affect the shortest path distances from node 1
     * to other nodes (or satisfy other problem-specific criteria for non-criticality).
     */
    ll ans = 0; // Use long long for the answer, as the number of edges (m_edges) can be large.

    for (const auto& edge_pair : originalEdgesList) { // Iterate through original edges again
        int u = edge_pair.first;
        int v = edge_pair.second;

        // Rule 1: Edge involves at least one node unreachable from node 1.
        // If an edge connects to a node that's already unreachable, or connects two unreachable nodes,
        // its removal doesn't change the shortest path distances for nodes within the component
        // reachable from node 1. Thus, it's counted as non-critical in this context.
        if (dist[u] == INF_DISTANCE || dist[v] == INF_DISTANCE) {
            ++ans;
            continue; // Proceed to the next edge
        }

        // Rule 2: Edge connects two nodes at the same BFS level (a "cross-edge").
        // (At this point, both u and v are reachable from node 1, as Rule 1 didn't apply).
        // Edges connecting nodes at the same shortest distance from the source are never part
        // of any shortest path from that source (shortest paths always go from a layer 'd' to 'd+1').
        // Therefore, removing them doesn't alter any shortest path lengths from node 1.
        if (dist[u] == dist[v]) {
            ++ans;
            continue; // Proceed to the next edge
        }
        
        // Rule 3: Edge connects nodes in adjacent BFS levels.
        // (At this point: u and v are reachable, and dist[u] != dist[v]).
        // From BFS properties on unweighted graphs, it must be that |dist[u] - dist[v]| == 1.
        // One node is effectively a "parent" (in a shallower BFS layer) and the other is a "child"
        // (in the next deeper BFS layer).
        if (dist[u] + 1 == dist[v]) { // Here, v is the deeper node (child), u is shallower (parent)
            // This edge (u,v) is considered non-critical if EITHER:
            // 1. The child node 'v' has at least two "parent-level" neighbors (preCnt[v] >= 2).
            //    This means 'v' has an alternative path of the same shortest length from another parent.
            // OR
            // 2. The child node 'v' has at least one neighbor at its own level (sameCnt[v] >= 1).
            //    The specific logic of this problem deems the edge (u,v) non-critical even if 'u'
            //    is the sole parent of 'v', provided 'v' has same-level connections.
            //    (Interpretation: This might imply that same-level connectivity offers some form
            //    of redundancy relevant to the problem, even if it doesn't preserve the absolute
            //    shortest path to 'v' if 'u' is its only parent and (u,v) is removed. This condition
            //    is key to this specific problem's definition of "non-critical".)
            if (preCnt[v] >= 2 || sameCnt[v] >= 1) {
                ++ans;
            }
        } else if (dist[v] + 1 == dist[u]) { // Symmetrical case: u is deeper (child), v is shallower (parent)
            if (preCnt[u] >= 2 || sameCnt[u] >= 1) {
                ++ans;
            }
        } else {
            // This 'else' branch covers cases where dist[u] and dist[v] are both finite,
            // not equal, and their difference is not 1.
            // For an unweighted graph and BFS distances, this situation (|dist[u]-dist[v]| > 1)
            // should not occur for any edge (u,v) if both u and v are reachable.
            // This branch is kept for complete faithfulness to the original code's structure.
            // It might act as a safeguard or handle an extremely unusual graph property or
            // interpretation, deeming such edges non-critical.
            ++ans;
        }
    }

    // Output the final accumulated count of "non-critical" edges.
    // Using printf can sometimes be faster for output in competitive programming.
    printf("%lld\n", ans);

    return 0;
}




