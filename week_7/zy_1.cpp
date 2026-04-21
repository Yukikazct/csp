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
    for(int i = 0; i < n ; i++)
    {
        cin>>c[i];
    }
    vector<int> ans(n,0);
    if(judge(c[0])) ans[0] = 1;
    else ans[0] = 0;
    for(int i = 1 ; i < n ; i++)
    {
        if(judge(c[i]))
        {
            ans[i] = ans[i - 1] + 1; 
        }
        else
        ans[i] = 0;
    }
    int final_ans = *max_element(ans.begin() , ans.end());
    cout<<final_ans<<endl;

    return 0;

}