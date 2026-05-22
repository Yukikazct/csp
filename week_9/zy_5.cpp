#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

typedef long long ll; 

int main()
{
    int N;
    ll V;
    cin >> N >> V;

    vector<ll> w(N), c(N);
    for(int i = 0; i < N; i++)
    {
        cin >> w[i] >> c[i];
    }

    int n1 = N / 2;
    int n2 = N - n1;

    vector<pair<ll, ll>> part1;
    for(int mask = 0; mask < (1 << n1); mask++)
    {
        ll total_w = 0, total_c = 0;
        for(int i = 0; i < n1; i++)
        {
            if(mask & (1 << i))
            {
                total_w += w[i];
                total_c += c[i];
                if(total_w > V) break; 
            }
        }
        if(total_w <= V)
            part1.emplace_back(total_w, total_c);
    }

    vector<pair<ll, ll>> part2;
    for(int mask = 0; mask < (1 << n2); mask++)
    {
        ll total_w = 0, total_c = 0;
        for(int i = 0; i < n2; i++)
        {
            if(mask & (1 << i))
            {
                total_w += w[n1 + i];
                total_c += c[n1 + i];
                if(total_w > V) break; 
            }
        }
        if(total_w <= V)
            part2.emplace_back(total_w, total_c);
    }

    sort(part2.begin(), part2.end());
    vector<ll> max_val(part2.size());
    max_val[0] = part2[0].second;
    for(int i = 1; i < part2.size(); i++)
    {
        max_val[i] = max(max_val[i-1], part2[i].second);
    }


    ll ans = 0;
    for(auto &p : part1)
    {
        ll w1 = p.first;
        ll c1 = p.second;
        ll remaining = V - w1;

        int l = 0, r = part2.size() - 1, pos = -1;
        while(l <= r)
        {
            int mid = (l + r) / 2;
            if(part2[mid].first <= remaining)
            {
                pos = mid;
                l = mid + 1;
            }
            else
            {
                r = mid - 1;
            }
        }

        if(pos != -1)
        {
            ans = max(ans, c1 + max_val[pos]);
        }
    }

    cout << ans << endl;
    return 0;
}