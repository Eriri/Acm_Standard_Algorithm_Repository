#include<bits/stdc++.h>
using namespace std;

#define inf (0x3f3f3f3f)
#define maxn 1000 
#define maxm 1000

template<class C,class W>
struct mcmf
{
	mcmf(){memset(N,0,sizeof(N));cnt=2;maxflow=mincost=0;};
	mcmf(int _s,int _t):s(_s),t(_t){memset(N,0,sizeof(N));cnt=2;maxflow=mincost=0;};
	int N[maxn],pre[maxn],cnt,s,t;W mindis[maxn],mincost;C maxflow;bool inq[maxn];
	struct edge
	{	
		edge(){};
		edge(int v,int n,C c,W w):vt(v),ne(n),cap(c),wei(w){};
		int vt,ne;C cap;W wei;
	}E[maxm];
	void build(int u,int v,C c,W w)
	{E[cnt]=edge(v,N[u],c,w);N[u]=cnt++;E[cnt]=edge(u,N[v],0,-w);N[v]=cnt++;}
	bool spfa()
	{
		queue<int> q;
		memset(mindis,inf,sizeof(mindis));memset(inq,false,sizeof(inq));
		q.push(s);mindis[s]=0;
		while(!q.empty())
		{
			int u=q.front();q.pop();inq[u]=false;
			for(int e=N[u];e;e=E[e].ne)
			{
				if(E[e].cap&&mindis[E[e].vt]>mindis[u]+E[e].wei)
				{
					mindis[E[e].vt]=mindis[u]+E[e].wei;pre[E[e].vt]=e^1;
					if(!inq[E[e].vt]){q.push(E[e].vt);inq[E[e].vt]=true;}
				}
			}
		}
		return mindis[t]<inf;
	}
	W costflow()
	{
		int u;C f;
		while(spfa())
		{
			for(u=t,f=inf;u!=s;u=E[pre[u]].vt)
				f=min(f,E[pre[u]^1].cap);
			for(u=t;u!=s;u=E[pre[u]].vt)
				{E[pre[u]].cap+=f;E[pre[u]^1].cap-=f;};
			mincost+=mindis[t]*f;maxflow+=f;
		}
		return mincost;
	}
};
int main(){}
