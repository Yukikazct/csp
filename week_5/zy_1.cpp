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
    double right = *max_element(a.begin() , a.end());
    double mid = (left + right) / 2.0;
  


    while(right - left > 1e-6)
    {
         int cnt = 0;
        for(int i = 0 ; i < n ; i++)
        {
            cnt += (int)(a[i] / mid);
            if(cnt >= k)
            {
                break;
            }
        }
        if(cnt >= k)
        {
            left = mid;
        }
        else
        {
            right = mid;
        }
        mid = (left + right) / 2.0;

    }
    printf("%.6f\n" , left);
}