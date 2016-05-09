#include<bits/stdc++.h>
using namespace std;

#define maxn
#defien maxm

int od[maxn],dd[maxn],ans;
struct node
{
	int l,r,n;
}tree[maxm];
int init(int l,int r)
{
	int id=ans++;
	tree[id].n=0;
	if(l!=r)
	{
		tree[id].l=init(l,(l+r)/2);
		tree[id].r=init((l+r)/2+1,r);
	}
	return id;
}
int bt(int pre,int data,int l,int r)
{
	int id=++ans;
	tree[id].n=tree[pre].n+1;
	if(l==r)
	{
		tree[id].l=tree[id].r=0;
		return id; 
	}
	if(data>dd[(l+r)/2])
	{
		tree[id].l=tree[pre].l;
		tree[id].r=bt(tree[pre].r,data,(l+r)/2+1,r);
	}
	else
	{
		tree[id].r=tree[pre].r;
		tree[id].l=bt(tree[pre].l,data,l,(l+r)/2);		
	}
	return id;
}
int sv(int idx,int idy,int k,int l,int r)
{
	if(l==r)
	{
		return dd[l];
	}
	else
	{
		if(k>(tree[tree[idy].l].n-tree[tree[idx].l].n))
		{
			return sv(tree[idx].r,tree[idy].r,k-(tree[tree[idy].l].n-tree[tree[idx].l].n),(l+r)/2+1,r);
		}
		else
		{
			return sv(tree[idx].l,tree[idy].l,k,l,(l+r)/2);
		}
	}
}
int main()
{
	int i;
	int t;
	int n,m,data,size,l,r,k;
	
		memset(od,0,sizeof(od));
		memset(dd,0,sizeof(dd));
		scanf("%d%d",&n,&m);
		for(i=1;i<=n;++i)
		{
			scanf("%d",&data);
			od[i]=dd[i]=data;
		}
		sort(dd+1,dd+n+1);
		size=unique(dd+1,dd+n+1)-dd-1;
		ans=0;
		od[0]=init(1,size);
		for(i=1;i<=n;++i)
		{
			data=od[i];
			od[i]=bt(od[i-1],data,1,size);
		}
		for(i=0;i<m;++i)
		{
			scanf("%d%d%d",&l,&r,&k);
			printf("%d\n",sv(od[l-1],od[r],k,1,size));
		}
	
}
