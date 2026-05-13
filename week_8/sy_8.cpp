#include<iostream>
#include<vector>
using namespace std;

int main()
{
    vector<char> input;
    char ch;
    while(cin >> ch)
    {
        if(ch >= '0' && ch <= '9')
        {
            input.push_back(0);
        }
        else if(ch >= 'a' && ch <= 'z')
        {
            input.push_back(1);
        }
        else if(ch >= 'A' && ch <= 'Z')
        {
            input.push_back(2);
        }
    }
    int size = input.size();
    if(size < 6)
    {
        cout<< 0 << endl;
        return 0;
    }
    int ans = 0;
    bool is_num = false;
    bool is_lower = false;
    bool is_upper = false;
    for(int i = 0 ; i < size ; i++)
    {
        if(input[i] == 0 && !is_num)
        {
            ans++;
            is_num = true;
            is_lower = false;
            is_upper = false;
        }
        else if(input[i] == 1 && !is_lower)
        {
            ans++;
            is_lower = true;
            is_num = false;
            is_upper = false;
        }
        else if(input[i] == 2 && !is_upper)
        {
            ans++;
            is_upper = true;
            is_num = false;
            is_lower = false;
        }
        

    }
    cout << ans << endl;
}