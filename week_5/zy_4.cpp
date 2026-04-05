#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main()
{
    int n;
    long long K;
    cin>>n>>K;
    vector<long long> a(n);
    for(int i = 0; i < n; i++)
    {
        cin>>a[i];
    }
    sort(a.begin(), a.end());
    int left = 0;
    long long cnt = 0;
    
 for(int right = 1; right < n ; right++)
 {
    if(a[right] - a[left] <= K)
    {
        cnt++;
    }
    left++;//如果小于等于K，那么向右移动表示删除，如果大于K，那么right向右移动更加不可能小于等于K，所以也要向右移动
 }
    cout<<cnt<<endl;
}