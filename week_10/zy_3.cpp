#include <iostream>
#include <vector>
#include <climits>
using namespace std;

struct Edge
{
    int u, v, w;
};

// Bellman-Ford 判断是否存在负环
bool hasNegativeCycle(int n, const vector<Edge>& edges)
{
    // dist 初始化为 0，等价于添加超级源点，确保能检测到所有负环
    vector<int> dist(n + 1, 0);

    for (int i = 1; i <= n; i++)
    {
        bool updated = false;
        for (const auto& e : edges)
        {
            if (dist[e.u] + e.w < dist[e.v])
            {
                dist[e.v] = dist[e.u] + e.w;
                updated = true;
                // 第 n 轮仍能松弛 → 存在负环
                if (i == n) return true;
            }
        }
        // 无松弛可提前/结束
        if (!updated) break;
    }
    return false;
}

int main()
{
    int F;
    cin >> F;
    while (F--)
    {
        int n, m, w;
        cin >> n >> m >> w;

        vector<Edge> edges;
        // 双向道路：拆成两条有向边，权值为正
        for (int i = 0; i < m; i++)
        {
            int s, e, t;
            cin >> s >> e >> t;
            edges.push_back({s, e, t});
            edges.push_back({e, s, t});
        }
        // 单向虫洞：权值为负（时光倒流）
        for (int i = 0; i < w; i++)
        {
            int s, e, t;
            cin >> s >> e >> t;
            edges.push_back({s, e, -t});
        }

        cout << (hasNegativeCycle(n, edges) ? "YES" : "NO") << '\n';
    }
    return 0;
}
