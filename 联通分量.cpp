#include<bits/stdc++.h>
using namespace std;
#define maxn 10000

int ts=1,top=-1,dfn[maxn],low[maxn],fa[maxn],stk[maxn];
vector<int> N[maxn];

void dfs(int u)
{
    dfn[u]=low[u]=ts++;stk[++top]=u;
	for(auto v:N[u])
    {
        if(!dfn[v])dfs(v),low[u]=min(low[u],low[v]);
        else if(!fa[v])low[u]=min(low[u],dfn[v]);
    }
	if(dfn[u]==low[u])do{fa[stk[top]]=u;}while(stk[top--]!=u);
}

void dfs(int u,int d,int p)
{
	int sec=0,son;
	dfn[u]=low[u]=d;son=d>1;stk[++top]=u;
	for(auto v:N[u])
	{
		if(!dfn[v])
		{
			dfs(v,d+1,u);
			low[u]=min(low[u],low[v]);
			if(low[v]>dfn[u]);//isbridge[(u,v)]=true;
			if(low[v]>=dfn[u]&&++son==2);//iscut[u]=true;
		}
		else if(v!=p||sec++)low[u]=min(low[u],dfn[v]);
	}
	if(dfn[u]==low[u])do{fa[stk[top]]=u;}while(stk[top--]!=u);
}

int main(){}
