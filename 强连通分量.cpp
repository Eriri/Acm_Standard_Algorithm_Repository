#include<bits/stdc++.h>
using namespace std;
#define maxn 10000
#define maxe 10000
int top,ts,scc;
int dfn[maxn],low[maxn];
bool isse[maxn],instk[maxn];
stack<int> stk;
int min(int a,int b){return a>b?b:a;}
int max(int a,int b){return a>b?a:b;}
struct node
{
	node():eid(0){};
	int eid;
}N[maxn];
struct edge
{
	edge(){};
	edge(int v,int n):vt(v),ne(n){};
	int vt,ne;
}E[maxe];

void dfs(int n)
{
	stk.push(n);
	isse[n]=instk[n]=true;
	dfn[n]=low[n]=ts;
	int i=N[n].eid;
	while(i!=0)
	{
		if(isse[E[i].vt]==true)
		{
			if(instk[E[i].vt]==true)
			{
				low[n]=min(low[n],low[E[i].vt]);
			}
		}
		else
		{
			++ts;
			dfs(E[i].vt);
			low[n]=min(low[n],low[E[i].vt]);
		}
		i=E[i].ne;
	}
	if(low[n]==dfn[n])
	{
		++scc;
		while(stk.top()!=n)
		{
			top=stk.top();
			stk.pop();
			instk[top]=false;
		}
		stk.pop();
		instk[n]=false;
	}
}
void tarjan(int n)
{
	while(!stk.empty())stk.pop();
	ts=1;
	dfs(n);
}
int main()
{
	memset(isse,0,sizeof(isse));
	memset(N,0,sizeof(N));
	memset(E,0,sizeof(E));
	memset(instk,0,sizeof(instk));
	memset(dfn,0,sizeof(dfn));
	memset(low,0,sizeof(low));
	
	int n,m;
	int u,v;
	scanf("%d%d",&n,&m);
	for(int i=0;i<m;++i)
	{
		scanf("%d%d",&u,&v);
		E[cnt]=edge(v,N[u].eid);N[u].eid=cnt++;
	}
	for(int i=1;i<=n;++i) if(isse[i]==false)tarjan(i);
	printf("%d\n",scc);
}
