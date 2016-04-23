#include<bits/stdc++.h>
using namespace std;

#define inf 0x7fffffff
#define maxn 
#define maxm

int N[maxn],mindist[maxn];
bool inset[maxn];

struct edge
{
	edge(){};
	edge(int v,int n,int c):vt(v),ne(n),co(c){};
	int vt,ne,co;
}E[maxm];

struct cmp
{bool operator()(const pair<int,int> &a,const pair<int,int> &b)
{return a.second>b.second;}};

int main()
{
	int cnt,n,m,u,v,c,e,s;
	cnt=1;
	scanf("%d%d",&n,&m);
	for(int i=0;i<m;++i)
	{
		scanf("%d%d%d",&u,&v,&c);
		E[cnt]=edge(v,N[u],c);N[u]=cnt++;
	}
	priority_queue<pair<int,int>,vector<pair<int,int>>,cmp> Q;
	scanf("%d%d",&s,&t);
	Q.push(pair<int,int>(s,0));
	while(!Q.empty())
	{
		u=Q.top().first;c=Q.top().second;Q.pop()
		if(inset[u])continue;
		inset[u]=true;mindist[u]=c;
		for(e=N[u];e!=0;e=E[e].ne)
		{
			if(mindist[u]+E[e].co<mindist[E[e].vt])
			{
				Q.push(pair<int,int>(E[e].vt,mindistp[u]+E[e].co));
			}
		}
	}	
}