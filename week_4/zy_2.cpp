#include<iostream>
#include<vector>
#include<string>
using namespace std;

int main()
{
    int n;
    cin >> n;
    string s;
    cin >> s;

    vector<vector<int>> pre(n + 1, vector<int>(26, 0));
    for (int i = 1; i <= n; i++) {
        pre[i] = pre[i - 1];
        int idx = s[i-1] - 'A';
        pre[i][idx]++;
    }


    int l = 1;       
    int min_len = n;  

    for (int r = 1; r <= n; r++) {
        while (1) {
            bool judge = true;
            for (int c = 0; c < 26; c++) {
                if (pre[r][c] - pre[l-1][c] == 0) {
                    judge = false;
                    break;
                }
            }
            if (judge) {
                min_len = min(min_len, r - l + 1);
                l++; 
            } 
            else {
                break;
            }
        }
    }

    cout << min_len << endl;
    return 0;
}