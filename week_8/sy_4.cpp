#include<iostream>
#include<vector>

using namespace std;

int main()
{
    int n;
    cin>>n;
    long long h, x;
    cin>>h>>x;
    vector<long long> v(n);
    for(int i=0;i<n;i++)
    {
        cin>>v[i];
    }
    int be_defeated = 0;
    bool finish_all = true;

    for(int i=0;i<n;i++)
    {
       h -= max(v[i] - x, 0LL);
         if(h <= 0)
         {
             finish_all = false;
             break;
         }
         else
         {
            be_defeated++;
            x = max(x, v[i]);
         }
    }
    if(finish_all)
    {
        cout<<"YES"<<endl;
        cout<<h<<endl;
    }
    else
    {
        cout<<"NO"<<endl;
        cout<<be_defeated<<endl;
    }
    
    return 0;
}