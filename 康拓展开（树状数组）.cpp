#include <bits/stdc++.h>
using namespace std;
#define maxn 10000

string pmtn,cotnex;int n,bit[maxn];

int lowbit(int n){return n&(-n);}
void update(int p,int v){for(;p<=n;p+=lowbit(p))bit[p]+=v;}
int query(int r){int v=0;for(;r;r-=lowbit(r))v+=bit[r];return v;}

void init()
{
	memset(bit,0,sizeof(bit));
	n=max(pmtn.length(),cotnex.length());
	for(int i=1;i<=n;++i)update(i,1);
}

int find(int k)
{
	int p;
	for(p=1;k;k-=bit[p],++p)
		for(;p+lowbit(p)<=n&&bit[p+lowbit(p)]<k;p+=lowbit(p));
	return p;
}

void trans_cotnex()
{
	cotnex.clear();init();
	for(int i=0;i<n;++i)
	{
		cotnex+=query(pmtn[i]-'0')+'0';
		update(pmtn[i]-'0'+1,-1);
	}
	cout<<cotnex<<endl;
}

void trans_pmtn()
{
	pmtn.clear();init();
	for(int i=0;i<n;++i)
	{
		int k=find(cotnex[i]-'0'+1);
		pmtn+=k-1+'0';
		update(k,-1);
	}
	cout<<pmtn<<endl;
}

int main(){}
