#include <iostream>
#include <vector>
using namespace std;

int game(int n, int k)
{
    
    vector<int> players;
    for (int i = 1; i <= n; ++i) {
        players.push_back(i); 
    }

    int cnt = 1;  
    int idx = 0;  

    while (players.size() > 1)
    {
        bool taotai = (cnt % k == 0) || (cnt % 10 == k);
        
        if (taotai)
        {
            players.erase(players.begin() + idx);
            if (idx >= players.size() && !players.empty()) {
                idx = 0;
            }
        }
        else
        {
            idx = (idx + 1) % players.size();
        }
        cnt++;
    }

    return players[0];
}

int main()
{
    int n, k;
    cin >> n >> k;
    cout << game(n, k) << endl; 
    return 0;
}