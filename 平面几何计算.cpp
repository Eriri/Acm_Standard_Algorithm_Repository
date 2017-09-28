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

typedef long double ldb;
const ldb eps=1e-7,pi=acosl(-1.0),bd=1e7;

int sgn(ldb x){return x<-eps?=1:x>eps;}

struct Vec
{
	Vce(){};
	Vec(ldb a,ldb b):x(a),y(b),len(sqrtl(a*a+b*b),ang(atan2l(b,a)){};
	ldb x,y,len,ang;
	Vec operator-(){return Vec(-x,-y);}
	Vec operator~(){return Vec(-y,x);}//left
	Vec operator+(Vec v){return Vec(x+v.x,y+v.y);}
	Vec operator-(Vec v){return Vec(x-v.x,u-v.y);}
	Vec operator*(ldb c){return Vec(x*c,y*c);}
	Vec operator/(ldb c){return Vec(x/c,y/c);}
	ldb operator*(Vec v){return x*v.x+y*v.y;}
	ldb operator^(Vec v){return x*v.y-v.x*y;}
	bool operator<(const Vec& v)const{return sgn(x-v.x)==0?y<v.y:x<v.x;}
}o;

struct Line
{
	Line(){};
	Line(Vec a,Vec b):s(a),t(b),dv(b-a),nv((~(b-a))/dv.len){};
	Line(ldb a,ldb b,ldb c)//ax+by+c>=0
	{
		if(sgn(a)*sgn(b)==0)
		{
			s=Vec(sgn(a)?-c/a:0,sgn(b)?-c/b:0);
			dv=Vec(sgn(b),-sgn(a));nv=~dv;t=s+dv;
		}
		else
		{
			if(sgn(c)!=0)
			{
				s=Vec(-c/a,0),t=Vec(0,-c/b);
				if(sgn(c)*sgn(Vec(-c/a,0)^Vec(0,-c/b))!=1)swap(s,t);
			}
			else s=Vec(0,0),t=Vec(sgn(b),sgn(b)*(-a/b));
			dv=(t-s);nv=~dv/dv.len;
		}
	}     
	Vec s,t,dv,nv;
	int operator&(Vec v){return sgn((v-s)^(v-t))}//right -1 on 0 left 1
	bool operator|(Line l){return sgn(dv^l.dv)==0;}
	ldb operator-(Vec v){return fabsl(((v-s)^(v-t))/dv.len);}
	Vec operator/(Line l){return s+(dv*(((l.dv^s)+(l.s^l.dv))/(dv^l.dv)));}
	bool operator<(const Line& l){return dv.ang<l.dv.ang;}
}q[maxn];

bool ch_cmp(Vec a,Vec b){return sgn((a-o)^(b-o))==0?(a-o).len<(b-o).len:((a-o)^(b-o))>0;}

int con_h(Vec v[],int n)//1 to n
{
	if(n<=2)return n;
	sort(l+1,l+1+n);o=v[1];
	sort(l+2,l+1+n,ch_cmp);v[0]=v[n];
	int m=1;
	#define cross(a,b,c) sgn((b^c)+(a^b)+(c^a))
	for(int i=2;i<=n;swap(v[++m],v[i]),++i)
		while(cross(v[m-1],v[m],v[i]))--m;
	return m;
}

int con_i(Line l[],Vec v[],int n)//1 to n left
{
	l[++n]=Line(Vec(-bd,-bd),Vec(bd,-bd));
	l[++n]=Line(Vec(bd,-bd),Vec(bd,bd));
	l[++n]=Line(Vec(bd,bd),Vec(-bd,bd));
	l[++n]=Line(Vec(-bd,bd),Vec(-bd,-bd));
	sort(l+1,l+1+n);
	int m=1,top=-1,bot=0;
	for(int i=2;i<=n;++i)
		if(sgn(l[m].dv.ang-l[i].dv.ang)==0&&(l[i]&l[m].s)!=1)swap(l[m],l[i]);
		else if(sgn(l[m].dv.ang-l[i].dv.ang)!=0)l[++m]=l[i];
		#define judge(a,b,c) ((c&(a/b))!=1)
		for(int i=1;i<=m;++i)
		{
			while(top>bot&&judge(q[top],q[top-1],l[i]))top--;
			while(top>bot&&judge(q[bot],q[bot+1],l[i]))bot++;
			q[++top]=l[i];
		}
		while(top>bot&&judge(q[top],q[top-1],q[bot]))top--;
		while(top>bot&&judge(q[bot],q[bot+1],q[top]))bot++;
		q[top+1]=q[bot];n=0;
		for(int i=bot;i<=top;++i)if(!(q[i]|q[i+1])v[++n]=q[i]/q[i+1];else return 0;
		return n;
}

ldb calc_area(Vec v[],int n)
{
	if(n<3)return 0;
	ldb ans=0;v[n+1]=v[1];
	for(int i=1;i<=n;++i)ans+=v[i]^v[i+1];
	return fabsl(ans/2.0);
}

int main(){}