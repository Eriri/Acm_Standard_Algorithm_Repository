#include<bits/stdc++.h>
using namespace std;
#define rep(i,s,t) for(int i=(s);i<(t);++i)
#define repb(i,s,t) for(int i=(s);i<=(t);++i)
#define lepb(i,s,t) for(int i=(s);i>=(t);--i)
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define sz(x) ((int)x.size())
#define mst(a,b) memset(a,b,sizeof(a))
#define mcpy(a,b) memcpy(a,b,sizeof(a))
#define dd(x) cout<<#x<<'='<<x<<' '
#define de(x) cout<<#x<<'='<<x<<'\n'
#define _ puts("-----")
#define fi first
#define se second
#define sq(x) ((x)*(x))
typedef long long ll;
typedef pair<int,int> pii;
typedef double db;

const int inf = 0x3f3f3f3f;
const ll inff = 4557430888798830399ll;
const db eps = 1e-12;
const db pi = acosl(-1.0);
const ll mod = 1e9+7;

char io[1<<15],*is=io,*ie=io+1;
#define rd if(++is==ie)ie=(is=io)+fread(io,1,sizeof(io),stdin)
template<class T>
inline bool Cin(T &a){
	a=0;bool s=0;
	if(is==ie)return 0;
	do{rd;if(*is=='-')s=1;}while(!isdigit(*is)&&is!=ie);
	if(is==ie)return 0;
	do{(a*=10)+=*is&15;rd;}while(isdigit(*is)&&is!=ie);
	if(s)a=-a;return 1;}

inline int Gets(char a[]){
	int p=0;
	if(is==ie)return 0;
	do rd; while(!isgraph(*is)&&is!=ie);
	if(is==ie)return 0;
	do {a[p++]=*is;rd;}while(isgraph(*is)&&is!=ie);
	a[p]=0;return p;}

#define maxn 200005
#define maxm 5000005
namespace Seg
{
	#define ls(u) ch[u][0],l,(l+r)/2
	#define rs(u) ch[u][1],(l+r)/2+1,r
	int ch[maxm][2],T[maxm],cnt=1,S[maxm];
	void init(){mst(S,0);mst(ch,0);cnt=1;}//1...n
	void upd(int u){S[u]=S[ch[u][0]]+S[ch[u][1]];}
	int insert(int& u,int l,int r,map<int,int>& p)
	{
		if(p.lower_bound(l)==p.upper_bound(r))return u;
		int v=cnt++;assert(cnt<=maxm);
		if(l==r){S[v]=S[u]+p[l];return v;}
		ch[v][0]=insert(ls(u),p);ch[v][1]=insert(rs(u),p);
		upd(v);return v;
	}
	int insert(int& u,int l,int r,int& p,int a)
	{
		if(p<l||p>r)return u;
		int v=cnt++;assert(cnt<=maxm);
		if(l==r){S[v]=S[u]+a;return v;}
		ch[v][0]=insert(ls(u),p,a);ch[v][1]=insert(rs(u),p,a);
		upd(v);return v;
	}
	int que(int u,int l,int r,int L,int R)
	{
		if(R<l||L>r||l>r||L>R)return 0;
		if(L<=l&&r<=R)return S[u];
		return que(ls(u),L,R)+que(rs(u),L,R);
	}
	int sum(int u,int l,int r,int D)
	{
		if(D<l)return 0;if(r<=D)return S[u];
		return sum(ls(u),D)+sum(rs(u),D);
	}
	int kth(int u,int l,int r,int k)
	{
		if(l==r)return l;
		if(k<=S[ch[u][0]])return kth(ls(u),k);
		return kth(rs(u),k-S[ch[u][0]]);
	}
	void dfs(int u,int l,int r){
		dd(u);dd(l);dd(r);dd(ch[u][0]);de(ch[u][1]);de(S[u]);
		if(l==r)return;dfs(ls(u));dfs(rs(u));}
	#undef ls
	#undef rs
};

namespace Seg_p
{ 
	#define ls(u) u->ch[0],l,(l+r)/2
	#define rs(u) u->ch[1],(l+r)/2+1,r
	struct E
	{
		E(){S=0;ch[0]=ch[1]=NULL;};
		int S;E* ch[2];
	}*T[maxn];
	void init(){T[0]=new E();T[0]->ch[0]=T[0]->ch[1]=T[0];}
	void upd(E* u){u->S=u->ch[0]->S+u->ch[1]->S;}
	E* insert(E* u,int l,int r,map<int,int>& p)
	{
		if(p.lower_bound(l)==p.upper_bound(r))return u;
		E* v=new E();
		if(l==r){v->S=u->S+p[l];return v;}
		v->ch[0]=insert(ls(u),p);v->ch[1]=insert(rs(u),p);
		upd(v);return v;
	}
	E* insert(E* u,int l,int r,int p,int a)
	{
		if(p<l||p>r)return u;
		E* v=new E();
		if(l==r){v->S=u->S+a;return v;}
		v->ch[0]=insert(ls(u),p,a);v->ch[1]=insert(rs(u),p,a);
		upd(v);return v;
	}
	int que(E* u,int l,int r,int L,int R)
	{
		if(R<l||L>r||l>r||L>R)return 0;
		if(L<=l&&r<=R)return u->S;
		return que(ls(u),L,R)+que(rs(u),L,R);
	}
	int sum(E* u,int l,int r,int D)
	{
		if(l>D)return 0;if(r<=D)return u->S;
		return sum(ls(u),D)+sum(rs(u),D);
	}
	int kth(E* u,int l,int r,int k)
	{
		if(l==r)return l;
		if(k<=u->ch[0]->S)return kth(ls(u),k);
		return kth(rs(u),k-u->ch[0]->S);
	}
	int kth(E* L,E* R,int l,int r,int k)
	{
		if(l==r)return l;
		if(k<=R->ch[0]->S-L->ch[0]->S)return kth(L->ch[0],ls(R),k);
		return kth(L->ch[1],rs(R),k-(R->ch[0]->S-L->ch[0]->S));
	}
	void dfs(E* u,int l,int r){
		dd(l);dd(r);de(u->S);
		if(l==r)return;dfs(ls(u));dfs(rs(u));}
	#undef ls
	#undef rs
};

namespace St
{
	int st[maxn][20],dpth[maxn];
	set<int> N[maxn];map<int,int> val[maxn];map<int,int>::iterator it;
	void gen_st(int n){rep(j,1,20)repb(i,1,n)st[i][j]=st[st[i][j-1]][j-1];}
	void dfs(int u,int f)
	{
		dpth[u]=dpth[f]+1;st[u][0]=f;
		for(auto v:N[u])if(v!=f)dfs(v,u);
	}
	int lca(int u,int v)
	{
		if(dpth[u]<dpth[v])swap(u,v);
		int d=dpth[u]-dpth[v];
		rep(i,0,20)if((1<<i)&d)u=st[u][i];
		if(u==v)return u;
		lepb(i,19,0)if(st[u][i]!=st[v][i])u=st[u][i],v=st[v][i];
		return st[u][0];
	}
}


int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
}
