#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

typedef long long ll;
typedef pair<ll, int> P;

const ll INF = 1e18;
const int MAXN = 10005;
const int MAXM = 50005;

struct Edge
{
    int to, c, d;
};

int n, m, T;
vector<Edge> G[MAXN];
ll dist[MAXN];

bool check(int cap)
{
    for (int i = 1; i <= n; i++)
        dist[i] = INF;
    priority_queue<P, vector<P>, greater<P> > q;
    dist[1] = 0;
    q.push(make_pair(0, 1));
    while (!q.empty())
    {
        P cur = q.top();
        q.pop();
        int u = cur.second;
        if (cur.first != dist[u]) continue;
        if (u == n) break;
        for (int i = 0; i < (int)G[u].size(); i++)
        {
            Edge& e = G[u][i];
            if (e.c < cap) continue;
            int v = e.to;
            ll nd = dist[u] + e.d;
            if (nd < dist[v])
            {
                dist[v] = nd;
                q.push(make_pair(nd, v));
            }
        }
    }
    return dist[n] <= T;
}

int main()
{
    int X;
    cin >> X;
    while (X--)
    {
        cin >> n >> m >> T;
        for (int i = 1; i <= n; i++)
            G[i].clear();

        int maxc = 0;
        for (int i = 1; i <= m; i++)
        {
            int a, b, c, d;
            cin >> a >> b >> c >> d;
            G[a].push_back({b, c, d});
            G[b].push_back({a, c, d});
            if (c > maxc) maxc = c;
        }

        int lo = 0, hi = maxc, ans = 0;
        while (lo <= hi)
        {
            int mid = (lo + hi) / 2;
            if (check(mid))
            {
                ans = mid;
                lo = mid + 1;
            }
            else
            {
                hi = mid - 1;
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
