#include <iostream>
#include <vector>
#include<deque>
#include<algorithm>
using namespace std;

struct DSU //并查集
{
    vector<int> fa;
    DSU(int n) 
    { 
        fa.resize(n + 1);         
        for (int i = 1; i <= n; i++) 
            fa[i] = i;   //初始化每个节点的父节点为自己       
    }
    int find(int x) 
    { 
        if(fa[x] != x)
        {
            fa[x] = find(fa[x]);
        }
        return fa[x];//路径压缩
    }
    bool unite(int x, int y) 
    { 
        if(find(x) == find(y)) return false;
        else
        {
            fa[find(x)] = find(y); 
            return true;//合并
        }
          
    }
};





struct qu
{
    int a;
    int b;
    long long price;

};

bool cmp(qu a , qu b)
{
    return a.price < b.price;//按照价格从小到大排序
}

int main() 
{
    long long n , m;
    long long p; 
    cin>>n>>m>>p;
    long long cost = n * p;//默认花费为给每块田都建一个抽水机
    DSU dsu(n);//并查集初始化
    long long k = n  ;
    long long qu_cost = 0;//修渠的花费

    deque<qu> shui_qu;

    while(m--)
    {
        int a , b;
        long long c;
        cin>>a>>b>>c;
        qu temp;
        temp.a = a;
        temp.b = b;
        temp.price = c;
        shui_qu.push_back(temp);
    }

    sort(shui_qu.begin() , shui_qu.end() , cmp);//将能修的渠按照价格从小到大排序

    int times = shui_qu.size();
    while(times--)
    {   
        long long temp_cost ;
        qu temp = shui_qu.front();//取出价格最低的渠修建
        shui_qu.pop_front();
        int A = temp.a;
        int B = temp.b;
        if (dsu.unite(A, B)) //能连通新区域的渠才建
        {
            k--; //如果成功合并了两个不同的连通分量，说明连通分量数量减少了1
            qu_cost += temp.price; //更新修渠的总花费
            temp_cost = qu_cost + k * p;//计算当前的总花费：修渠的花费加上剩余区域建抽水机的花费
        }
      
        if(temp_cost < cost)
        {
            cost = temp_cost;//更新最小花费
        }
        else
        {
            break;//如果当前的总花费已经不再减少，说明后续的渠修建只会增加总花费，可以停止修建
        }
        
    }
    cout<<cost<<endl;
    return 0;
}