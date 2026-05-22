#include<iostream>
#include<vector>
#include<unordered_set>

using namespace std;

int solve(int n, vector<int>& a) 
{
    unordered_set<int> seen;
    for (int i = n - 1; i >= 0; --i) 
    {
        if (seen.count(a[i])) 
        {
            return i + 1;
        }
        seen.insert(a[i]);
    }
    return 0;
}

int main()
{
    int n;
    cin>>n;
    vector<int> v(n);
    for(int i=0;i<n;i++)
    {
        cin>>v[i];
    }
    cout<<solve(n,v)<<endl;

    return 0;

}