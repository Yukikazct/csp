#include<iostream>
#include<vector>
#include<queue>
using namespace std;

const int dir[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> grid(n, vector<int>(m));
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> grid[i][j];

    int high_points = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (!visited[i][j]) {
                queue<pair<int, int>> q;
                q.push({i, j});
                visited[i][j] = true;
                while (!q.empty()) {
                    auto [x, y] = q.front();
                    q.pop();
                    bool is_high = true;
                    for (int d = 0; d < 4; ++d) {
                        int nx = x + dir[d][0];
                        int ny = y + dir[d][1];
                        if (nx >=0 && nx <n && ny >=0 && ny <m) {
                            if (grid[nx][ny] >= grid[x][y]) {
                                is_high = false;
                                break;
                            }
                        }
                    }
                    if (is_high) high_points++;
                    for (int d = 0; d <4; ++d) {
                        int nx = x + dir[d][0];
                        int ny = y + dir[d][1];
                        if (nx >=0 && nx <n && ny >=0 && ny <m && !visited[nx][ny]) {
                            visited[nx][ny] = true;
                            q.push({nx, ny});
                        }
                    }
                }
            }
        }
    }

    cout << high_points << endl;
    return 0;
}