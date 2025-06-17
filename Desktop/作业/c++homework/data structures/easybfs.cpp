#include<iostream>
#include<vector>
#include<queue>
using namespace std;

void BFS(const vector<vector<int>>& adj, int numOfvertices, int startNode){
    vector<bool> visited(numOfvertices,false);
    queue<int> q;

    if(startNode<0||startNode>numOfvertices)
        return ;
    
    q.push(startNode);
    int m=q.front();
    q.pop();

    cout<<m<<endl;

    while(!q.empty()){
        int node=q.front();
        q.pop();
        cout << node << " ";

        for(int neighbor : adj[node]){
            if(!visited[neighbor]){
                visited[neighbor]=true;
                q.push(neighbor);

            }
        }


       
    }
    cout<<endl;
}

void AddEdge(vector<vector<int>>& adj,int u,int v, int numOfvertices){

    if (u < 0 || u >= numOfVertices || v < 0 || v >= numOfVertices) {
        cout << "警告: 无法添加无效边 (" << u << ", " << v << "). 顶点应在 [0, " << numOfVertices - 1 << "] 之间。" << endl;
        return;
    }

    adj[u].push_back(v);
    adj[v].push_back(u);
}

int main(){



    return 0; 
}