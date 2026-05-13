#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

struct Program {
    int time;       // 运行时间
    int memory;     // 内存占用
};

// 树状数组：支持单点修改、前缀和查询
struct BIT {
    vector<int> tree;
    int n;
    
    BIT(int size = 0) { init(size); }
    
    void init(int size) 
    {
        n = size;
        tree.assign(n + 1, 0);
    }
    
    // 在 pos 位置增加 val
    void add(int pos, int val) 
    {
        for (; pos <= n; pos += pos & -pos) 
        {
            tree[pos] += val;
        }
    }
    
    // 查询 [1, pos] 的前缀和
    int query(int pos) 
    {  
        int res = 0;
        for (; pos > 0; pos -= pos & -pos) 
        {
            res += tree[pos];
        }
        return res;
    }
};

int main() 
{
    
    int N;
    cin >> N;
    
    vector<Program> programs(N);
    vector<int> allMemory;  // 收集所有内存值用于离散化
    
    for (int i = 0; i < N; i++) 
    {
        cin >> programs[i].time >> programs[i].memory;
        allMemory.push_back(programs[i].memory);
    }
    
    // 离散化：将内存值映射到 1~M 的连续区间，便于树状数组操作
    sort(allMemory.begin(), allMemory.end());
    allMemory.erase(unique(allMemory.begin(), allMemory.end()), allMemory.end());
    
    auto getId = [&](int mem) 
    {
        return lower_bound(allMemory.begin(), allMemory.end(), mem) - allMemory.begin() + 1;
    };
    
    // 按运行时间升序，时间相同则按内存升序
    // 时间相同的程序，内存小的先处理，确保内存大的查询时能统计到内存小的
    sort(programs.begin(), programs.end(), [](const Program& a, const Program& b) 
    {
        if (a.time != b.time) return a.time < b.time;
        return a.memory < b.memory;
    });
    
    BIT bit(allMemory.size());
    vector<int> ans(N, 0);  // ans[i] 记录得分为 i 的程序数量
    
    for (int i = 0; i < N; i++) 
    {
        int memId = getId(programs[i].memory);
        // 查询当前程序内存值在已处理程序中的排名
        int score = bit.query(memId);
        ans[score]++; 
        // 将当前程序加入树状数组，供后续程序查询
        bit.add(memId, 1);
    }
    
    for (int i = 0; i < N; i++) 
    {
        cout << ans[i] << '\n';
    }
    
    return 0;
}