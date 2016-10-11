#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll ext_gcd(ll a,ll b,ll &x,ll &y)
{
	if(b==0){x=1;y=0;return a;}
	else
	{
		ll t=ext_gcd(b,a%b,y,x);
		y-=x*(a/b);return t;
	}
}

void linear_equations(ll a,ll b,ll c)
{
	ll d,x,y;
	d=ext_gcd(a,b,x,y);//c%d==0
	x*=c/d;//x=x0+(b/d)*t
	y*=c/d;//y=y0-(a/d)*t
}

int main(){};
