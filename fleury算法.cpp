#include<bits/stdc++.h>
using namespace std;
#define maxn 10000

int n,N[maxn],E[maxn][maxn];stack<int> node;

void dfs(int u)
{
    node.push(u);
    for(int v=0;v<n;++v)if(E[u][v])
    	{E[u][v]=E[v][u]=0;dfs(v);break;}
}

void fleury(int s)
{
    node.push(s);
    while(!node.empty())
    {
        int u=node.top(),v,o;node.pop();
        for(v=0,o=0;v<n&&!o;++v)o=E[u][v];
        if(o) dfs(u);
        else printf("%d\n",u);
    }
}

int main(){}

