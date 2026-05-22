#include<iostream>
#include<vector>
#include<algorithm>
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
   for(int i = 0 ;i < N ; i++)
   {
         for(int j = V; j >= w[i]; j--)
         {
              dp[j] = max(dp[j], dp[j - w[i]] + c[i]);
         }
   }
    cout << dp[V] << endl;
    return 0;
}