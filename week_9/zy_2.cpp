#include<iostream>
#include<vector>

using namespace std;

int main()
{
    int N ,V;
    cin >> N >> V;
    vector<int> w(N);
    vector<int> c(N);
    for(int i = 0; i < N; i++)
    {
        cin >> w[i] >> c[i];
    }
    vector<int> dp(V + 1, 0);
    for(int i = 0; i <= V; i++)
    {
        for(int j = 0 ; j < N ; j++)
        {
            if(i >= w[j])
            {
                dp[i] = max(dp[i], dp[i - w[j]] + c[j]);
            }
        }
    }
    cout << dp[V] << endl;
    return 0;
}