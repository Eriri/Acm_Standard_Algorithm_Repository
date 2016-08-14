#include<bits/stdc++.h>
using namespace std;

#define maxn 

typedef __int64 ll;

ll det(ll mtx[maxn][maxn],int rc,ll mod)
{
	ll ans=1,t;
	for(int i=0;i<rc;++i)
	{
		for(int j=i+1;j<rc;++j)
		{
			while(mtx[j][i])
			{
				t=mtx[i][i]/mtx[j][i];
				for(int k=i;k<rc;++k)mtx[i][k]=(mtx[i][k]-mtx[j][k]*t)%mod;
				for(int k=i;k<rc;++k)swap(mtx[i][k],mtx[j][k]);
				ans=-ans;
			}
		}
		ans=(ans*mtx[i][i])%mod;
	}
	return (ans+mod)%mod;
}










int main(){}
