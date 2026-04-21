#include <iostream>
#include <vector>
#include<deque>
#include<algorithm>
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





struct qu
{
    int a;
    int b;
    long long price;

};

bool cmp(qu a , qu b)
{
    return a.price < b.price;
}

int main() 
{
    long long n , m;
    long long p; 
    cin>>n>>m>>p;
    long long cost = n * p;
    DSU dsu(n);
    long long k = n  ;
    long long qu_cost = 0;

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

    sort(shui_qu.begin() , shui_qu.end() , cmp);

    int times = shui_qu.size();
    while(times--)
    {   
        long long temp_cost ;
        qu temp = shui_qu.front();
        shui_qu.pop_front();
        int A = temp.a;
        int B = temp.b;
        if (dsu.unite(A, B)) 
        {
            k--; 
            qu_cost += temp.price; 
            temp_cost = qu_cost + k * p;
        }
      
        if(temp_cost < cost)
        {
            cost = temp_cost;
        }
        
    }
    cout<<cost<<endl;
    return 0;
}