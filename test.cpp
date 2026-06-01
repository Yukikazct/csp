#include<iostream>
using namespace std;

bool cmp(int a , int b)
    {
        return a > b;
    }
int main()
{
    vector<int> v = {1, 2, 3, 4, 5};
    sort(v.begin(), v.end(), cmp);
    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i] << " ";
    }
    return 0;
}