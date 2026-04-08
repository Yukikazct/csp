#include<iostream>
#include<vector>

using namespace std;

bool is_7_times(int x)
    {
        if(x % 7 == 0)
        {
            return true;
        }
        else return false;
    }


bool have_7(int x)
{
    while(x > 0)
    {
        if(x % 10 == 7)
        {
            return true;
        }
        x /= 10;
    }
    return false;
}

int main()
{
    int n , m;
    cin>>n>>m;
    vector<int> cnt(n,0);
    for(int i = 1 ; i <=m ; i++)
    {
        int person = (i - 1) % n;
        if(is_7_times(i) || have_7(i))
        {
            cnt[person]++;
        }
    }
    for(int i = 0 ; i < n ; i++)
    {
        cout<<cnt[i]<<" ";
    }

   return 0;
}