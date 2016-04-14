#include<bits/stdc++.h>
using namespace std;
#define inf 500

int n,m;
int matching;
int pair_u[220],pair_v[220],dist[220];
struct node
{
	node():eid(0){};
	node(int id):eid(id){};
	int eid;
}N[220];

struct edge
{
	edge(){vt=ne=0;};
	edge(int v,int n):vt(v),ne(n){};
	int vt;
	int ne;
}E[41000];

bool bfs()
{
	int i;
	int u,v;
	queue<int> q;
	for(i=1;i<=n;++i)
	{
		if(pair_u[i]==0){q.push(i);dist[i]=0;}
		else dist[i]=inf;
	}
	dist[0]=inf;
	while(!q.empty())
	{
		u=q.front();
		q.pop();
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
	memset(pair_u,0,sizeof(pair_u));
	memset(pair_v,0,sizeof(pair_v));
	while(bfs()==true)
	{
		for(int i=1;i<=n;++i)
		{
			if(pair_u[i]==0)
			{
				if(dfs(i)==true) ++matching;
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
	int i,j,k;
	int u,v;
	
	scanf("%d%d",&n,&m);
	
	matching=0;cnt=1;
	
	for(i=0;i<m;++i)
	{
		scanf("%d%d",&u,&v);
		E[cnt]=edge(v,N[u].eid);N[u]=cnt++;
		E[cnt]=edge(u,N[v].eid);N[v]=cnt++;
	}
	
	hopcroft_karp();
	printf("%d\n",matching);	
}
