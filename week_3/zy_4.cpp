#include<iostream>
#include<vector>

using namespace std;
bool prime(int n)
{
        if(n==1) return false;
        if(n==2) return true;
	for(int i=2;i*i<=n;i++)
	   if (n%i==0) return false;
	return true; 
}
    int n,k;
    vector<int> x;
    int ans = 0;

void dfs(int i , int cnt , int sum)//从0开始第i个数 之前已经选了cnt个 已选的和
{
    if(cnt + (n-i) < k )return;//可行性剪枝
    if(cnt == k)
    {
        if(prime(sum))
        {
            ans++;//如果是质数就+1
        }
        return;
    }
    if(i==n)return;
    dfs(i+1,cnt,sum);//不选这个数 跳过
    dfs(i+1,cnt+1,sum+x[i]);//选了这个数
    
}

int main()
{
    cin>>n>>k;
    for (int i = 0; i < n; ++i) 
    {
    int num;
    cin >> num;
    x.push_back(num);//将数字压入x
    }
    dfs(0,0,0);//从第1个数，目前选了0个数，和为0 的状态开始
    cout<<ans<<endl;
    return 0;
}



