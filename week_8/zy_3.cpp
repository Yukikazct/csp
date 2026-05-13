#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

struct BIT {
    int n;
    vector<ll> tr; 

    BIT(int _n) : n(_n), tr(_n + 1, 0) {}

    void add(int i, ll k) 
    {
        for (; i <= n; i += i & -i)
            tr[i] += k;
    }

    ll query(int i) 
    {
        ll res = 0;
        for (; i; i -= i & -i)
            res += tr[i];
        return res;
    }

 
    ll range_query(int l, int r)
    {
        return query(r) - query(l - 1);
    }
};

int main() {

    int n, q;
    cin >> n >> q;
    BIT bit(n);
    for (int i = 1; i <= n; ++i) {
        ll x;
        cin >> x;
        bit.add(i, x);
    }

    while (q--) {
        int op;
        cin >> op;
        if (op == 1) 
        {
            
            int i; ll x;
            cin >> i >> x;
            bit.add(i, x);
        } 
        else 
        {
            int l, r;
            cin >> l >> r;
            cout << bit.range_query(l, r) << '\n';
        }
    }
    return 0;
}