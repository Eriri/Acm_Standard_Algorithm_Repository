#include<bits/stdc++.h>
using namespace std;

long long base[13]={2,3,5,7,11,13,17,19,23,29,31,37,41};//upto 3*10^24

long long multiply_mod(long long a,long long b,long long c)
{
    long long ans=0;
    while(b)
    {
        if(b&1) ans=(ans+a)%c;
        a=(a+a)%c;
        b>>=1;
    }
    return ans;
}

long long power_mod(long long b,long long p,long long m)
{
    long long ans=1;
    while(p)
    {
        if(p&1) ans=multiply_mod(ans,b,m);
        b=multiply_mod(b,b,m);
        p>>=1;
    }
    return ans;
}

bool miller_rabin(long long n)
{
    if(n==1||n%2==0) return false;
    int t;
    long long m,u,p;
    for(t=0,m=n-1;m%2==0;++t,m>>=1);//n-1 -> m*2^t
    for(int i=0;i<13&&base[i]<n;++i)//test
    {
        u=power_mod(base[i],m,n);//(base[i]^m)%n solution
        for(int j=0;j<t;++j)
        {
            p=u;
            u=power_mod(u,2,n);//only solution n-1
            if(u==1&&p!=1&&p!=n-1)return false;//judge
        }
        if(u!=1) return false;
    }
    return true;
}

int main()
{
	long long n;
	scanf("%lld",&n);
	if(miller_rabin(n)) printf("yes\n");
	else printf("no\n");
}


