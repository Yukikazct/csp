#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;

int bfs(int n ,vector<vector<int>>& adj , int s, vector<int>& dist)
{
    vector<bool> visited(n + 1 , false);
    queue<int> q;
    dist.assign(n + 1, 0); 

    visited[s] = true;
    q.push(s);

    int max_ = 0;
    int far_node = s;

    while(!q.empty())
    {
        int u = q.front();
        q.pop();

        for(int v : adj[u])
        {
            if(!visited[v])
            {
                visited[v] = true;
                dist[v] = dist[u] + 1;
                if(dist[v] > max_)
                {
                    max_ = dist[v];
                    far_node = v;
                }
                q.push(v);
            }
        }
    }
    return far_node;
}

int main()
{
    int n;
    cin>>n;
    vector<vector<int>> adj(n + 1);

    for(int i=0;i<n-1;i++)
    {
        int a , b;
        cin>>a>>b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<int> dist_u, dist_v;


    int u = bfs(n, adj, 1, dist_u);
    int v = bfs(n, adj, u, dist_u);
    bfs(n, adj, v, dist_v);
    for(int i = 1 ; i<= n ;i++)
    {
        cout << max(dist_u[i], dist_v[i]) << " ";
    }

    return 0;
}