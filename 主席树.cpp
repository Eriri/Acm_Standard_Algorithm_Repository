#include<bits/stdc++.h>
using namespace std;

#define maxn 1000
#define maxm 1000

struct node
{
	int l,r,n;
}T[maxm];

int cnt=1;

int init(int l,int r)
{
	int id=cnt++;
	if(l!=r)
	{
		T[id].l=init(l,(l+r)/2);
		T[id].r=init((l+r)/2+1,r);
	}
	return id;
}

int insert(int now,int l,int r,int p,int v)
{
	int id=cnt++;
	T[id].n=T[now].n+v;
	if(l==r)return id;
	T[id].l=T[now].l;T[id].r=T[now].r;
	if(p>(l+r)/2)T[id].r=insert(T[now].r,(l+r)/2+1,r,p,v);
	else T[id].l=insert(T[now].l,l,(l+r)/2,p,v);		
	return id;
}

int findkth(int ln,int rn,int l,int r,int k)
{
	if(l==r)return l;
	else if(k>T[T[rn].l].n-T[T[ln].l].n)return find(T[ln].r,T[rn].r,(l+r)/2+1,r,k-(T[T[rn].l].n-T[T[ln].l].n));
	else return find(T[ln].l,T[rn].r,l,(l+r)/2,k);
}

int main(){}
