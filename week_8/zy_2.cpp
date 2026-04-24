#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int> v; 
    int m = n;      
    
    while(m--)      
    {
        int num;
        cin >> num;
        v.push_back(num);
    }
    
    sort(v.begin(), v.end()); 
    cout << v.back() << " ";
    
    double mid;
    if(n % 2 == 1)  
    {
        mid = v[n / 2]; 
        printf("%.0f ", mid);
    }
    else  
    {
        mid = (v[n/2 - 1] + v[n/2]) / 2.0;
        if(mid == (int)mid)  
        {
            printf("%.0f ", mid);
        }
        else
        printf("%.1f ", mid);
    }
    cout << v[0] << endl;
    
    return 0;
}