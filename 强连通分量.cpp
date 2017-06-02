#include<bits/stdc++.h>
using namespace std;

#define maxn 1000
#define maxm 1000

int top,ts,scc,dfn[maxn],low[maxn];
bool vis[maxn],ins[maxn];
stack<int> stk;
vector<int> N[maxn];

void dfs(int u)
{
	stk.push(u);vis[u]=ins[u]=true;dfn[u]=low[u]=ts;
	for(auto v:N[u])
	{
		if(vis[v]){if(ins[v])low[u]=min(low[u],low[v]);}
		else {++ts;dfs(v);low[u]=min(low[u],low[v]);}
	}
	if(low[u]==dfn[u])
	{
		++scc;
		do{
			top=stk.top();stk.pop();
			ins[top]=false;
		}while(top!=u);
	}
}

void tarjan(int u)
{
	while(!stk.empty())stk.pop();
	ts=1;dfs(u);
}

int main(){}
