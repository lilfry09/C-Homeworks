#include <iostream>
#include <vector>
using namespace std;

long long mergeAndCount(vector<int>& a, int left, int mid, int right) {
    vector<int> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0;
    long long invCount = 0;

    while (i <= mid && j <= right) {
        if (a[i] <= a[j]) {
            temp[k++] = a[i++];
        } else {
            // 当前a[i] > a[j]，说明a[i...mid]都 > a[j]
            invCount += (mid - i + 1);
            temp[k++] = a[j++];
        }
    }

    while (i <= mid) {// 处理剩余的左半部分
        temp[k++] = a[i++];
    }

    while (j <= right) {// 处理剩余的右半部分
        temp[k++] = a[j++];
    }

    for (int idx = 0; idx < k; idx++) {// 将临时数组中的元素复制回原数组
        a[left + idx] = temp[idx];
    }

    return invCount;
}

long long countInversions(vector<int>& a, int left, int right) {
    long long invCount = 0;
    if (left < right) {
        int mid = left + (right - left) / 2;
        invCount += countInversions(a, left, mid);
        invCount += countInversions(a, mid + 1, right);
        invCount += mergeAndCount(a, left, mid, right);
    }
    return invCount;
}

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    long long count = countInversions(a, 0, n - 1);
    cout << count << endl;

    return 0;
}
