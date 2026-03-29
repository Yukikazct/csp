#include<iostream>
#include<deque>
#include<vector>
using namespace std;
/*单调队列*/
int main() {
    int n, k;
    cin >> n >> k;
    vector<int> num(n);
    for (int i = 0; i < n; i++) {
        cin >> num[i];
    }

    deque<int> q_max;
    deque<int> q_min;
    vector<int> ans_max;
    vector<int> ans_min;

    for (int i = 0; i < n; i++) {
        while (!q_max.empty() && num[q_max.back()] <= num[i])
        {
            q_max.pop_back();
        }
        while(!q_min.empty()&& num[q_min.back()] >= num[i])
        {
            q_min.pop_back();
        }

        q_max.push_back(i);
        q_min.push_back(i);

        while (q_max.front() <= i - k) 
        {
            q_max.pop_front();
        }

        while(q_min.front() <= i - k)
        {
            q_min.pop_front();
        }

        if (i >= k - 1) 
        {
            ans_max.push_back(num[q_max.front()]);
        }

        if(i >= k - 1)
        {
            ans_min.push_back(num[q_min.front()]);
        }
    }


    for(int x : ans_min) cout << x << " ";
    cout << endl;
    for (int x : ans_max) cout << x << " ";
    cout << endl;
   
    return 0;
}