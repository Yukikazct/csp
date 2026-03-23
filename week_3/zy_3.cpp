#include<iostream>
#include<queue>
#include<vector>
using namespace std;
//这是bfs策略的简单应用
int bfs(int N,int A,int B,vector<int> &K)
{
    if(A==B)//如果起点和终点相同，直接返回0步
    {
        return 0;
    }
    vector<bool> visited(N+1,false);//已访问过的节点
    queue<pair<int,int>> q;
    q.push({A,0});//从起点开始，起始为0步
    visited[A] = true;
    while(!q.empty())
    {
        auto[current,steps] = q.front();//取出队列首元素
        q.pop();//弹出

        int up = current + K[current-1];//向上升
        if(up == B)
        {
            return steps + 1;
        }
        if(up <= N && up >= 1 && !visited[up])//在范围内且未被访问过
        {
            visited[up] = true;
            q.push({up,steps+1});//记录操作
        }

        int down = current - K[current-1];//向下降 同上
        if(down == B)
        {
            return steps + 1;
        }
        if(down >= 1 && down <= N && !visited[down])
        {
            visited[down] = true;
            q.push({down,steps+1});
        }
    }
    return -1;
}

int main()
{
    int N,A,B;
    while(cin>>N){
        if(N==0)
        {
        return 0;
        }
    
    cin>>A>>B;
    vector<int> K(N);
    for(int i=0;i<N;i++)
    {
        cin>>K[i];
    }
    cout<<bfs(N,A,B,K)<<endl;//调用bfs方法
}
}