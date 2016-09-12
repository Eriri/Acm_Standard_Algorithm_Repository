#include<bits/stdc++.h>
using namespace std;

#define maxn 1000

bool ispri[maxn];
int pri[maxn],pnum;

void sieve(int n)
{
	memset(ispri,0,sizeof(ispri));
	memset(pri,0,sizeof(pri));
	pnum=0;ispri[0]=ispri[1]=true;
	for(int i=2;i<n;++i)
	{
		if(!ispri[i])pri[pnum++]=i;
		for(int j=0;j<pnum&&i*pri[j]<n;++j)
			{ispri[i*pri[j]]=true;if(i%pri[j]==0)break;}
	}
}

int main(){}
