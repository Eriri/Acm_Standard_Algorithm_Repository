#include<bits/stdc++.h>
using namespace std;

#define maxn 1000
#define maxm 1000

int top,ts,scc,dfn[maxn],low[maxn],N[maxn];
bool vis[maxn],instk[maxn];
stack<int> stk;

struct edge
{
	edge(){};
	edge(int v,int n):vt(v),ne(n){};
	int vt,ne;
}E[maxm];

void dfs(int u)
{
	stk.push(u);vis[u]=instk[u]=true;dfn[u]=low[u]=ts;
	for(int e=N[u];e;e=E[e].ne)
	{
		if(vis[E[e].vt]==true){if(instk[E[e].vt]==true)low[n]=min(low[n],low[E[e].vt]);}
		else{++ts;dfs(E[e].vt);low[n]=min(low[n],low[E[e].vt]);}
	}
	if(low[n]==dfn[n])
	{
		++scc;
		while(stk.top()!=n){top=stk.top();stk.pop();instk[top]=false;}
		stk.pop();instk[n]=false;
	}
}
void tarjan(int u)
{
	while(!stk.empty())stk.pop();
	ts=1;dfs(u);
}
int main(){}
