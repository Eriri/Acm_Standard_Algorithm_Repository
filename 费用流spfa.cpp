#include<bits/stdc++.h>
using namespace std;

#define inf (0x3f3f3f3f)
#define maxn 1000 
#define maxm 1000

struct edge
{	
	edge(){};
	edge(int v,int n,int c,int w):vt(v),ne(n),cap(c),wei(w){};
	int vt,ne,cap,wei;
}E[maxm];

int N[maxn],mindis[maxn],pre[maxn],cnt,s,t,mincost;
bool inq[maxn];

void build(int u,int v,int c,int w)
{
	E[cnt]=edge(v,N[u],c,w);N[u]=cnt++;
	E[cnt]=edge(u,N[v],0,-w);N[v]=cnt++;
}

bool spfa()
{
	int u,e;
	queue<int> q;
	memset(mindis,inf,sizeof(mindis));	
	memset(inq,false,sizeof(inq));
	q.push(s);mindis[s]=0;
	while(!q.empty())
	{
		u=q.front();q.pop();inq[u]=false;
		for(e=N[u];e;e=E[e].ne)
		{
			if(E[e].cap&&mindis[E[e].vt]>mindis[u]+E[e].wei)
			{
				mindis[E[e].vt]=mindis[u]+E[e].wei;
				pre[E[e].vt]=e^1;
				if(!inq[E[e].vt])
				{q.push(E[e].vt);inq[E[e].vt]=true;}
			}
		}
	}
	return mindis[t]<inf;
}

void costflow()
{
	int u,f;
	while(spfa())
	{
		for(u=s,f=inf;u!=s;u=E[pre[u]].vt)
			f=min(f,E[pre[u]^1].cap);
		for(u=s;u!=s;u=E[pre[u]].vt)
			{E[pre[u]].cap+=f;E[pre[u]^1].cap-=f;};
		mincost+=mindis[t]*f;
	}
}

int main()
{
	build_map();
	costflow();	
	printf("%d\n",mincost);	
}

