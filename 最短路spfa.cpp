#include<bits/stdc++.h>
using namespace std;

#define maxn
#define maxm

struct edge
{
	edge(){};
	edge(int v,int n,int c):vt(v),ne(n),co(c){};
	int vt,ne,co;
}E[maxm];

int node[maxn],mindis[maxn];
bool vis[maxn];

struct cmp
{
  	bool operator ()(int x,int y)
  	{
  		return mindis[x]>mindis[y];
  	}
};

void spfa(int u)
{
    priority_queue<int,vector<int>,cmp> updt;
	int v,e;
	updt.push(u);
	vis[u]=true;
	while(!updt.empty())
	{
	 	v=updt.top();
	 	updt.pop();
		vis[v]=false;
		e=node[v];
		while(e!=0)
		{
			if(mindis[E[e].vt]>mindis[v]+E[e].co)
			{
				mindis[E[e].vt]=mindis[v]+E[e].co;
				if(vis[E[e].vt]==false)
				{
					updt.push(E[e].vt);
					vis[E[e].vt]=true;
				}
			}
			e=E[e].ne;
		}
	}
}
