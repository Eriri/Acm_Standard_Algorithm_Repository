#include<bits/stdc++.h>
using namespace std;

#define maxn

int n,N[maxn];
bool E[maxn][maxn];
stack<int> node;

void dfs(int u)
{
    int v;
    node.push(u);
    for(v=0;v<n;++v)if(E[u][b])
    {
        E[u][v]=E[v][u]=false;
        dfs(v);
        break;
    }
}

void fleury(int s)
{
    int u,v;
    bool oe;
    node.push(s);
    while(!node.empty())
    {
        u=node.top();node.pop();
        for(v=0,oe=false;v<n&&oe==false;++v)oe=E[u][v];
        if(oe) dfs(u);
        else printf("%d\n",u);
    }
}

int main()
{
    read_map();//input eular map,node start from 0.
    fleury(0);
}

