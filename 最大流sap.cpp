#include<bits/stdc++.h>
using namespace std;

#define maxn 
#define maxm 
#define inf 

struct edge
{
	edge(){};
	edge(int v,int n,int c):vt(v),ne(n),cap(c){};
	int vt,ne,cap;
}E[maxm];

int N[maxn],now[maxn],dpth[maxn],vtn[maxn];
int cnt,maxflow,tflow,s,t,d;
bool found;

void build(int u,int v,int c)
{
	E[cnt]=edge(v,N[u],c);now[u]=N[u]=cnt++;
	E[cnt]=edge(u,N[v],0);now[v]=N[v]=cnt++;
}

void init_level_network()
{
	int u,v,e;
	queue<int> q;
	memset(dpth,0,sizeof(dpth));
	memset(vtn,0,sizeof(vtn));
	vtn[0]=1;
	q.push(t);
	while(!q.empty())
	{
		u=q.front();q.pop();
		for(e=N[u];e!=0;e=E[e].ne)
		{
			v=E[e].vt;
			if(v!=t&&dpth[v]==0)
			{
				dpth[v]=dpth[u]+1;
				++vtn[dpth[v]];
				q.push(v);
			}
		}
	}
}

void sap(int u)
{
	if(u==t)
	{
		found=true;
		maxflow+=tflow;
		return;
	}
	int v,e,ct;
	for(e=now[u],ct=tflow;e!=0;e=E[e].ne)
	{
		v=E[e].vt;
		if(E[e].cap>0&&dpth[v]+1==dpth[u])
		{
			now[u]=e;
			tflow=min(tflow,E[e].cap);
			sap(v);
			if(dpth[s]==d)return;
			if(found)break;
			tflow=ct;
		}
	}
	if(found)
	{
		E[e].cap-=tflow;
		E[e^1].cap+=tflow;
	}
	else
	{
		--vtn[dpth[u]];
		if(vtn[dpth[u]]==0)
		{
			dpth[s]=d;
			return;
		}
		now[u]=N[u];
		v=d-1;
		for(e=N[u];e!=0;e=E[e].ne)
		{
			if(E[e].cap>0&&dpth[E[e].vt]<v)
			{
				v=dpth[E[e].vt];
				now[u]=e;
			}
		}
		dpth[u]=v+1;
		++vtn[dpth[u]];
	}
}

int main()
{
	int n,m;
	build_network();//1...n node and m edge
	s=0,t=n+1;d=n+2;
	maxflow=0;
	init_level_network();
	while(dpth[s]<d)
	{
		tflow=inf;
		found=false;
		sap(s);
	}
	printf("%d\n",maxflow);
}


