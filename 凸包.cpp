#include<bits/stdc++.h>
using namespace std;

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
	return x/sqrt(x*x+y*y);
}

bool cmp(poi p1,poi p2)
{
	return cosx(p1,points[1])>cosx(p2,points[1]);
}

int graham_scan(int n)//n is the number of points;
{
	int m=1;
	for(int i=2,i<=n;++i)
	{
		while(ccw(points[m-1],points[m],points[i])<=0)
		{
			if(m>1)	--m;
			else if(i==n)	break;
			else ++i;
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
	scanf("%d",&n);
	for(i=1;i<=n;++i)
	{
		scamf("%lf%lf",&x,&y);
		points[i]=poi(x,y);
	}
	sort(points+1,points+1+n);
	sort(points+2,points+1+n,cmp);
	points[0]=points[n];
	m=graham_scan(n);
	for(int i=1;i<=m;++i)printf("%lf %lf\n",points[i].x,points[i].y);
}