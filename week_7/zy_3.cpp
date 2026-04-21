#include <iostream>
#include <vector>
using namespace std;

struct DSU 
{
    vector<int> fa;
    DSU(int n) 
    { 
        fa.resize(n + 1);         
        for (int i = 1; i <= n; i++) 
            fa[i] = i;             
    }
    int find(int x) 
    { 
        if(fa[x] != x)
        {
            fa[x] = find(fa[x]);
        }
        return fa[x];
    }
    bool unite(int x, int y) 
    { 
        if(find(x) == find(y)) return false;
        else
        {
            fa[find(x)] = find(y); 
            return true;
        }
        
        
    }
};


int main() 
{
    int n , m;
    cin>>n>>m;
    DSU dsu(n);
    int k = n - 1;
    vector<pair<int , int>> edges;
    while(m--)
    {
        int a ,b;
        cin>>a>>b;
        if (dsu.unite(a, b)) 
        {
            k--;  
        }
        cout<<k<<endl;
    }
}


