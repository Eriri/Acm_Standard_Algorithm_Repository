#include<bits/stdc++.h>
using namespace std;
#define maxn 1000
typedef long long ll;
typedef double db;

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

db f(db x){return ;}

db simpson(db a,db b){return (f(a)+4.0*f((a+b)/2)+f(b))*(b-a)/6;}

db asr(db a,db b,db S)
{
	db L=simpson(a,(a+b)/2),R=simpson((a+b)/2,b),dS=fabs(L+R-S)/15;
	if(dS<=eps)return L+R+dS;
	return asr(a,(a+b)/2,L)+asr((a+b)/2,b,R);
}


int main(){}
