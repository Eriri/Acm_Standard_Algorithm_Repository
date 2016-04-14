#include<bits/stdc++.h>
using namespace std;

#define cst() int __t;scanf("%d",&__t);while(__t--)
#define wse(n) while(scanf("%d",&n)!=EOF)
#define wie(n) while(n!=EOF)
#define git(n) scanf("%d",&n)
#define gdb(n) scanf("%lf",&n)
#define gll(n) scanf("%lld",&n)
#define gsr(s) scanf("%s",s)
#define git2(n1,n2) scanf("%d%d",&n1,&n2)
#define gll2(n1,n2) scanf("%lld%lld",&n1,&n2)
#define gdb2(n1,n2) scanf("%lf%lf",&n1,&n2)
#define git3(n1,n2,n3) scanf("%d%d%d",&n1,&n2,&n3)
#define gll3(n1,n2,n3) scanf("%lld%lld%lld",&n1,&n2,&n3)
#define gdb3(n1,n2,n3) scanf("%lf%lf%lf",&n1,&n2,&n3)
#define git4(n1,n2,n3,n4) scanf("%d%d%d%d",&n1,&n2,&n3,&n4)
#define gll4(n1,n2,n3,n4) scanf("%lld%lld%lld%lld",&n1,&n2,&n3,&n4)
#define gdb4(n1,n2,n3,n4) scanf("%lf%lf%lf%lf",&n1,&n2,&n3,&n4)
#define rep(i,s,e) for(int i=s;i<e;++i)
#define repb(i,s,e) for(int i=s;i<=e;++i)
#define lep(i,s,e) for(int i=s;i>e;--i)
#define lepb(i,s,e) for(int i=s;i>=e;--i)
#define mst(a) memset(a,0,sizeof(a))

#define inf 0x7fffffff
#define PI acos(-1.0)
#define pow2(x) ((x)*(x))
#define eps (1e-10)

struct poi
{
	poi(){};
	poi(double xx,double yy):x(xx),y(yy){};
	double x,y;
	bool operator<(const poi p)const
	{
		return (y==p.y)?x<p.x:y<p.y;
	}
}points[10004];

double ccw(poi p1,poi p2,poi p3)
{
	return (p2.x-p1.x)*(p3.y-p1.y)-(p2.y-p1.y)*(p3.x-p1.x);
}

double cosx(poi p,poi p0)
{
	double x=p.x-p0.x;
	double y=p.y-p0.y;
	return x/sqrt(pow2(x)+pow2(y));
}

bool cmp(poi p1,poi p2)
{
	return cosx(p1,points[1])>cosx(p2,points[1]);
}

int graham_scan(int n)//n is the number of points;
{
	int m=1;
	repb(i,2,n)
	{
		while(ccw(points[m-1],points[m],points[i])<=0)
		{
			if(m>1){--m;}
			else if(i==n){break;}
			else{++i;}
		}
		++m;
		swap(points[m],points[i]);
	}
	return m;//m is the number of points in convex hull;
}

int main()
{
	int n,m;
	double x,y;
	git(n);
	repb(i,1,n)
	{
		gdb2(x,y);
		points[i]=poi(x,y);
	}
	sort(points+1,points+1+n);
	sort(points+2,points+1+n,cmp);
	points[0]=points[n];
	m=graham_scan(n);
}