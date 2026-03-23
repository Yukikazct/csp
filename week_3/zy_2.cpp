#include<iostream>
using namespace std;

int main()
{
    int input;
    int sum = 0;
    int plus = 0;
    while(cin>>input)
    {
        if(input==0)
        {
            break;
        }
        if(input == 1)
        {
            sum ++;
            plus = 0;
        }
        if(input == 2)
        {
            if(plus == 0)
            {
                plus = 2;
                sum += plus;
            }
            else
            {
                plus +=2;
                sum += plus;
            }
        }


    }
    cout<<sum<<endl;
    return 0;
}