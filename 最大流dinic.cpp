#include<bits/stdc++.h>
using namespace std;
#define inf 0x7fffffff
#define maxn 
#define maxm 

struct node
{
    node():eid(0){};
    int eid,level;
}N[maxn];

struct edge
{
    edge(){};
    edge(int v,int n,int c,int o):vt(v),ne(n),cap(c),oed(o){};
    int vt,ne,cap,oed;
}E[maxm];

int n,s,t;
int stk[maxm],top;
int maxflow;

bool build_level_network()
{
    for (int i=s;i<=t;++i) N[i].level=inf;
	N[s].level=0;
    queue<int> wfs;
	int u,v,e;
	wfs.push(s);
	while (!wfs.empty())
	{
		u=wfs.front();
		wfs.pop();
		for(e=N[u].eid,v=E[e].vt;e!=0;e=E[e].ne,v=E[e].vt)
		{
			if(N[v].level>N[u].level+1&&E[e].cap>0)
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
		for(int i=0;i<top;++i)f=min(f,E[stk[i]].cap);
		for(int i=0;i<top;++i)
		{
			E[stk[i]].cap-=f;
            E[E[stk[i]].oed].cap+=f;
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
    build_map();//node_num [1...n]
    s=0,t=n+1;
    maxflow=0;
    dinic();
    printf("%d\n",maxflow);
}
