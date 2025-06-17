#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
//核心：把水源也看成结点，然后把所有的墙也看成结点，用kruscal算法


class unionfind {
private:
	vector<int> parent;
	vector<int> rank;	
}

int main() {
	int n;
	cin >> n;
	vector<int> a(n);
    vector<int> walls;
    vector<vector<int>> pipes(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        walls.push_back(a[i]);
    }
    sort(walls.begin(), walls.end());


}