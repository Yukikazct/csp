#include<iostream>
using namespace std;

int main()
{
    char a[4];
    string s;
    cin>>s;
    char c = s[0];
    for(int i = 0;i < 3;i++)
    {
        if(s[i] != c)
        {
            cout<<"Lost"<<endl;
            return 0;
        }
    }
    cout<<"Won"<<endl;
    return 0;
}