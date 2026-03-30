/*
#include<iostream>
#include<vector>
#include<climits>
using namespace std;

const int MOD = 1e9 + 7;

int main()
{
    int n;
    cin>>n;
    vector<vector<int>> num(n+1,vector<int>(101,0));
    int m;
    cin>>m;

    while(m--)
    {
        int l,r,c,b;
        cin>>l>>r>>c>>b;

        int x = c;
        for(int p=2; p*p<=x; p++){
            if(x%p==0){
                int cnt=0;
                while(x%p==0) cnt++,x/=p;
                for(int i=l;i<=r;i++) num[i][p] += cnt*b;
            }
        }
        if(x>1){
            for(int i=l;i<=r;i++) num[i][x] += b;
        }
    }

    long long ans = 1;
    for(int p=2; p<=100; p++){
        int min_cnt = INT_MAX;
        for(int i=1; i<=n; i++){
            min_cnt = min(min_cnt, num[i][p]);
        }
        if(min_cnt > 0){
            long long temp = 1;
            for(int i=0; i<min_cnt; i++){
                temp = temp * p % MOD;
            }
            ans = ans * temp % MOD;
        }
    }

    cout<<ans<<endl;
    return 0;
}
    最原始没有优化的版本 耗时极大*/



#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;
const int MOD = 1e9 + 7;
vector<pair<int, int>> fac[105];

// 100内质因数分解表
void init() {
    for (int i = 1; i <= 100; ++i) {
        int x = i;
        for (int p = 2; p * p <= x; ++p) {
            if (x % p == 0) {
                int cnt = 0;
                while (x % p == 0) cnt++, x /= p;
                fac[i].emplace_back(p, cnt);
            }
        }
        if (x > 1) fac[i].emplace_back(x, 1);
    }
}

// 快速幂
ll qpow(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1    ) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

int main() {
    init();
    int n, m;
    cin >> n >> m;
    
    vector<vector<ll>> diff(105, vector<ll>(n + 2, 0));

    // 你的核心代码（完全不动）
    while (m--)
    {
        int l, r, c, b;
        cin >> l >> r >> c >> b;
      for (int i = 0; i < fac[c].size(); i++) 
       {
            int p = fac[c][i].first;
            int cnt = fac[c][i].second;
            ll add = (ll)cnt * b;
            diff[p][l] += add;
            diff[p][r + 1] -= add;
        }
    }

    ll ans = 1;
    for (int p = 2; p <= 100; ++p) {
        ll now = 0, min_num = 1e18;
        for (int i = 1; i <= n; ++i) {
            now += diff[p][i];
            min_num = min(min_num, now);
        }
        
        // 优化：只用快速幂替换朴素循环，其余不动
        if (min_num > 0) {
            ans = ans * qpow(p, min_num) % MOD;
        }
    }

    cout << ans << endl;
    return 0;
}