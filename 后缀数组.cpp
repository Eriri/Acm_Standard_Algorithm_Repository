#include<bits/stdc++.h>
using namespace std;
#define maxn 1000
/*
�ַ�Ҫ��ת��Ϊ������
��������ַ�������r �����У���r[0]��r[n-1]������Ϊn�������ֵС��m��
���е�r[i]������0,r[n]�������㷨����0
���������󣬽������sa ������(���δ�1..n)����sa[1]��sa[n]��s[0]������
*/
int cmp(int *r,int a,int b,int l)
{
	return r[a]==r[b]&&r[a+l]==r[b+l];
}
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
height[2..n]:height[i]�������lcp(sa[i],sa[i-1])
rank[0..n-1]:rank[i]�������ԭ����suffix[i]������
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
