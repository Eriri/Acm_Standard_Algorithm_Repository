#include<bits/stdc++.h>
using namespace std;
#define maxn 10000

int S;
struct kdtree
{
	kdtree(){};
	int root,k;
	struct node
	{
		node(){};
		int ord[6],min[6],max[6],lr[2];
		bool operator<(const node& n)const
		{return ord[S]<n.ord[S];}
	}N[maxn];
	void up(int par,int son)
	{
		for(int i=0;i<k;++i)
		{
			N[par].min[i]=min(N[par].min[i],N[son].min[i]);
			N[par].max[i]=max(N[par].max[i],N[son].max[i]);
		}
	}
	int build(int l,int r,int s)//[1..n]
	{
		int m=(l+r)>>1;
		S=s;nth_element(N+l,N+m,N+r+1);
		if(l!=m){N[m].lr[0]=build(l,m-1,(s+1)%k);up(m,N[m].lr[0]);}
		if(m!=r){N[m].lr[1]=build(m+1,r,(s+1)%k);up(m,N[m].lr[1]);}
		return m;
	}
	void insert(int p,int id,int s)
	{
		int n=(N[id].ord[s]<=N[p].ord[s]);
		if(N[id].lr[n])insert(p,N[id].lr[n],(s+1)%k);
		else N[id].lr[n]=p;
		up(id,N[id].lr[n]);
	}
};
int main(){};
