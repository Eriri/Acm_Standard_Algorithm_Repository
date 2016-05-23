#include <bits/stdc++.h>
using namespace std;

#define maxn

string pmtn,cotnex;
int n,bit[maxn];


int lowbit(int n){return n&(-n);}

void update(int p,int v)
{
	while(p<=n)
	{
		bit[p]+=v;
		p+=lowbit(p);
	}
}

void init()
{
	memset(bit,0,sizeof(bit));
	n=max(pmtn.length(),cotnex.length());
	for(int i=1;i<=n;++i)update(i,1);
}

int query(int r)
{
	int v=0,p=1;
	while(p<=r)
	{
		while(p+lowbit(p)<=r)p+=lowbit(p);
		v+=bit[p];++p;
	}
	return v;
}
int find(int k)
{
	int p=0;
	while(k>0)
	{
		++p;
		while(bit[p]<k)
		{
			if(p+lowbit(p)<=n&&bit[p+lowbit(p)]<k)p+=lowbit(p);
			else break;
		}
		k-=bit[p];
	}
	return p;
}

void trans_cotnex()
{
	cotnex.clear();
	init();
	for(int i=0;i<n;++i)
	{
		cotnex+=query(pmtn[i]-'0')+'0';
		update(pmtn[i]-'0'+1,-1);
	}
	cout<<cotnex<<endl;
}

void trans_pmtn()
{
	int k;
	pmtn.clear();
	init();
	for(int i=0;i<n;++i)
	{
		k=find(cotnex[i]-'0'+1);
		pmtn+=k-1+'0';
		update(k,-1);
	}
	cout<<pmtn<<endl;
}

int main()
{
	cin>>pmtn;trans_cotnex();
	cin>>cotnex;trans_pmtn();
}
