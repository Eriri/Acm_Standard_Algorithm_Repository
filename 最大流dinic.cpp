#include<bits/stdc++.h>
using namespace std;
#define inf 0x7fffffff
#define maxn 
#define maxm 

struct edge
{
    edge(){};
    edge(int v,int n,int c):vt(v),ne(n),cap(c){};
    int vt,ne,cap;
}E[maxm];

int N[maxn],stk[maxm],level[maxn],n,s,t,top,maxflow,cnt;

bool build_level_network()
{
    for (int i=s;i<=t;++i) level[i]=inf;
	level[s]=0;
    queue<int> wfs;
	int u,v,e;
	wfs.push(s);
	while (!wfs.empty())
	{
		u=wfs.front();
		wfs.pop();
		for(e=N[u],v=E[e].vt;e;e=E[e].ne,v=E[e].vt)
		{
			if(level[v]>level[u]+1&&E[e].cap)
			{
				level[v]=level[u]+1;
				if(level[v]<level[t])wfs.push(v);
			}
		}
	}
	return level[t]!=inf;
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
            E[stk[i]^1].cap+=f;
		}
		return f;
	}
	else
	{
		f=0;
		for(e=N[n];e;e=E[e].ne)
		{
			if(level[E[e].vt]==level[n]+1)
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
    cnt=2;
    build_map();//node_num [1...n]
    s=0,t=n+1;
    maxflow=0;
    dinic();
    printf("%d\n",maxflow);
}
