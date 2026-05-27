#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef long long ll;
typedef pair<ll, int> P;

const ll INF = 1e18;
const int MAXN = 1000005;

int n, m;
vector<P> G[MAXN], rG[MAXN];
ll d1[MAXN], d2[MAXN];
bool vis[MAXN];

void dijkstra(int s, vector<P> graph[], ll dist[])
{
    for (int i = 1; i <= n; i++)
    {
        dist[i] = INF;
        vis[i] = false;
    }
    priority_queue<P, vector<P>, greater<P> > q;
    dist[s] = 0;
    q.push(make_pair(0, s));
    while (!q.empty())
    {
        P cur = q.top();
        q.pop();
        int u = cur.second;
        if (vis[u]) continue;
        vis[u] = true;
        for (int i = 0; i < (int)graph[u].size(); i++)
        {
            int v = graph[u][i].second;
            ll w = graph[u][i].first;
            if (dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;
                q.push(make_pair(dist[v], v));
            }
        }
    }
}

int main()
{

    int T;
    cin >> T;
    while (T--)
    {
        cin >> n >> m;
        for (int i = 1; i <= n; i++)
        {
            G[i].clear();
            rG[i].clear();
        }
        for (int i = 1; i <= m; i++)
        {
            int u, v;
            ll w;
            cin >> u >> v >> w;
            G[u].push_back(make_pair(w, v));
            rG[v].push_back(make_pair(w, u));
        }

        dijkstra(1, G, d1);
        dijkstra(1, rG, d2);

        ll ans = 0;
        for (int i = 1; i <= n; i++)
            ans += d1[i] + d2[i];
        cout << ans << '\n';
    }
    return 0;
}
