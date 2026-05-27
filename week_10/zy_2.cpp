#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct Load
{
    int begin;
    int end;
};

bool cmp(Load a, Load b)
{
    return a.begin < b.begin;
}

int main()
{
    int n;
    cin >> n;
    vector<Load> H(n), W(n);
    for (int i = 0; i < n; i++)
        cin >> H[i].begin >> H[i].end;
    for (int i = 0; i < n; i++)
        cin >> W[i].begin >> W[i].end;

    // 按开始时间排序，为双指针扫描做准备
    sort(H.begin(), H.end(), cmp);
    sort(W.begin(), W.end(), cmp);

    long long total_time = 0;
    int i = 0, j = 0;
    while (i < n && j < n)
    {
        // 计算当前两个区间的重叠部分
        int start = max(H[i].begin, W[j].begin);
        int end = min(H[i].end, W[j].end);
        if (start < end)
            total_time += end - start;

        // 谁先结束就移动谁的指针，保证不漏掉可能的重叠
        if (H[i].end < W[j].end)
            i++;
        else
            j++;
    }
    cout << total_time << endl;
    return 0;
}
