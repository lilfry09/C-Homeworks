#include <vector>
#include <queue>
#include <iostream>
#include <stdexcept>
using namespace std;
template <typename verType, typename edgeType>
class Graph{
    public:
        Graph(int vSize, const verType d[]);
        void insert(int u, int v, edgeType w);
        void remove(int u, int v);
        bool exist(int u, int v) const;
        ~Graph();
        void printGraph() const;
        void DFS(int start) const;
        void DFS() const;
        void BFS(int start) const;
        void BFS() const;
    private:
        struct edgeNode{//边节点
            int end;
            edgeType weight;
            edgeNode *next;
            edgeNode(int e, edgeType w, edgeNode *n=nullptr){//构造函数
                end = e;
                weight = w;
                next = n;
            }
        };
        struct verNode{//顶点节点
            verType data;
            edgeNode *firstEdge;
            verNode(edgeNode *f=nullptr){//构造函数
                firstEdge = f;
            }
        };
        verNode *verList;
        int verNum, edgeNum;
        void DFS(int start, bool visited[]) const;
        void BFS(int start, bool visited[]) const;

        void DFS(int start) const;//非递归算法
    

};

template <typename verType, typename edgeType>
Graph<verType, edgeType>::Graph(int vSize, const verType d[]){//构造函数
    verNum = vSize;
    edgeNum = 0;
    verList = new verNode[vSize];//创建顶点数组

    for(int i=0;i<vSize;i++){//初始化顶点数组
        verList[i].data = d[i];//顶点数据
        verList[i].firstEdge = nullptr;//顶点的第一条边
    }
}

template <typename verType, typename edgeType>
void Graph<verType, edgeType>::DFS(int start, bool visited[]) const{
    edgeNode<edgeType> *p;
    cout<<verList[start].data<<" ";
    visited[start] = true;
    p=verList[start].firstEdge;
    while(p!=nullptr){
        if(!visited[p->end]) DFS(p->end, visited);
        p=p->next;
    }
}
//处理非联通图
void Graph<verType, edgeType>::DFS() const{
    bool *visited = new bool[numOfVer];
    if(!visited) throw out_of_range("visited is null");
    for(int i=0;i<numOfVer;i++){
        visited[i] = false;
    }
    for(int i=0;i<numOfVer;i++){
        if(!visited[i]) DFS(i, visited);
        cout<<endl;
        
    }
    
}



//递归bfs
template <typename verType, typename edgeType>
void Graph<verType, edgeType>::BFS(int start, bool visited[]) const{//广度优先遍历
    queue<int> q;//创建队列
    q.push(start);//入队
    visited[start] = true;//标记为已访问
    while(!q.empty()){//队列不为空
        int v = q.front();//取出队首元素
        q.pop();//出队
        cout<<verList[v].data<<" ";
        edgeNode *p = verList[v].firstEdge;//遍历邻接表
        while(p!=nullptr){//邻接表不为空
            if(!visited[p->end]){//如果没有访问过，就入队
                q.push(p->end);
                visited[p->end] = true;
            }
            p=p->next;
        }
    }
}

template <typename verType, typename edgeType>
void Graph<verType, edgeType>::BFS() const{//广度优先遍历
    bool *visited = new bool[verNum];//创建访问数组
    if(!visited) throw out_of_range("visited is null");//如果访问数组为空，抛出异常
    for(int i=0;i<verNum;i++){//初始化访问数组
        visited[i] = false;//未访问
    }
    for(int i=0;i<verNum;i++){//遍历所有顶点
        if(!visited[i]){//如果没有访问过，就进行广度优先遍历
            BFS(i, visited);
        }
    }
    cout<<endl;
}

