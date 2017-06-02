#include<bits/stdc++.h>
using namespace std;

#define maxn 1000

bool vis[maxn],ins[maxn],ok=true;
int pa[maxn],dfn[maxn],low[maxn],col[maxn],deg[maxn],ts;
vector<int> N[maxn],M[maxn];
queue<int> q;stack<int> stk;

int fa(int n){return n==pa[n]?n:pa[n]=fa(pa[n]);}

void tarjan(int u)
{
	stk.push(u);vis[u]=ins[u]=true;dfn[u]=low[u]=ts;
	for(auto v:N[u])
	{
		if(vis[v]){if(ins[v]){low[u]=min(low[u],low[v]);}}
		else {++ts;tarjan(v);low[u]=min(low[u],low[v]);}
	}
	if(low[u]==dfn[u])
	{
		do{
			ins[stk.top()]=false;
			pa[stk.top()]=u;
			stk.pop();
		}while(pa[u]==-1);
	}
}

void two_sat(int n)//red 1...n blue n+1...n+n
{
	for(int i=1;i<=2*n;++i)if(pa[i]==-1){ts==1;tarjan(i);}
	for(int i=1;i<=n;++i)if(fa(i)==fa(i+n))ok=false;
	if(ok)
	{
		for(int u=1;u<=2*n;++u)for(auto v:N[u])if(fa(u)!=fa(v))
		{
			M[fa(v)].push_back(u);++deg[v];
		}
		for(int u=1;u<=n;++u)if(fa(u)==u&&deg[u]==0&&!col[u])
		{
			col[u]='r';q.push(fa(u+n));
			while(!q.empty())
			{
				int v=q.front();q.pop();col[v]='b';
				for(auto t:M[v])if(!col[t])q.push(t);
			}
		}
	}
}

int main(){}
