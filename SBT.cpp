#include<bits/stdc++.h>
using namespace std;
#define maxn 100005

struct SBT
{
	SBT(){memset(N,0,sizeof(N));cnt=1;};
	struct node
	{
		node(){};
		node(int n,int s):num(n),size(s){lr[0]=lr[1]=0;};
		int num,size,lr[2];
	}N[maxn];
	int cnt;
	int rotate(int n,int s)//0->right 1->left
	{
		int lr=N[n].lr[s];
		N[n].lr[s]=N[lr].lr[s^1];N[lr].lr[s^1]=n;N[lr].size=N[n].size;
		N[n].size=N[N[n].lr[s^1]].size+N[N[n].lr[s]].size+1;
		return lr;
	}
	int maintain(int n,int s)//true->right;false->left;
	{
		if(N[N[N[n].lr[s]].lr[s]].size>N[N[n].lr[s^1]].size)n=rotate(n,s);
		else if(N[N[N[n].lr[s]].lr[s^1]].size>N[N[n].lr[s^1]].size)
		{N[n].lr[s]=rotate(N[n].lr[s],s^1);n=rotate(n,s);}
		else return n;
		N[n].lr[0]=maintain(N[n].lr[0],1);N[n].lr[1]=maintain(N[n].lr[1],0);
		n=maintain(n,1);n=maintain(n,0);
	}
	int insert(int n,int v)
	{
		if(n==0){N[cnt++]=node(v,1);return cnt-1;}
		else
		{
			++N[n].size;
			N[n].lr[v>=N[n].num]=insert(N[n].lr[v>=N[n].num],v);
			return n=maintain(n,v<N[n].num);
		}
	}
};

int main(){};


