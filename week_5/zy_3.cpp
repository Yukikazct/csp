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
        int sell = 0;
        int trade_count = 0;
        int i = 0;
        while(i < n - 1)
        {
            while(i < n -1 && a[i + 1] <= a[i])
            {
                i++;
            }
            buy = i;
            while(i < n - 1 && a[i + 1] >= a[i])
            {
                i++;
            }
            sell = i;
            if(sell > buy)
            {
                profits += a[sell] - a[buy];
                trade_count += 2;
            }


        }
        cout<<profits<<" "<<trade_count<<endl;
       
    }
    return 0;

}