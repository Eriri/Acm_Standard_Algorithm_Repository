#include<bits/stdc++.h>
using namespace std;

#define maxn 1000
#define maxm 1000

struct node
{
	int l,r,n;
}tree[maxm];

int cnt=1;

int init(int l,int r)
{
	int id=cnt++;
	if(l!=r)
	{
		tree[id].l=init(l,(l+r)/2);
		tree[id].r=init((l+r)/2+1,r);
	}
	return id;
}

int insert(int now,int l,int r,int p,int v)
{
	int id=cnt++;
	tree[id].n=tree[now].n+v;
	if(l==r)return id;
	tree[id].l=tree[now].l;tree[id].r=tree[now].r;
	if(p>(l+r)/2)tree[id].r=insert(tree[now].r,(l+r)/2+1,r,p,v);
	else tree[id].l=insert(tree[now].l,l,(l+r)/2,p,v);		
	return id;
}

int main(){}
