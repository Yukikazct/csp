#include <iostream>  
using namespace std;
const int Maxn=200010;

// 单调栈节点：x为最大值，y为该最大值对应的原序列位置
struct node
{
	long long x;
	int y;
}a[Maxn];

int m,tot,cnt,f[Maxn];
long long d,t,x,num[Maxn];
char ch[3];

// 并查集查找（路径压缩）
int find(int x)
{
	if(x!=f[x])f[x]=find(f[x]);
	return f[x];
}

int main()
{

	cin >> m >> d;  
	for(int i=1;i<=m;i++)
	{
		cin >> ch; 
		cin >> x;  
		if(ch[0]=='A')
		{
			// 实际美味度 = (输入值 + 上次答案) % p
			x+=t;
			x%=d;
			tot++;              // 序列长度+1
			num[tot]=x;         // 记录该位置的实际值
			f[tot]=tot;         // 并查集初始化：每个点独立成集
			// 维护单调递减栈：新元素会"覆盖"所有比它小的栈顶元素 被覆盖的元素所在集合合并到新元素位置
			while(x>a[cnt].x&&cnt)
			{
				f[a[cnt].y]=tot; // 将栈顶元素的集合合并到当前新元素
				cnt--;           // 栈顶出栈
			}
			// 新元素入栈
			a[++cnt].x=x;
			a[cnt].y=tot;
		}
		else
		{
			// 查询最后x个元素：区间 [tot-x+1, tot]
			// 找该区间左端点 tot-x+1 所在集合的代表元
			x=tot-x+1;
			int y=find(x);      // y 即为该区间的最大值位置
			t=num[y];           // 记录答案，供下次 A 操作使用
			cout << t << endl;  
		}
	}
	return 0;
}