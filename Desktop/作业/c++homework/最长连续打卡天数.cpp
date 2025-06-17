#include <iostream>
#include <vector>
#include <algorithm> 

using namespace std;

int main() {
    // 加速C++的cin/cout，对于大量输入输出有帮助
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; // 同学来图书馆的总天数
    cin >> n;

    // 特殊情况：如果总天数为0，则最长连续打卡天数为0
    if (n == 0) {
        cout << 0 << endl;
        return 0;
    }

    vector<int> days(n); // 存储打卡日期的向量
    for (int i = 0; i < n; ++i) {
        cin >> days[i];
    }

    // 1. 对打卡日期进行排序
    sort(days.begin(), days.end());

    // 2. 移除重复的打卡日期
    // std::unique会将不重复的元素移到向量的前面，并返回一个指向第一个重复元素的迭代器
    // 然后vector::erase根据这个迭代器删除所有重复的元素
    days.erase(unique(days.begin(), days.end()), days.end());

    int max_streak = 1;   
    int current_streak = 1;  

    // 3. 遍历去重并排序后的日期，计算最长连续打卡天数
    // 从第二个元素开始比较（如果只有一个元素，循环不执行，max_streak保持为1，正确）
    for (size_t i = 1; i < days.size(); ++i) {
        if (days[i] == days[i - 1] + 1) {
            current_streak++;
        } else {
            current_streak = 1;
        }
        // 更新最长连续打卡天数
        // max_streak = max(max_streak, current_streak); // 也可以用下面的 if 语句
        if (current_streak > max_streak) {
            max_streak = current_streak;
        }
    }

    cout << max_streak << endl;

    return 0;
}
