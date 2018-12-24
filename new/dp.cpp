#include<bits/stdc++.h>
using namespace std;
#define rep(i,s,t) for(int i=(s);i<(t);++i)
#define repb(i,s,t) for(int i=(s);i<=(t);++i)
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define sz(x) ((int)x.size())
#define mst(a,b) memset(a,b,sizeof(a))
#define dd(x) cout<<#x<<'='<<x<<' '
#define de(x) cout<<#x<<'='<<x<<'\n'
#define fi first
#define se second
#define sq(x) ((x)*(x))
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef double db;
typedef vector<vector<db> > mat;
typedef db(*func)(db x);

const int inf = 0x3f3f3f3f;
const ll inff = 4557430888798830399ll;
const db eps = 1e-12;
const ll mod = 1e9+7;


/*
void ob(int x){rep(i,0,12)cout<<((x>>(i+i))&3);cout<<" ";}
//-1 strict|0 choose|1 must
#define upd(a,v) a=max(a,v)
template<class S,class T>
T connective_dp(int g[maxn][maxm],int n,int m){
	unordered_map<S,T> H[2],h;
	int x[32],o=0,k,ct;S s,p,q;T v;
	rep(i,0,32)x[i]=i+i;H[o][0]=0;
	repb(i,1,n){
		h.clear();for(auto z:H[o])h[z.fi<<2]=z.se;H[o]=h;
		repb(j,1,m){
			o^=1;H[o].clear();
			for(auto z:H[o^1]){
				if(z.fi>>x[m+1])continue;
				s=z.fi;v=z.se;p=(s>>x[j-1])&3;q=(s>>x[j])&3;
				if(g[i][j]==-1){if(!p&&!q)upd(H[o][s],v+V[i][j]);}
				else if(!p&&!q){
					if(g[i][j]==0)upd(H[o][s],v+V[i][j]);
					upd(H[o][s^(1<<x[j-1])^(2<<x[j])],v+V[i][j]);}
				else if(!p||!q)
					upd(H[o][s],v+V[i][j]),
					upd(H[o][s^((p|q)<<x[j-1])^((p|q)<<x[j])],v+V[i][j]);
				else if(p==q){
					for(k=p-1?j-2:j+1,ct=1;;p-1?k--:k++){
						if(((s>>x[k])&3)==p)ct++;
						if(((s>>x[k])&3)==(p^3))ct--;
						if(!ct)break;}
					upd(H[o][s^(p<<x[j-1])^(q<<x[j])^(3<<x[k])],v+V[i][j]);}
				else if(p==1&&q==2&&i==n&&j==m)
					upd(H[o][(s^(p<<x[j-1])^(q<<x[j]))],v+V[i][j]);
				else if(p==2&&q==1)upd(H[o][s^(p<<x[j-1])^(q<<x[j])],v+V[i][j]);}}}
	return H[o][0];}*/

/*
(j,i]	p[i]-p[j]-j*(s[i]-s[j])
(k,i]	p[i]-p[k]-k*(s[i]-s[k])
(j,i]>(k,i]
(p[k]-k*s[k])-(p[j]-j*s[j]) > -s[i]*(k-j)
k<j (p[k]-k*s[k])-(p[j]-j*s[j]) / (k-j) < -s[i]
k>j (p[k]-k*s[k])-(p[j]-j*s[j]) / (k-j) > -s[i]
*/

#define maxn 200005
ll a[maxn],p[maxn],s[maxn];

typedef pair<ll,ll> P;
ll operator^(P a,P b){return a.fi*b.se-a.se*b.fi;}
bool judge(P a,P b,P c){return ((a^b)+(b^c)+(c^a))<=0;}
ll get(int i,int j){return p[i]-p[j]-(s[i]-s[j])*j;}
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int n,l,r,m;vector<P> c;P t;ll ans;
	cin>>n;
	repb(i,1,n)cin>>a[i];
	repb(i,1,n)s[i]=s[i-1]+a[i],p[i]=p[i-1]+a[i]*i;
	c.pb(mp(0,0));ans=0;
	repb(i,1,n)
	{
		l=1;r=sz(c)-2;
		while(l<=r)
		{
			m=(l+r)/2;
			ans=max(ans,get(i,c[m].fi));
			if((c[m-1].se-c[m].se)>=(c[m-1].fi-c[m].fi)*(-s[i])||
				(c[m+1].se-c[m].se)<=(c[m+1].fi-c[m].fi)*(-s[i]))
			l=m+1;
			else r=m-1;
		}
		ans=max(ans,max(get(i,c[0].fi),get(i,c[sz(c)-1].fi)));
		t=mp(i,p[i]-s[i]*i);
		while(sz(c)>1&&judge(c[sz(c)-2],c[sz(c)-1],t))c.pop_back();
		c.pb(t);
	}
	cout<<ans<<endl;
}

