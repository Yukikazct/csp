#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int N, V;
    cin >> N >> V;

    vector<long long> dp(V + 1, 0);

    for (int i = 0; i < N; i++)
    {
        int w, c, k; 
        cin >> w >> c >> k;

        int base = 1; // 二进制拆分的基数
        while (k > 0)
        {
            // 取当前部分的数量，不超过剩余数量k
            int cnt = min(base, k);
            int total_w = cnt * w;
            int total_c = cnt * c;

            // 倒序遍历容量，避免重复选取
            for (int j = V; j >= total_w; j--)
                dp[j] = max(dp[j], dp[j - total_w] + total_c);

            k -= cnt;       
            base *= 2;      //处理下一个幂次
        }
    }

    cout << dp[V] << endl;
    return 0;
}