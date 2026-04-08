#include<iostream>
#include<vector>
using namespace std;    

int main()
{
    int T;
    cin>>T;
    while(T--)
    {
        int n;
        cin>>n;
        vector<int> a(n);
        for(int i = 0; i < n; i++)
        {
            cin>>a[i];
        }
        long long profits = 0;
        int buy = 0;
        int sell = 0;//记录买入和卖出的索引
        int trade_count = 0;
        int i = 0;
        while(i < n - 1)
        {
            while(i < n -1 && a[i + 1] <= a[i])//如果是连续下跌，就不买入，直到找到一个局部最低点
            {
                i++;
            }
            buy = i;
            while(i < n - 1 && a[i + 1] >= a[i])//如果是连续上涨，就不卖出，直到找到一个局部最高点
            {
                i++;
            }
            sell = i;
            if(sell > buy)//卖一定在上次买之后
            {
                profits += a[sell] - a[buy];
                trade_count += 2;//一次买入一次卖出
            }


        }
        cout<<profits<<" "<<trade_count<<endl;
       
    }
    return 0;

}