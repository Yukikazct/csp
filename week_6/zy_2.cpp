#include<iostream>
using namespace std;

int main()
{
    int n;
    cin >> n;
    int cnt = 0;
    while(n > 0)
    {
        if(n % 2 == 0)
        {
           cout<<0;
           cnt++;
              n = n / 2;
        }
        else
        {
            cout<<1;
            cnt++;
            n = n / 2;
        }
    }
    cout<<cnt<<endl;
}