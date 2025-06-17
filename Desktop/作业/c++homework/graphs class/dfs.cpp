#include <vector>
#include <queue>
#include <iostream>
#include <stdexcept>
using namespace std;

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

//非递归算法

void Graph<verType, edgeType>::DFS(int start) const{
    seqStack<int> st;
    edgeNode<edgeType> *p;
    bool *visited = new bool[numOfVer];
    int start;
    if(!visited) throw out_of_range("visited is null");
    for(int i=0;i<numOfVer;i++){
        if(!visited[i]){//
        st.push(i);
        visited[i] = true;
        while(!st.isEmpty())
        {
            start = st.top();
            st.pop();
            cout<<verList[start].data<<" "; 
            p = verList[start].firstEdge;//遍历邻接表
            while(p!=nullptr){
                if(!visited[p->end]){//如果没有访问过，就入栈
                    st.push(p->end);
                    visited[p->end] = true;
                }
                p=p->next;
            }

        } 

       } 

    }
    
    for(int i=0;i<numOfVer;i++){
        if(!visited[i]){//
        st.push(i);
        visited[i] = true;
        while(!st.isEmpty())
        {
            start = st.top();
            st.pop();
            cout<<verList[start].data<<" "; 
            p = verList[start].firstEdge;  //遍历邻接表
            while(p!=nullptr){
                if(!visited[p->end]){//如果没有访问过，就入栈
                    st.push(p->end);
                    visited[p->end] = true;
                }
                p=p->next;
            }

        } 

       } 

    }
    
}