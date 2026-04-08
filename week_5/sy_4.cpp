#include<iostream>
#include<vector>

using namespace std;

int main()
{
    int n;
    cin>>n;
    vector<int> a(n);
    int sum = 0;
    for(int i = 0; i < n ; i++)
    {
        cin>>a[i];
        sum += a[i];
    }
    if(sum % 2 != 0)
    {
        cout<<"0"<<endl;
        return 0;   
    }
    else
    {
        int half_sum = sum / 2;
        int cnt = 0;
        int current_sum = 0;
        for(int i = 0; i < n-1; i++)
        {
            current_sum += a[i];
            if(current_sum == half_sum)
            {
                cnt++;
            }
        }
        cout<<cnt<<endl;
    }
    return 0;
    

}