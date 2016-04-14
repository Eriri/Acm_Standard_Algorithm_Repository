#include<bits/stdc++.h>
using namespace std;

int next[100000];

int main()
{
	int i,j;
	string w;
	cin>>w;
	next[0]=-1;
	i=-1,j=0;
	while(j<w.length())
	{
		if(i==-1||w[i]==w[j])
		{
			++i;++j;
			next[j]=i;
		}
		else
		{
			i=next[i];
		}
	}
}
