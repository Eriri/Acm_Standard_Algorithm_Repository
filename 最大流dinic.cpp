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

int N[maxn],stk[maxm],level[maxn],n,s,t,top,maxflow,cnt=2;

bool build_level_network()
{
    	for (int i=s;i<=t;++i) level[i]=inf;
    	queue<int> wfs;
	wfs.push(s);level[s]=0;
	while (!wfs.empty())
	{
		int u=wfs.front();wfs.pop();
		for(int e=N[u];e;e=E[e].ne)
		{
			if(level[E[e].vt]>level[u]+1&&E[e].cap)
				{level[E[e].vt]=level[u]+1;if(level[E[e].vt]<level[t])wfs.push(E[e].vt);}
		}
	}
	return level[t]!=inf;
}

int update_flow(int u)
{
	int f;
	if(u==t)
	{
		f=inf;
		for(int i=0;i<top;++i)f=min(f,E[stk[i]].cap);
		for(int i=0;i<top;++i){E[stk[i]].cap-=f;E[stk[i]^1].cap+=f;}
		return f;
	}
	else
	{
		f=0;
		for(int e=N[u];e;e=E[e].ne)
		{
			if(level[E[e].vt]==level[u]+1){stk[top++]=e;f+=update_flow(E[e].vt);--top;}
			else continue;
		}

	}
	return f;
}

void dinic(){while(build_level_network()){top=0;maxflow+=update_flow(s);}}

int main(){}
