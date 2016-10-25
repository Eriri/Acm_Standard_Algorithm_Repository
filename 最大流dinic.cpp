#include<bits/stdc++.h>
using namespace std;
#define inf 0x3f3f3f3f
#define maxn 10000
#define maxm 10000

struct dinic
{
	dinic(){};
	struct edge
	{
		edge(){};
		edge(int v,int n,int c):vt(v),ne(n),cap(c){};
		int vt,ne,cap;
	}E[maxm];
	int N[maxn],stk[maxm],level[maxn],n,s,t,top,maxflow,cnt;
	void init(){memset(N,0,sizeof(N));cnt=2;maxflow=0;}
	void build(int u,int v,int c)
	{E[cnt]=edge(v,N[u],c);N[u]=cnt++;E[cnt]=edge(u,N[v],0);N[v]=cnt++;}
	bool build_level_network()
	{
		memset(level,inf,sizeof(level));
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
		if(u==t)
		{
			int f=inf;
			for(int i=0;i<top;++i)f=min(f,E[stk[i]].cap);
			for(int i=0;i<top;++i){E[stk[i]].cap-=f;E[stk[i]^1].cap+=f;}
			return f;
		}
		else
		{
			int f=0;
			for(int e=N[u];e;e=E[e].ne)if(level[E[e].vt]==level[u]+1&&E[e].cap)
				{stk[top++]=e;f+=update_flow(E[e].vt);--top;}
			return f;
		}
	}
	int run()
	{
		while(build_level_network()){top=0;maxflow+=update_flow(s);}
		return maxflow;
	}
};


int main(){}
