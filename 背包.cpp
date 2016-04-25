#include<bits/stdc++.h>
using namespace std;

#define maxn 

int n,v;
int f[maxn],value[maxn],weight[maxn],amount[maxn];

int pack_01(int n)//each amount equal one
{
	int pre[maxn];//path
	memset(f,0,sizeof(f));
	for(int i=1;i<=n;++i)
	{
		for(int j=v;j>=weight[i];--j)
		{
			f[j]=max(f[j],f[j-weight[i]]+value[i]);
		}
	}
	return f[v];
}

int pack_full(int n)//each amount is infinite
{
	memset(f,0,sizeof(f));
	for(int i=1;i<=n;++i)
	{
		for(int j=weight[i];j<=v;++j)
		{
			f[j]=max(f[j],f[j-weight[i]]+value[i]);	
		}
	}
	return f[v];
}

int pack_multi(int n)//each amount is given
{
	memset(f,0,sizeof(f));
	for(int i=1;i<=n;++i)
	{
		if(weight[i]*amount[i]>=v)
		{
			for(int j=weight[i];j<=v;++j)
			{
				f[j]=max(f[j],f[j-weight[i]+value[i]);
			}
		}
		else
		{
			int k=1;
			while(k<amount[i])
			{
				for(int j=v;j>=weight[i]*k;--j)
				{
					f[j]=max(f[j],f[j-weight[i]*k]+value[i]*k);
				}
				amount[i]-=k;
				k=k<<1;
			}
			for(int j=v;j>=weight[i]*amount[i];--j)
			{
				f[j]=max(f[j],f[j-weight[i]*amount[i]]+value[i]*amount[i]);
			}
		}
	}
	return f[v];
}