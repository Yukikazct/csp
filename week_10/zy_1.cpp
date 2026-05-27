#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    vector<int> next_day = a;
    next_day[0] = int (float(a[0] + a[1]) / 2 );
    next_day[n - 1] = int (float(a[n - 2] + a[n - 1]) / 2 );
    for (int i = 1; i < n - 1; i++)
    {
        next_day[i] = int (float(a[i - 1] + a[i] + a[i + 1]) / 3 );
    }
    for (int i = 0; i < n; i++)
    {
        cout << next_day[i] << " ";
    }  
    return 0;
}