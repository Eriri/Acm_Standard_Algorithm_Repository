#include<bits/stdc++.h>
using namespace std;
#define maxn 10000

int pri[maxn],euler_val[maxn],ispri[maxn];

int euler_func(int n)
{
    int cnt=0;
    memset(ispri,0,sizeof(ispri));
    euler_val[0]=euler_val[1]=1;
    for(int i=2;i<=n;++i)
    {
        if(!ispri[i]){pri[cnt++]=i;euler_val[i]=i-1;}
        for(int j=0;j<cnt&&pri[j]*i<=n;++j)
        {
            ispri[pri[j]*i]=1;
            if(i%pri[j]==0)euler_val[pri[j]*i]=euler_val[i]*pri[j];
            else euler_val[pri[j]*i]=euler_val[i]*(pri[j]-1);
        }
    }
    return euler_val[n]; 
}

int main(){};
