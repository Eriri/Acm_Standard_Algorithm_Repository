#include<bits/stdc++.h>
using namespace std;
#define maxn 10000
#define maxe 10000
int top,ts;
int dfn[maxn],low[maxn];
bool isse[maxn],instk[maxn];
stack<int> stk;
int min(int a,int b){return a>b?b:a;}
int max(int a,int b){return a>b?a:b;}
struct node
{
	node():eg(0){};
	int eg;
}N[maxn];
struct edge
{
	edge(){};
	edge(int v,int n):vt(v),ne(n){};
	int vt;
	int ne;
}E[maxe];
struct ee
{
	ee(){};
	ee(int a,int b):u(a),v(b){};
	int u,v;
	bool operator<(const ee &p)const
	{
		if(u==p.u)
		{
			return v<p.v;
		}
		else
		{
			return u<p.u;
		}
	}
};
set<ee> exist;
void dfs(int n)
{
	stk.push(n);
	isse[n]=true;instk[n]=true;
	dfn[n]=low[n]=ts;
	int i=N[n].eg;
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
			parent[top]=n;
		}
		stk.pop();
		instk[n]=false;
	}
}
void tarjan(int n)
{
	while(!stk.empty()){stk.pop();}
	ts=1;
	dfs(n);
}
int main()
{
	int i,j,k;
	int n,m;
	int u,v;
	memset(isse,0,sizeof(isse));
	memset(N,0,sizeof(N));
	memset(E,0,sizeof(E));
	memset(instk,0,sizeof(instk));
	memset(dfn,0,sizeof(dfn));
	memset(low,0,sizeof(low));
	scanf("%d%d",&n,&m);
	for(i=0,j=1;i<m;++i)
	{
		scanf("%d%d",&u,&v);
		E[j]=edge(v,N[u].eg);
		N[u].eg=j;
		++j;
	}
	for(i=1;i<=n;++i)
	{
		if(isse[i]==false)
		{
			tarjan(i);
		}
	}
}
