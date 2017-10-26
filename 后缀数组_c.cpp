struct suffix_array
{
	struct element{int i,k[2];}A[maxn],B[maxn];
	char S[maxn]; 
	int n,m,c[maxn],ra[maxn],sa[maxn],he[maxn];
	void construct(char str[],int len,int up)
	{
		memset(ra,0,sizeof(ra));
		n=len;m=up;A[0].k[0]=A[0].k[1]=-1;
		for(int i=1;i<=len;++i)
			A[i].i=i,S[i]=A[i].k[0]=str[i],A[i].k[1]=0;
		radix_sort();
		for(int j=1;j<n;j<<=1)
		{
			for(int i=1;i<=n;++i)
				A[i].i=i,A[i].k[0]=ra[i],A[i].k[1]=i+j<=n?ra[i+j]:0;
			radix_sort();
		}
		for(int i=1;i<=n;++i)sa[ra[i]]=i;
	}
	void radix_sort()
	{
		for(int p=1;p>=0;--p)
		{
			memset(c,0,sizeof(c));
			for(int i=1;i<=n;++i)++c[A[i].k[p]];
			for(int i=1;i<=m;++i)c[i]+=c[i-1];
			for(int i=n;i>=1;--i)B[c[A[i].k[p]]--]=A[i];	//stable
			for(int i=1;i<=n;++i)A[i]=B[i];
		}
		for(int i=1;i<=n;++i)
		{
			ra[A[i].i]=ra[A[i-1].i];
			if(A[i].k[0]!=A[i-1].k[1]||A[i].k[1]!=A[i-1].k[1])ra[A[i].i]++;
		}
	}
	void calculate()
	{
		int h=0;
		for(int i=1;i<=n;he[ra[i++]]=h,h?h--:0)
			for(;S[i+h]==S[sa[ra[i]-1]+h];h++);
	}
};
