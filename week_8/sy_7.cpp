#include <iostream>
#include <vector>
using namespace std;

int main() 
{
    int n;
    string T;
    cin >> n >> T;
    int m = T.size();
    string s = "01";
    while ((int)s.size() < n) 
    {
        int L = s.size();
        for (int i = 0; i < L; i++) 
        {
            s.push_back(s[i] == '0' ? '1' : '0');
        }
    }
    string text = s.substr(0, n);
    
    vector<int> pi(m, 0);
    for (int i = 1; i < m; i++) 
    {
        int j = pi[i - 1];
        while (j > 0 && T[i] != T[j]) 
        {
            j = pi[j - 1];
        }
        if (T[i] == T[j]) 
        {
            j++;
            pi[i] = j;
        }
    }
    

    long long cnt = 0;  
    int j = 0;
    for (int i = 0; i < n; i++) 
    {
        while (j > 0 && text[i] != T[j]) 
        {
            j = pi[j - 1];
        }
        if (text[i] == T[j]) 
        {
            j++;
        }
        if (j == m) 
        {
            cnt++;
            j = pi[j - 1]; 
        }
    }
    
    cout << cnt << "\n";
    return 0;
}