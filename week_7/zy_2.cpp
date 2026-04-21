#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

bool judge(char c)
{
    if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' )
    {
        return true;
    }
    else
    return false;
}

int main()
{
    int n;
    cin>>n;
    vector<char> c(n);
    for(int i = 0; i < n; i++)
    {
        cin>>c[i];
    }
    vector<char> out;
    bool to_out = true;
    for(int i = 0 ; i < n ; i++)
    {
        if(judge(c[i]) && to_out)
        {
            out.push_back(c[i]);
            to_out = false;
        }
        if(!judge(c[i]))
        {
            out.push_back(c[i]);
            to_out = true;
        }
    }
    
    for(int i = 0; i < out.size() ; i++)
    {
        cout<<out[i];
    }
    return 0;
}