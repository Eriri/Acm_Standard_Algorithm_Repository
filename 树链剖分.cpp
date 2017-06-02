#include<bits/stdc++.h>
using namespace std;

#define maxn 10000

vector<int> N[maxn];
int fa[maxn],so[maxn],tp[maxn],bd[maxn],sz[maxn],q[maxn],od[maxn],uod[maxn];
int h,t,id;

void init_tree_link(int root)
{
	memset(sz,0,sizeof(sz));
	memset(so,0,sizeof(so));
	memset(od,0,sizeof(od));
	q[1]=root;h=t=1;fa[root]=root;id=1;
	for(int p=h;p<=t;++p)
	{
		int u=q[p];sz[u]=1;
		for(auto v:N[u])if(v!=fa[u]){fa[v]=u;q[++t]=v;}
	}
	for(int p=t;p>=h;--p)
	{
		int u=q[p],ms=0;bd[u]=u;
		for(auto v:N[u])if(v!=fa[u])
		{
			if(sz[v]>ms){so[u]=v;ms=sz[v];}
			bd[u]=bd[so[u]];sz[u]+=sz[v];
		}
	}
	for(int p=h;p<=t;++p)if(!od[q[p]])
		for(int u=q[p];u;tp[u]=q[p],od[u]=id,uod[id]=u,u=so[u],++id);
}



int main(){};
