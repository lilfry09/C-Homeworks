#include<iostream>
#include<list>
#include<vector>
using namespace std;

void Dfsutil(int v, vector<bool>& visited, const vector<list<int>>& adj){
    visited[v]=true;
    cout<< v << " ";

    for(int neighbor : adj[v]){//遍历v的邻居
        if(!visited[neighbor])
            Dfsutil(neighbor, visited, adj);
    }

}

void DFS(int v, const vector<list<int>>& adj)//从v顶点开始的dfs
{
    vector<bool> visited(adj.size(), false);
    Dfsutil(v, visited, adj);
    
}

void DFS(const vector<list<int>>& adj){
    vector<bool> visited(adj.size(), false);
    for(int i = 0; i < adj.size(); i++){
        if(!visited[i])
            Dfsutil(i, visited, adj);
    }
}

void addEdge(vector<list<int>>& adj, int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u); // 无向图
}