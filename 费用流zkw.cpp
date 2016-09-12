#include<bits/stdc++.h>

using namespace std;

#define maxn 1000
#define maxm 1000
#define inf (0x3f3f3f3f)

template<class C,class W>
struct zkw
{
	zkw(){cnt=2;memset(N,0,sizeof(N));};
	zkw(int _s,int _t):s(_s),t(_t){cnt=2;memset(N,0,sizeof(N));};
	struct edge
	{
		edge(){};
		edge(int v,int n,C c,W w):vt(v),ne(n),cap(c),wei(w){};
		int vt,ne;C cap;W wei;
	}E[maxm];
	int N[maxn],s,t,cnt;bool vis[maxn];
	C maxflow;W mincost,mindis[maxn];
	void build(int u,int v,C c,W w)
	{E[cnt]=edge(v,N[u],c,w);N[u]=cnt++;
	E[cnt]=edge(u,N[v],0,-w);N[v]=cnt++;}
	bool modify()
	{
		C add=inf;
		for(int u=s;u<=t;++u)if(vis[u])
			for(int e=N[u];e;e=E[e].ne)if(!vis[E[e].vt]&&E[e].cap)
				add=min(add,mindis[E[e].vt]+E[e].wei-mindis[u]);
		if(add==inf)return false;
		for(int u=s;u<=t;++u)if(vis[u])mindis[u]+=add;
		return true;
	}
	C dfs(int u,C f)
	{
		if(u==t){maxflow+=f;mincost+=mindis[s]*f;return f;}
		C nflow,tflow;nflow=0;vis[u]=true;
		for(int e=N[u];e;e=E[e].ne)
		if(!vis[E[e].vt]&&E[e].cap&&mindis[E[e].vt]+E[e].wei==mindis[u])
		{
			tflow=dfs(E[e].vt,min(E[e].cap,f-nflow));
			E[e].cap-=tflow;E[e^1].cap+=tflow;nflow+=tflow;
			if(nflow==f)break;
		}
		return nflow;
	}
	W run()
	{
		maxflow=mincost=0;mst(mindis,0);
		do do memset(vis,0,sizeof(vis));while(dfs(s,inf));while(modify());
		return mincost;
	}
};

int main(){}
