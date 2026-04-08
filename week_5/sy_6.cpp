#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main()
{
    int n;
    cin>>n;
    vector<int> a(n);
    for(int i = 0; i < n; i++)
    {
        cin>>a[i];
    }
    int a_max = *max_element(a.begin(), a.end());
    int cnt = 0;
    int cnt_max = 0;
    int i = 0;
    for(int i = 0 ; i < n; i++)
    {
        if(a[i] == a_max)
        {
            cnt++;
        }
        else
        {
            if(cnt > cnt_max)
            {
                cnt_max = cnt;
            }
            cnt = 0;
        }
    }
    cnt_max = max(cnt_max, cnt);//若最后一个数也是最大值，那么在循环中就没有更新cnt_max，所以要在循环结束后再更新一次
    cout<<a_max<<" "<<cnt_max<<endl;、
}