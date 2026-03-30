#include<iostream>
#include<stack>
#include<vector>
using ll = long long;
using namespace std;


int main()
{
    vector<int> rectangle ; 
    int n;
    cin>>n;
    while(n--)
    {
        int x;
        cin>>x;
        rectangle.push_back(x);
    }
    rectangle.push_back(0);//哨兵
    stack<int> s;
    ll max_area = 0;
    for(int i = 0 ; i < rectangle.size() ; i++)
    {
        while(!s.empty() && rectangle[s.top()] > rectangle[i])
        {
            int height = rectangle[s.top()];
            s.pop();
            int width;
            if(s.empty()) width = i;
            else width = i - s.top() - 1;
            max_area = max(max_area , (ll)height * width);
        }
        s.push(i);
    }
    cout << max_area << endl;
    return 0;
}