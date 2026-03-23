#include<iostream>
#include<string>
#include<cmath>
using namespace std;
 int main()
 {
    int n;
    cin>>n;
    string s;
    cin>>s;
    int R_num = 0,G_num = 0,B_num = 0;
    for(int i = 0;i < n;i++)
    {
        if(s[i] == 'R')
            R_num++;
        else if(s[i] == 'G')
            G_num++;
        else if(s[i] == 'B')
            B_num++;
    }
    int min_num = min(R_num,min(G_num,B_num));
    int ans = min_num ;
    cout<<ans<<endl;
    return 0;

 }