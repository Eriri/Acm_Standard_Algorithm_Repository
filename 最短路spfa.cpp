#include<bits/stdc++.h>
using namespace std;

#define maxn 1000
#define maxm 1000
#define inf (0x3f3f3f3f)

struct edge
{
	edge(){};
	edge(int v,int n,int c):vt(v),ne(n),co(c){};
	int vt,ne,co;
}E[maxm];

int N[maxn],mindis[maxn];
bool vis[maxn];

struct cmp{bool operator ()(int x,int y){return mindis[x]>mindis[y];}};

void spfa(int u)
{
	priority_queue<int,vector<int>,cmp> updt;
	updt.push(u);vis[u]=true;memset(mindis,inf);mindis[u]=0;
	while(!updt.empty())
	{
	 	u=updt.top();updt.pop();vis[u]=false;
		for(int e=N[v];e;e=E[e].ne)if(mindis[E[e].vt]>mindis[u]+E[e].co)
		{
			mindis[E[e].vt]=mindis[u]+E[e].co;
			if(vis[E[e].vt]==false){updt.push(E[e].vt);vis[E[e].vt]=true;}
		}
	}
}

int main(){}
