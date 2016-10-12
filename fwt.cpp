#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod=100000007,inv=50000004;
#define maxn (1<<16)

//transition rule 
//xor (x0,x1)->(x0-x1,x0+x1) (x0,x1)<-((x0+x1)/2,(x1-x0)/2))
//and (x0,x1)->(x1,x0+x1)    (x0,x1)<-(x1-x0,x0)
//or  (x0,x1)->(x0,x0+x1)    (x0,x1)<-(x0,x1-x0)

ll ts(ll i,ll j,int s,int p)
{
	ll r;
	if((s+p)&1)r=(i+j+mod)%mod;
	else r=(i-j+mod)%mod;
	if(s==1)r=r*inv%mod;
	return r;
}

void trans(ll a[],int l,int r,int s)
{
    if(l==r)return;
    int m=(l+r)>>1;ll ai,aj;
    if(s==0)trans(a,l,m,s);trans(a,m+1,r,s);
    for(int i=l,j=m+1;i<=m;++i,++j)
    {
    	ai=ts(a[i],a[j],s,0);
    	aj=ts(a[i],a[j],s,1);
		a[i]=ai;a[j]=aj;
    }
    if(s==1)trans(a,l,m,s);trans(a,m+1,r,s);
}

//xor as sample
int main()
{
	ll a[maxn],b[maxn],c[maxn];
	int L=1<<16;
    trans(a,0,L-1,0);trans(b,0,L-1,0);
    for(int i=0;i<L;++i)c[i]=a[i]*b[i]%mod;
    untrans(c,0,L-1,1);
}
