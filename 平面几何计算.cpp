#include<bits/stdc++.h>
using namespace std;

#define eps 1e-7

struct point
{
    point(){};
    point(double _x,double _y):x(_x),y(_y){};
    double point_dis(point p)
    {return sqrt((x-p.x)*(x-p.x)+(y-p.y)*(y-p.y));}
    double x,double y;
}

struct line
{
    line(double _a,double _b,double _c):a(_a),b(_b),c(_c){};
    line(point p,point q):a(p.y-q.y),b(q.x-p.x),c(p.x*q.y-p.y*q.x){};
    bool is_parallel(line l)
    {return fabs(a*l.b-l.a*b)<eps;}
    double line_dis(line l)
    {return fabs(this.point_dis(point(0,0))-l.point_dis(0,0);}
    double point_dis(point p)
    {return fabs(a*p.x+b*p.y+c)/sqrt(a*a+b*b);}
    point cross_poi(line l)
    {return point((b*l.c-l.b*c)/(a*l.b-l.a*b),(l.a*c-a*l.c)/(a*l.b-l.a*b));}
    double a,b,c;
}

struct circle
{
    circle(){};
    circle(double _x,double _y,double _r):centre(point(_x,_y)),r(_r){};
    circle(point _c,double _r):centre(_c),r(_r){};
    bool point_in_circle(point p)
    {return centre.point_dis(p)<=r;}
    int circle_pos_stas(circle c)
    {
        
        
    }
    point centre;
    double r; 
}


double triangle_area(point p1,point p2,point p3)//unclockwise
{
	return (0.5)*(p1.x*p2.y+p2.x*p3.y+p3.x*p1.y-p1.x*p3.y-p2.x*p1.y-p3.x*p2.y);
}