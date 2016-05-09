#include<bits/stdc++.h>
using namespace std;

#define eps 1e-7

struct Point
{
    Point(){};
    Point(double _x,double _y):x(_x),y(_y){};
    double point_dis(Point p)
    {return sqrt((x-p.x)*(x-p.x)+(y-p.y)*(y-p.y));}
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
        
        
    }
    Point centre;
    double r; 
};

double triangle_area(Point p1,Point p2,Point p3)
{return 0.5*Line(p1,p2).point_dis(p3)*p1.point_dis(p2);}

double convex_area(Point p[],int size)
{
	int i;double ans;
	for(i=1,ans=0;i<size-1;++i)
	ans+=triangle_area(p[0],p[i],p[i+1]);
	return ans;
}


int main(){}
