#include<bits/stdc++.h>
using namespace std;

#define PI (acos(-1.0))
typedef complex<double> cpd;

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
}

void multiply(cpd A[],cpd B[],cpd C[],int len)
{
	fft(A,len,1);fft(B,len,1);
	for(int i=0;i<len;++i)C[i]=A[i]*B[i];
	fft(C,len,-1);
}

int main(){};
