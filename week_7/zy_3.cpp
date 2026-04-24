#include <iostream>
#include <vector>
using namespace std;

struct DSU //并查集
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
            fa[x] = find(fa[x]);//路径压缩
        }
        return fa[x];
    }
    bool unite(int x, int y) 
    { 
        if(find(x) == find(y)) return false;
        else
        {
            fa[find(x)] = find(y); //合并
            return true;
        }
        
        
    }
};


int main() 
{
    int n , m;
    cin>>n>>m;
    DSU dsu(n);
    int k = n - 1;//初始的连通分量数量为n，故需要n-1条边来连接所有的节点
    while(m--)
    {
        int a ,b;
        cin>>a>>b;
        if (dsu.unite(a, b)) 
        {
            k--;  //如果成功合并了两个不同的连通分量，说明连通分量数量减少了1
        }
        cout<<k<<endl;
    }
}


