#include<bits/stdc++.h>
using namespace std;

struct poi
{
    
}


double cal(poi p1,poi p2,poi p3)//unclockwise
{
	return (0.5)*(p1.x*p2.y+p2.x*p3.y+p3.x*p1.y-p1.x*p3.y-p2.x*p1.y-p3.x*p2.y);
}