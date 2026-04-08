#include<bits/stdc++.h>
using namespace std;

int main()
{
    int n , k;
    cin>>n>>k;
    vector<int> a(n);
    for(int i = 0 ; i < n ; i++)
    {
        cin>>a[i];
    }

    double left = 0.0;
    double right = *max_element(a.begin() , a.end());//找出最大的绳子长度
    double mid = (left + right) / 2.0;
  


    while(right - left > 1e-6)//终止条件
    {
         int cnt = 0;
        for(int i = 0 ; i < n ; i++)
        {
            cnt += (int)(a[i] / mid);//每条绳子/mid取整数解，即为截出的绳子数量
            if(cnt >= k)
            {
                break;//如果已经截取出了K条，就跳出循环
            }
        }
        if(cnt >= k)
        {
            left = mid;//将左指针右移动，尝试更长的绳子长度
        }
        else
        {
            right = mid;//如果截取出的绳子数量不足K条，就将右指针左移动，尝试更短的绳子长度
        }
        mid = (left + right) / 2.0;//更新mid值

    }
    printf("%.6f\n" , left);
}