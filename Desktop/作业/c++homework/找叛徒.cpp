#include<iostream>
#include<vector>
using namespace std;

int main(){
    int n,m;
    cin>>n>>m;
    vector<vector<int>> trust(n+1);
    for(int i=0;i<m;i++){
        int a,b;
        cin>>a>>b;
        trust[a].push_back(b); //a信任b
    }
    int count=0;
    vector<int> ans;

    for(int i=1;i<=n;i++){
        count=0;
        for(int j=1;j<=n;j++){  // 修正：遍历1到n而不是0到m-1
            if(j==i) continue;
            bool is_trusted=false;
            for(int k=0;k<trust[j].size();k++){
                if(trust[j][k]==i){
                    is_trusted=true;
                    break;
                }
            }
            if(is_trusted) count++;
        }
        if(count==n-1){ //除了自己，其他都信任
            ans.push_back(i);
        }
    }

    for(int i=0;i<ans.size();){
        bool is_trusting=false;
        for(int j=0;j<trust[ans[i]].size();j++){
            if(trust[ans[i]][j]>0){  // 修正：检查是否信任任何人
                is_trusting=true;
                break;
            }
        }
        if(is_trusting) ans.erase(ans.begin()+i);
        else i++;
    }

    if(ans.size()==1) cout<<ans[0]<<endl;
    else cout<<-1<<endl;
    
    return 0;
}
