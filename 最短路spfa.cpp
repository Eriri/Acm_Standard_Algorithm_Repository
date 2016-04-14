#include<iostream>
#include<cstring>
#include<string>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<set>
#include<vector>
#include<algorithm>
#include<queue>
#include<stack>
using namespace std;

struct edge
{
	edge(){};
	edge(int v,int n,int c):vt(v),ne(n),co(c){};
	int vt,ne,co;
}E[];

int node[],mindis[];
bool vis[];

struct cmp
{
  	bool operator ()(int x,int y)
  	{
  		return mindis[x]>mindis[y];
  	}
	
};

void spfa(int u)
{
    priority_queue<int,vector<int>,cmp> updt;
	int v,e;
	updt.push(u);
	vis[u]=true;
	while(!updt.empty())
	{
	 	v=updt.top();
	 	updt.pop();
		vis[v]=false;
		e=node[v];
		while(e!=0)
		{
			if(mindis[E[e].vt]>mindis[v]+E[e].co)
			{
				mindis[E[e].vt]=mindis[v]+E[e].co;
				if(vis[E[e].vt]==false)
				{
					updt.push(E[e].vt);
					vis[E[e].vt]=true;
				}
			}
			e=E[e].ne;
		}
	}
}
