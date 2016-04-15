#include<bits/stdc++.h>
using namespace std;
#define inf 500
#define maxn 1000
	
int matching;
int pair_u[maxn],pair_v[maxn],dist[maxn];
set<int> U,V;
set<int>::iterator itr;

struct node
{
	node():eid(0){};
	int eid;
}N[maxn];

struct edge
{
	edge(){};
	edge(int v,int n):vt(v),ne(n){};
	int vt,ne;
}E[41000];

bool bfs()
{
	int u,v;
	queue<int> q;
	for(itr=U.begin();itr!=U.end();++i)
	{
		if(pair_u[*itr]==0){q.push(*itr);dist[*itr]=0;}
		else dist[*itr]=inf;
	}
	dist[0]=inf;
	while(!q.empty())
	{
		u=q.front();q.pop();
		if(dist[u]<dist[0])
		{
			for(i=N[u].eid;i!=0;i=E[i].ne)
			{
				v=E[i].vt;
				if(dist[pair_v[v]]==inf)
				{
					dist[pair_v[v]]=dist[u]+1;
					q.push(pair_v[v]);
				}
			}
		}
	}
	return dist[0]!=inf;
}

bool dfs(int u)
{
	int i,v;
	if(u!=0)
	{
		for(i=N[u].eid;i!=0;i=E[i].ne)
		{
			v=E[i].vt;
			if(dist[pair_v[v]]==dist[u]+1)
			{
				if(dfs(pair_v[v])==true)
				{
					pair_v[v]=u;
					pair_u[u]=v;
					return true;
				}
			}
		}
		dist[u]=inf;
		return false;
	}
	return true;
}

void hopcroft_karp()
{
	while(bfs()==true)
	{
		for(itr=U.begin();itr!=U.end();++i)
		{
			if(pair_u[*itr]==0)
			{
				if(dfs(*itr)==true) ++matching;
			}
		}
	}
}

int main()
{
	memset(N,0,sizeof(N));
	memset(E,0,sizeof(E));
	memset(pair_u,0,sizeof(pair_u));
	memset(pair_v,0,sizeof(pair_v));
	memset(dist,0,sizeof(dist));
	
	int n,m,cnt;
	int u,v;
	scanf("%d%d",&n,&m);
	matching=0;cnt=1;
	for(int i=0;i<m;++i)
	{
		scanf("%d%d",&u,&v);
		U.insert(u);V.insert(v);
		E[cnt]=edge(v,N[u].eid);N[u].eid=cnt++;
		E[cnt]=edge(u,N[v].eid);N[v].eid=cnt++;
	}
	hopcroft_karp();
	printf("%d\n",matching);	
}
