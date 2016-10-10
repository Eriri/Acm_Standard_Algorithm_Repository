#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod=100000007,inv=50000004;
#define maxn (1<<16)

//xor (x0,x1)->(x0-x1,x0+x1) (x0,x1)<-((x0+x1)/2,(x1-x0)/2))
//and (x0,x1)->(x1,x0+x1)    (x0,x1)<-(x1-x0,x0)
//or  (x0,x1)->(x0,x0+x1)    (x0,x1)<-(x0,x1-x0)

void trans(ll a[],int l,int r)
{
    if(l==r)return;
    int m=(l+r)>>1;ll ai,aj;
    trans(a,l,m);trans(a,m+1,r);
    for(int i=l,j=m+1;i<=m;++i,++j)
    {
		ai=(a[i]-a[j]+mod)%mod;
		aj=(a[i]+a[j]+mod)%mod;
		a[i]=ai;a[j]=aj;
    }
}

void untrans(ll a[],int l,int r)
{
    if(l==r)return;
    int m=(l+r)>>1;ll ai,aj;
    for(int i=l,j=m+1;i<=m;++i,++j)
    {
        ai=(a[i]+a[j]+mod)%mod*inv%mod;
        aj=(a[j]-a[i]+mod)%mod*inv%mod;
        a[i]=ai;a[j]=aj;
    }
    untrans(a,l,m);untrans(a,m+1,r);
}
//or as sample
int main()
{
	ll a[maxn],b[maxn],c[maxn];
	int L=1<<16;
    trans(a,0,L-1);trans(b,0,L-1);
    for(int i=0;i<L;++i)c[i]=a[i]*b[i]%mod;
    untrans(c,0,L-1);
}
