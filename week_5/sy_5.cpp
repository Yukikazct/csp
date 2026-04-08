#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

typedef long long ll;

int main()
{
    int n;
    cin >> n;
    vector<ll> nums(n);
    for (int i = 0; i < n; ++i)
        cin >> nums[i];
    
    vector<ll> to_n(n);
    ll h = 0, total = 0;
    for (int i = 0; i < n; ++i) {
        ll k = nums[i];
        total += (1 + k) * k / 2 + h * k;
        h += k;
        to_n[i] = total;
    }
    //不用药水
    ll ans = total;
    
    //  0疲劳时，爬 i到n-1 的总代价
    vector<ll> forword_i_to_n(n + 1);
    h = 0;
    total = 0;
    for (int i = n - 1; i >= 0; --i) {
        ll k = nums[i];
        total += (1 + k) * k / 2 + h * k;
        h += k;
        forword_i_to_n[i] = total;
    }
    
    // 枚举在位置 i 用药水
    for (int i = 0; i < n; ++i) {
        ll left = (i == 0) ? 0 : to_n[i - 1];
        ll right = forword_i_to_n[i];
        if (left + right < ans)
            ans = left + right;
    }
    
    cout << ans << endl;
    return 0;
}