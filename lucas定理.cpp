#include<bits/stdc++.h>
using namespace std;
#define maxn 1000
typedef long long ll;

ll fac[maxn],rfac[maxn],inv[maxn];

ll fpow(ll b,ll p,ll m)
{ll r=1;for(;p;p>>=1){if(p&1)r=r*b%m;b=b*b%m;} return r;}

void init(int size,ll p)
{
	fac[0]=fac[1]=1;
	for(int i=2;i<=size;++i)fac[i]=fac[i-1]*i%p;
	inv[size]=fpow(fac[size],p-2,p);
	for(int i=size-1;i>=0;--i)inv[i]=inv[i+1]*(i+1)%p;
}

ll c0(ll n,ll m,ll p)
{
	if(n<0||m<0||n<m)return 0;
	ll a=1,b=1;
	for(int i=1;i<=m;++i){a=a*(n-m+i)%p;b=b*i%p;}
	return a*fpow(b,p-2,p)%p;
}

ll c(ll n,ll m,ll p)
{
	if(n<0||m<0||n<m)return 0;
	return fac[n]*inv[m]*inv[n-m]%p;
}

ll lucas(ll n,ll m,ll p)
{
	if(n<0||m<0||n<m)return 0;
	ll ans=1;
	for(;n||m;n/=p,m/=p)ans=ans*c(n%p,m%p,p)%p;
	return ans;
}

int main(){}
