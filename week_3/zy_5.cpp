#include <vector>
#include <iostream>

using namespace std;

int n, k;
vector<string> board;
vector<bool> used_col;
int ans = 0;
void dfs(int row, int cnt) {
    if (cnt + (n - row) < k) return;

    if (cnt == k)
    {
        ans++;
        return;
    }
    if (row == n) return;

    for (int col = 0; col < n; col++) {
        if (board[row][col] == '#' && !used_col[col]) {
            used_col[col] = true; 
            dfs(row + 1, cnt + 1); 
            used_col[col] = false;
        }
    }
    dfs(row + 1, cnt);
}

int main()
{
    while(cin>>n>>k)
    {
        if(n==-1 && k==-1)
        {
           return 0;
        }
        board.clear();
        for(int i = 0; i < n; i++)
        {
            string row;
            cin >> row;
            board.push_back(row);
        }
        used_col.assign(n, false);
        ans = 0;
        dfs(0, 0);
        cout << ans << endl;
    }
}