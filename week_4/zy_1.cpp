#include<iostream>
#include<vector>
using namespace std;

int main()
{
    int n;
    cin>>n;
    string s;
    cin>>s;
    vector<vector<int>> pre(n+1 , vector<int>(26,0));
    for(int i = 1 ; i <= n ; i++)
    {
        pre[i] = pre[i - 1];
        int idx = s[i-1] - 'A';
        pre[i][idx]++;//记录第n个出现的字母
    }

    int m;
    cin>>m;
    while(m--)
    {
        int l ,r;
        cin>>l>>r;
        bool judge = true;
        for(int i = 0 ; i < 26 ; i++)
        {
            if(pre[r][i] - pre[l-1][i] == 0 )//前缀和判断
            {
                judge = false;
                cout<<"NO"<<endl;
                break;
            }
        }
        if(judge) cout<<"YES"<<endl;
    }




    return 0;
}
