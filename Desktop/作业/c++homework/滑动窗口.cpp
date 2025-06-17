#include<iostream>
#include<vector>
#include<deque>
using namespace std;
class MyQueue { //单调队列（从大到小）
    public:
        deque<int> que; // 使用deque来实现单调队列
        // 每次弹出的时候，比较当前要弹出的数值是否等于队列出口元素的数值，如果相等则弹出。
        // 同时pop之前判断队列当前是否为空。
        void pop(int value) {
            if (!que.empty() && value == que.front()) {
                que.pop_front();
            }
        }
        // 如果push的数值大于入口元素的数值，那么就将队列后端的数值弹出，直到push的数值小于等于队列入口元素的数值为止。
        // 这样就保持了队列里的数值是单调从大到小的了。
        void push(int value) {
            while (!que.empty() && value > que.back()) {
                que.pop_back();
            }
            que.push_back(value);
    
        }
        // 查询当前队列里的最大值 直接返回队列前端也就是front就可以了。
        int front() {
            return que.front();
        }
    };

class MyQueue2 { //单调队列（从小到大）
    public:
        deque<int> que; // 使用deque来实现单调队列
        // 每次弹出的时候，比较当前要弹出的数值是否等于队列出口元素的数值，如果相等则弹出。
        // 同时pop之前判断队列当前是否为空。
       void pop(int value) {
            if (!que.empty() && value == que.front()) {
                que.pop_front();
            }
        }
        // 如果push的数值小于入口元素的数值，那么就将队列后端的数值弹出，直到push的数值大于等于队列入口元素的数值为止。
        // 这样就保持了队列里的数值是单调从小到大的了。
        void push(int value){
            while(!que.empty()&&value<que.back()){  
                que.pop_back();
                
            }
            que.push_back(value);
        }
        // 查询当前队列里的最小值 直接返回队列前端也就是front就可以了。
        int front() {
           return que.front(); 
        }
    };

    

    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        MyQueue que;
        vector<int> result1;
        
        for (int i = 0; i < k; i++) { // 先将前k的元素放进队列
            que.push(nums[i]);
        }
        result1.push_back(que.front()); // result 记录前k的元素的最大值
        for (int i = k; i < nums.size(); i++) {
            que.pop(nums[i - k]); // 滑动窗口移除最前面元素
            que.push(nums[i]); // 滑动窗口前加入最后面的元素
            result1.push_back(que.front()); // 记录对应的最大值

        }
        return result1;
    }

    vector<int> minSlidingWindow(vector<int>& nums, int k) {
        MyQueue2 que;
        vector<int> result2;
        for (int i = 0; i < k; i++) { // 先将前k的元素放进队列
            que.push(nums[i]);
        } 
        result2.push_back(que.front()); // result 记录前k的元素的最小值
        for (int i = k; i < nums.size(); i++) {
            que.pop(nums[i - k]); // 滑动窗口移除最前面元素
            que.push(nums[i]); // 滑动窗口前加入最后面的元素
            result2.push_back(que.front()); // 记录对应的最小值 
        }
        return result2;

    }
   
int main(){
    int N,k;
    cin>>N>>k;
    vector<int> nums(N);
    for(int i=0;i<N;i++){
        cin>>nums[i];
    }
    vector<int> result1=maxSlidingWindow(nums,k);
    vector<int> result2=minSlidingWindow(nums,k);

   
    for(int i=0;i<result2.size();i++){
        cout<<result2[i]<<" "; 
    }
    cout<<endl;

    for(int i=0;i<result1.size();i++){
        cout<<result1[i]<<" ";
    }
    
    return 0;
}