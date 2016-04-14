#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int map[7][7],degree[7];
void dfs(int node)
{
	int i;
	for(i=0;i<7;++i)
	{
		if(map[node][i])
		{
			--degree[node];
			--degree[i];
			--map[node][i],--map[i][node];
			dfs(i);
		}
	}
};
int gra()
{
	int i;
	for(i=0;i<7;++i)
	{
		if(degree[i])
		{
			return 0;
		}
	}
	return 1;
};
int main()
{
	int i,j,k;
	int n;
    int u,v;
	int single;
	memset(map,0,sizeof(map));
	memset(degree,0,sizeof(degree));
	scanf("%d",&n);
	for(i=0;i<n;++i)
	{
		scanf("%d%d",&u,&v);
		++map[u][v],++map[v][u];
		++degree[u],++degree[v];
	}
	single=0;
	for(i=0;i<7;++i)
	{
		if(degree)
		{
			u=i;
			if(degree[i]%2)
			{
				v=i;
			    ++single;
			}
		}
	}
	if(single==0||single==2)
	{
		if(single==0)
		{
			dfs(u);
		}
		else 
		{
			dfs(v);
		}
		if(gra())
		{
			printf("yes\n");
		}
		else
		{
			printf("no\n");
		}	
		
	}
	else
	{
		printf("no\n");
	}
	return 0;
}
