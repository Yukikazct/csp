#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

int main()
{
    int r , y , g;
    cin >> r >> y >> g;
    int n;
    cin >> n;
    long long time = 0;
    while(n--)
    {
        int  k ,t;
        cin >> k >> t;
        if(k == 0)
        {
            time += t;
        }
        else if(k == 1)
        {
            time = time + t ;
        }
        else if(k == 2)
        {
            time = time + t + r;
        }
        else
        {
            continue;
        }
        
       
    }
    cout<<time<<endl;
    return 0;
}