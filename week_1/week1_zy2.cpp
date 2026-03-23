#include<iostream>
using namespace std;

int main()
{
    float A,B;
    cin>>A>>B;
    float baifenbi = (A-B)*100/A;
    printf("%.3f\n",baifenbi);
    return 0;
}