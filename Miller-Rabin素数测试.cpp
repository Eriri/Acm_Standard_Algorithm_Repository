#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

ll base[13]={2,3,5,7,11,13,17,19,23,29,31,37,41};//upto 3*10^24

ll multiply_mod(ll a,ll b,ll c)
{
    ll ans=0;
    for(;b;b>>=1,a=(a+a)%c)
		if(b&1)ans=(ans+a)%c;
    return ans;
}

ll power_mod(ll b,ll p,ll m)
{
    ll ans=1;
    for(;p;p>>=1,b=multiply_mod(b,b,m))
		if(p&1)ans=multiply_mod(ans,b,m);
    return ans;
}

bool miller_rabin(ll n)
{
    if(n==1||n%2==0) return false;
    int t;
    ll m,u,p;
    for(t=0,m=n-1;m%2==0;++t,m>>=1);//n-1 -> m*2^t
    for(int i=0;i<13&&base[i]<n;++i)//test
    {
        u=power_mod(base[i],m,n);//(base[i]^m)%n solution
        for(int j=0;j<t;++j)
        {
            p=u;u=power_mod(u,2,n);//only solution n-1
            if(u==1&&p!=1&&p!=n-1)return false;//judge
        }
        if(u!=1) return false;
    }
    return true;
}

int main()
{
	ll n;
	cin>>n;
	printf("%d\n",miller_rabin(n)==true);
}


