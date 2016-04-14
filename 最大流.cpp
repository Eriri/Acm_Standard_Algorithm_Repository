#include <iostream>
#include <queue>
#include <stdio.h>
using namespace std;
#define inf 0x7fffffff
#define maxn 1000
#define maxm 1000

struct node
{
    node():eid(0),level(0){};
    int eid,level;
}N[maxn];

struct edge
{
    edge(){};
    edge(int v,int n,int c,int o):vt(v),ne(n),cap(c),oed(o){};
    int vt,ne,cap,oed;
}E[maxm];

int n,m;
int s,t;
int stk[maxn],top;
int maxflow;

bool build_level_network()
{
    N[s].level=0;
    for (int i=0;i<n;++i) N[i].level=inf;
	queue<int> wfs;
	int u,v,e;
	wfs.push(s);
	while (!wfs.empty())
	{
		u=wfs.front();
		wfs.pop();
		for(e=N[u].eid;e!=0;e=E[e].ne)
		{
			v=E[e].vt;
			if(N[v].level>N[u].level+1)
			{
				N[v].level=N[u].level+1;
				if(N[v].level<N[t].level)wfs.push(v);
			}
		}
	}
	return N[t].level!=inf;
}

int update_flow(int n)
{
    int e,v,f;
	if(n==t)
	{
		f=inf;
		for(int i=0;i<top;++i)f=min(f,E[i].cap);
		for(int i=0;i<top;++i)
		{
			E[i].cap-=f;
			E[E[i].oed].cap+=f;
		}
		return f;
	}
	else
	{
		f=0;
		for(e=N[n].eid;e!=0;e=E[e].ne)
		{
			if(N[E[e].vt].level==N[n].level+1)
			{
				stk[top++]=e;
				f+=update_flow(E[e].vt);
				--top;
			}
			else continue;
		}

	}
	return f;
}

void dinic()
{
    while(build_level_network())
    {
		top=0;
        maxflow+=update_flow(s);
    }
}

int main()
{
    int cnt;
    int u,v,c;
    cnt=1;
    scanf("%d%d",&n,&m);
    for(int i=0;i<m;++i)
    {
        scanf("%d%d%d",&u,&v,&c);
        E[cnt]=edge(v,N[u].eid,c,cnt+1);N[u].eid=cnt++;
        E[cnt]=edge(u,N[v].eid,0,cnt-1);N[v].eid=cnt++;
    }
    s=1,t=n;
    maxflow=0;
    dinic();
    printf("%d\n",maxflow);
}