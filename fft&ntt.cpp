#include<bits/stdc++.h>
using namespace std;
#define PI (acos(-1.0))
typedef complex<double> cpd;
typedef long long ll;

void fft(cpd C[],int len,int s)
{
	int i,j,k,h;cpd wn,w,c,c2;
	for(i=j=0;i<len-1;++i,j|=k)
	{
		if(i<j)swap(C[i],C[j]);
		for(k=len>>1;j>=k;j-=k,k>>=1);
	}
	for(h=2;h<=len;h<<=1)
	{
		wn=cpd(cos(s*2*PI/h),sin(s*2*PI/h));
		for(i=0;i<len;i+=h)
		{
			for(j=i,w=cpd(1,0);j<i+(h>>1);++j,w=w*wn)
			{
				c=C[j];c2=C[j+(h>>1)];
				C[j]=c+w*c2;C[j+(h>>1)]=c-w*c2;
			}
		}
	}
	if(s==-1)for(i=0;i<len;++i)C[i]=C[i]/(double)len;
}

ll P=(17LL<<27)+1,G=3;//P=(15LL<<27)+1,G=31;
ll fpow(ll b,ll p,ll m){ll r=1;for(;p;(p>>=1),b=b*b%m)if(p&1)r=r*b%m;return r;}

void ntt(ll C[],int len,int s)
{
    int i,j,k,h;
    for(i=j=0;i<len-1;++i,j|=k)
    {
        if(i<j)swap(C[i],C[j]);
        for(k=len>>1;j>=k;j-=k,k>>=1);
    }
    ll wn,w,c,inv;
    for(h=2;h<=len;h<<=1)
    {
        wn=fpow(G,(P-1)/h,P);
        if(s==-1)wn=fpow(wn,P-2,P);
        for(i=0;i<len;i+=h)
        {
            for(j=i,w=1;j<i+(h>>1);++j,w=wn*w%P)
            {
                c=w*C[j+(h>>1)]%P;
                C[j+(h>>1)]=(C[j]-c+P)%P;
            	C[j]=(C[j]+c)%P;
			}
        }
    }
    if(s==-1)for(i=0,inv=fpow(len,P-2,P);i<len;++i)C[i]=C[i]*inv%P;
}

void multiply(cpd A[],cpd B[],cpd C[],int len)
{
	fft(A,len,1);fft(B,len,1);
	for(int i=0;i<len;++i)C[i]=A[i]*B[i];
	fft(C,len,-1);
}

int main(){};
