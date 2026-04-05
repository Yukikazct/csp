#include<bits/stdc++.h>
using namespace std;

int main()
{
    int n;  
    int x, y;
    cin >> n >> x >> y;
    int cost_min, cost_max;
    if(x < y) {cost_min = x; cost_max = y;}
    else {cost_min = y; cost_max = x;}
    
    int time_min = 0;
    int time_max = 0;
    n--;// 第一份由较快的机器完成
    time_min = cost_min;
    time_max = cost_min;//慢机器在等待
    
    while(n > 0)
    {
        // 判断慢机器是否能比快机器先完成下一份
        while(time_max + cost_max <= time_min + cost_min && n > 0)
        {
            time_max += cost_max;
            n--;
        }
        if(n == 0) break;  
        
        
        time_min += cost_min;
        n--;
    }
    cout << max(time_min, time_max) << endl;  
    return 0;
}