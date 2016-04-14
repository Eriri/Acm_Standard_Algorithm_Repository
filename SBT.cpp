#include<bits/stdc++.h>
using namespace std;

struct node
{
	node(){num=size=left=right=0;};
	int num,left,right,size;
}N[1000006];

int cnt=1;

int leftrotate(int n)
{
	int right=N[n].right;
	N[n].right=N[right].left;
	N[right].left=n;
	N[right].size=N[n].size;
	N[n].size=N[N[n].right].size+N[N[n].left].size+1;
	return right;
}

int rightrotate(int n)
{
	int left=N[n].left;
	N[n].left=N[left].right;
	N[left].right=n;
	N[left].size=N[n].size;
	N[n].size=N[N[n].right].size+N[N[n].left].size+1;
	return left;
}

int maintain(int n,bool flag)//true->right;false->left;
{
	if(flag==false)
	{
		if(N[N[N[n].left].left].size>N[N[n].right].size) n=rightrotate(n);
		
		else if(N[N[N[n].left].right].size>N[N[n].right].size)
		{
			N[n].left=leftrotate(N[n].left);
			n=rightrotate(n);
		}
		
		else return n;
	}
	
	else if(N[N[N[n].right].right].size>N[N[n].left].size) n=leftrotate(n);
	
	else if(N[N[N[n].right].left].size>N[N[n].left].size)
	{
		N[n].right=rightrotate(N[n].right);
		n=leftrotate(n);
	}
	
	else return n;
	
	N[n].left=maintain(N[n].left,true);
	N[n].right=maintain(N[n].right,false);
	n=maintain(n,true);
	n=maintain(n,false);
}

int insert(int n,int v)
{
	if(n==0)
	{
		N[cnt].num=v;
		N[cnt].size=1;
		cnt++;
		return cnt-1;
	}
	else
	{
		++N[n].size;
		
		if(v<N[n].num) N[n].left=insert(N[n].left,v);
		else N[n].right=insert(N[n].right,v);
		
		n=maintain(n,v>N[n].num);
		return n;
	}
}

int find(int n,int k)
{
	if(k>N[n].size) return 0;
	else
	{
		if(k<=N[N[n].left].size) return find(N[n].left,k);
		else if(k>N[N[n].left].size+1) return find(N[n].right,k-(N[N[n].left].size+1));
		else return N[n].num;
	}
}

int main()
{
	int n;
	int root,val,kth_num;
	scanf("%d",&n);
	root=0;
	for(int i=0;i<n;++i)
	{
		scanf("%d",&val);
		root=insert(root,val);
	}
	scanf("%d",&kth_num);
	printf("%d\n",find(root,kth_num));
}


