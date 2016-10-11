#include<bits/stdc++.h>
using namespace std;
#define maxn 1000
/*
字符要先转化为正整数
待排序的字符串放在r 数组中，从r[0]到r[n-1]，长度为n，且最大值小于m。
所有的r[i]都大于0,r[n]无意义算法中置0
函数结束后，结果放在sa 数组中(名次从1..n)，从sa[1]到sa[n]。s[0]无意义
*/
int cmp(int *r,int a,int b,int l){return r[a]==r[b]&&r[a+l]==r[b+l];}
int wa[maxn],wb[maxn],wv[maxn],ws1[maxn];
void da(int *r,int *sa,int n,int m)
{
	r[n++]=0;
	int i,j,p,*x=wa,*y=wb,*t;
	for(i=0;i<m;i++)ws1[i]=0;
	for(i=0;i<n;i++)ws1[x[i]=r[i]]++;
	for(i=1;i<m;i++)ws1[i]+=ws1[i-1];
	for(i=n-1;i>=0;i--)sa[--ws1[x[i]]]=i;
	for(j=1,p=1;p<n;j*=2,m=p)
	{
		for(p=0,i=n-j;i<n;i++) y[p++]=i;
		for(i=0;i<n;i++) if(sa[i]>=j) y[p++]=sa[i]-j;
		for(i=0;i<n;i++) wv[i]=x[y[i]];
		for(i=0;i<m;i++) ws1[i]=0;
		for(i=0;i<n;i++) ws1[wv[i]]++;
		for(i=1;i<m;i++) ws1[i]+=ws1[i-1];
		for(i=n-1;i>=0;i--) sa[--ws1[wv[i]]]=y[i];
		for(t=x,x=y,y=t,p=1,x[sa[0]]=0,i=1;i<n;i++)
		x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
	}
}
/*
height[2..n]:height[i]保存的是lcp(sa[i],sa[i-1])
rank[0..n-1]:rank[i]保存的是原串中suffix[i]的名次
*/
int rank[maxn],height[maxn];
void calheight(int *r,int *sa,int n)
{
	int i,j,k=0;
	for(i=1;i<=n;i++)rank[sa[i]]=i;
	for(i=0;i<n;height[rank[i++]]=k)
		for(k?k--:0,j=sa[rank[i]-1];r[i+k]==r[j+k];k++);
}
int main(){}
