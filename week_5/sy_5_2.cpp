#include<iostream>
#include<vector>
using namespace std;

typedef long long ll;
ll magic_cost(ll h, ll k, ll& new_h)
{
    ll cost = (1 + k) * k / 2 + h * k;
    new_h = h + k;
    return cost;
}

ll calc_total(const vector<ll>& nums, int n, int pos)
{
    ll total = 0;
    ll h = 0;
    for (int i = 0; i < n; ++i)
    {
        ll k = nums[i];
        if (i == pos)
            h = 0;
        ll new_h;
        total += magic_cost(h, k, new_h);
        h = new_h;
    }
    return total;
}

int main()
{
    int n;
    cin >> n;
    int sum = 0;
    vector<ll> nums(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> nums[i];
        sum += nums[i];
    }
    double half = sum / 2.0;
    int cnt = 0;
    int possible_1;
    int possible_2;
    for(int i = 0; i < n; ++i)
    {
        cnt += nums[i];
        if(cnt - half >= 0)
        {
            possible_1 = i;
            break;
        }
    }
    possible_2 = possible_1 - 1;
    


    ll ans = calc_total(nums, n, -1); 
    // 枚举
    for (int i = possible_1-5; i <= possible_1+5; ++i)
    {
        ll now = calc_total(nums, n, i);
        if (now < ans)
            ans = now;
    }

    cout << ans << endl;
    return 0;
}
