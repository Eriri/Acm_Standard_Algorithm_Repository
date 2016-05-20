#include<bits/stdc++.h>
using namespace std;

#define eps 1e-7

struct Point
{
	Point(){};
	Point(double _x,double _y):x(_x),y(_y){};
	double point_dis(Point p)
	{return sqrt((x-p.x)*(x-p.x)+(y-p.y)*(y-p.y));}
	double sinx(Point p)
	{return (p.y-y)/point_dis(p);}
	double cosx(Point p)
	{return (p.x-x)/point_dis(p);}
	double x,y;
};

struct Vector
{
	Vector(double _x,double _y):x(_x),y(_y){}
	Vector(Point p1,Point p2):x(p2.x-p1.x),y(p2.y-p1.y){};
	double angle_cos_roate(Vector v)
	{}
	double x,y;
};

struct Line
{
	Line(double _a,double _b,double _c):a(_a),b(_b),c(_c){};
	Line(Point p,Point q):a(p.y-q.y),b(q.x-p.x),c(p.x*q.y-p.y*q.x){};
	bool is_parallel(Line l)
	{return fabs(a*l.b-l.a*b)<eps;}
	double line_dis(Line l)
	{return fabs(this->point_dis(Point(0,0))-l.point_dis(Point(0,0)));}
	double point_dis(Point p)
	{return fabs(a*p.x+b*p.y+c)/sqrt(a*a+b*b);}
	Point cross_poi(Line l)
	{return Point((b*l.c-l.b*c)/(a*l.b-l.a*b),(l.a*c-a*l.c)/(a*l.b-l.a*b));}
	Point projection_poi(Point p)
	{return cross_poi(Line(b,-a,a*p.y-b*p.x));}
	double a,b,c;
};

struct Circle
{
	Circle(){};
	Circle(double _x,double _y,double _r):centre(Point(_x,_y)),r(_r){};
	Circle(Point _c,double _r):centre(_c),r(_r){};
	bool point_in_circle(Point p)
	{return centre.point_dis(p)<=r;}
	int circle_pos_stas(Circle c)
	{
		if(fabs(centre.point_dis(c.centre)-(r+c.r))<eps)return 1;//ex-tan
		if(fabs(centre.point_dis(c.centre)-fabs(r-c.r))<eps)return -1;//in-tan
		if(centre.point_dis(c.centre)>(r+c.r))return 2;
		if(centre.point_dis(c.centre)<fabs(r-c.r))return -2;
		return 0;
	}
	Point centre;
	double r; 
};

double triangle_area(Point p1,Point p2,Point p3)
{return 0.5*Line(p1,p2).point_dis(p3)*p1.point_dis(p2);}

bool cvx_cmp_1(Point a,Point b){return fabs(a.y-b.y)<eps?a.x<b.x:a.y<b.y;}
bool cvx_cmp_2(Point a,Point b){return p[1].cosx(a)>p[1].cosx(b);}
double ccw(Point a,Point b,Point c){return (b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x);}

void convex_fmt(Point p[],int size)//Point marked with 1..size
{
	sort(p+1,p+size+1,cvx_cmp_1);
	sort(p+2,p+size+1,cvx_cmp_2);
	p[0]=p[size];
	int m=1;
	for(int i=2;i<=size;++i)
	{
		while(ccw(p[m-1],p[m],p[i])<=0)
		{
			if(m>1)	--m;
			else if(i==size) break;
			else ++i;
		}
		++m;
		swap(p[m],p[i]);
	}
	size=m;
}

double convex_area(Point p[],int size)//already convex
{
	int i;double ans;
	for(i=2,ans=0;i<size;++i)
	ans+=triangle_area(p[1],p[i],p[i+1]);
	return ans;
}

int main(){}