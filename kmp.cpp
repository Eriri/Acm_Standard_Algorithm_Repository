#include<bits/stdc++.h>
using namespace std;
#define maxn 100000

int next[maxn];bool matched[maxn];

void build(string s)
{
	int i=-1,j=0;next[0]=-1;
	while(j<s.length())
		if(i==-1||s[i]==s[j])next[++j]=++i;else i=next[i];
}

int match(string s,string t)
{
	int i=0,j=0;
	while(i<s.length())
	{
		if(s[i]==t[j])
		{
			++i;++j;
			if(j==t.length()){matched[i-1]=true;j=next[j];}
		}
		else{j=next[j];if(j==-1){++i;++j;}}
	}
}

int main(){}
