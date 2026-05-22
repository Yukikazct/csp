#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main()
{
    int N, V;
    cin >> N >> V;
    vector<int> w(N);
    vector<int> c(N);
    vector<int> group(N);

    int K = 0;
    for(int i = 0; i < N; i++)
    {
        cin >> w[i] >> c[i] >> group[i];
        if(group[i] > K) K = group[i];
    }
    vector<int> dp(V + 1, 0);


    for(int k=1;k<=K;k++)
    {
        for(int j=V;j>=0;j--)
        {
            
            for(int i=0;i<N;i++)
            {
                if(group[i]==k && j>=w[i])
                {
                    dp[j] = max(dp[j],dp[j-w[i]]+c[i]);
                }
            }
        }
    }

    cout << dp[V] << endl;
    return 0;
}