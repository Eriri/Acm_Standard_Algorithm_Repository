#include<bits/stdc++.h>
using namespace std;
#define rep(i,s,t) for(int i=(s);i<(t);++i)
#define repb(i,s,t) for(int i=(s);i<=(t);++i)
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define sz(x) ((int)x.size())
#define mst(a,b) memset(a,b,sizeof(a))
#define sq(x) ((x)*(x))
#define dd(x) cout<<#x<<'='<<x<<' '
#define de(x) cout<<#x<<'='<<x<<'\n'
#define fi first
#define se second
typedef unsigned long long ull;
typedef unsigned int uint;
typedef long long ll;
typedef double db;
typedef pair<int,int> pii;

const int inf = 0x3f3f3f3f;
const ll mod = 1e9+7;
const db pi = acos(-1.0);
const db eps = 1e-8;

template<class T>inline bool Max(T&a,T b){if(a<b){a=b;return 1;};return 0;}
template<class T>inline bool Min(T&a,T b){if(a>b){a=b;return 1;};return 0;}

/*
struct BIT{
	BIT(){}
	void init(int n){N=n;assert(N<maxn);mst(a,0);}
	int lowbit(int x){return x&(-x);}
	void upd(int p,int v){for(;p<=N;a[p]+=v,p+=lowbit(p));}
	int sum(int p){int s=0;for(;p>0;s+=a[p],p-=lowbit(p));return s;}
	int sum(int l,int r){return sum(r)-sum(l-1);}
	int N,a[maxn];};

struct BIT2{
	BIT2(){};
	void init(int n){N=n;assert(N<maxn);mst(a,0);}
	int lowbit(int x){return x&(-x);}
	void upd(int x,int y,int v){
		for(int i=x;i<=N;i+=lowbit(i))
			for(int j=y;j<=N;j+=lowbit(j))a[i][j]+=v;}
	int sum(int x,int y){
		int s=0;
		for(int i=x;i>0;i-=lowbit(i))
			for(int j=y;j>0;j-=lowbit(j))s+=a[i][j];
		return s;}
	int sum(int lx,int ly,int rx,int ry){
		return sum(rx,ry)-sum(rx,ly-1)-sum(lx-1,ry)+sum(lx-1,ly-1);}
	int N,a[maxn][maxn];};

template<class T>
struct splay{
	splay(){};
	void init(){mst(ch,0);mst(pre,0);mst(sz,0);mst(rev,0);rt=0;cnt=1;}
	void app_rev(int u){rev[u]^=1;swap(ch[u][0],ch[u][1]);}
	void pu(int u){sz[u]=sz[ch[u][0]]+sz[ch[u][1]]+1;}
	void pd(int u){if(rev[u])app_rev(ch[u][0]),app_rev(ch[u][1]),rev[u]=0;}
	int D(int f,int u){return ch[f][1]==u;}
	void rot(int u){
		int f=pre[u],g=pre[f],d=D(f,u);pd(f);pd(u);
		ch[f][d]=ch[u][!d];pre[ch[f][d]]=f;
		pre[u]=g;pre[f]=u;ch[u][!d]=f;
		if(g)ch[g][D(g,f)]=u;pu(f);}

	void acc(int u,int a=0){
		if(!u)return;int f,g;
		for(pd(u);pre[u]!=a;){
			f=pre[u],g=pre[f];
			if(g!=a)D(f,u)==D(g,f)?rot(u):rot(f);rot(u);}
			pu(u);if(!a)rt=u;}

	//0 pre|1 next
	int cursor(int u,int d){
		for(acc(u),u=ch[u][d];u&&ch[u][!d];u=ch[u][!d]);return u;}

	void insert(T v){
		if(!rt)a[cnt]=v,sz[cnt]=1,rt=cnt++;
		else acc(insert(rt,v));}

	int insert(int u,T v){
		pd(u);if(v==a[u])return 0;
		if(ch[u][v>a[u]])return insert(ch[u][v>a[u]],v);
		a[cnt]=v;sz[cnt]=1;pre[cnt]=u;ch[u][v>a[u]]=cnt;return cnt++;}

	int build(int l,int r,T b[]){
		if(l>r)return 0;
		int m=(l+r)>>1,u=cnt++;a[u]=b[m];
		if(ch[u][0]=build(l,m-1,b))pre[ch[u][0]]=u;
		if(ch[u][1]=build(m+1,r,b))pre[ch[u][1]]=u;
		pu(u);return rt=u;}

	int kth(int k,int u){
		pd(u);
		if(k<=sz[ch[u][0]])return kth(k,ch[u][0]);
		else if(k==sz[ch[u][0]]+1)return u;
		else return kth(k-sz[ch[u][0]]-1,ch[u][1]);}

	void reverse(int l,int r){
		assert(l>=1&&l<=sz[rt]&&r>=1&&r<=sz[rt]&&l<=r);
		if(l==1&&r==sz[rt])app_rev(rt);
		else if(l==1)acc(kth(r+1,rt)),app_rev(ch[rt][0]);
		else if(r==sz[rt])acc(kth(l-1,rt)),app_rev(ch[rt][1]);
		else acc(kth(l-1,rt)),acc(kth(r+1,rt),rt),app_rev(ch[ch[rt][1]][0]);}

	int split(int l,int r){
		int z,k,d;
		if(l==1&&r==sz[rt])z=rt,rt=0;
		else if(l==1||r==sz[rt]){
			if(l==1)k=r+1,d=0;if(r==sz[rt])k=l-1,d=1;
			acc(kth(k,rt));pd(rt);
			z=ch[rt][d];pre[z]=ch[rt][d]=0;pu(rt);}
		else{
			acc(kth(l-1,rt));acc(kth(r+1,rt),rt);pd(rt);pd(ch[rt][1]);
			z=ch[ch[rt][1]][0];pre[z]=ch[ch[rt][1]][0]=0;pu(ch[rt][1]);pu(rt);}
		return z;}
	
	int merge(int x,int y){
		acc(kth(sz[x],x));x=rt;
		acc(kth(1,y));y=rt;
		ch[y][0]=x;pre[x]=y;pu(y);
		return y;}
	
	void dbg(int u){
		if(ch[u][0])dbg(ch[u][0]);
		dd(u);dd(a[u]);dd(pre[u]);dd(sz[u]);
		if(ch[u][0])dd(ch[u][0]);
		if(ch[u][1])dd(ch[u][1]);
		cout<<endl;
		if(ch[u][1])dbg(ch[u][1]);}

	T a[maxn];
	int ch[maxn][2],pre[maxn],sz[maxn],rt,cnt;
	bool rev[maxn];
};

typedef unsigned long long ull;
struct BITSET
{
	BITSET(){mst(v,0);}
	ull v[50];
	void s0(int p){v[p>>6]&=~(1ull<<p);}
	void s1(int p){v[p>>6]|=1ull<<p;}
};


const int maxn = 500005;
template<class C>
struct KDTREE_static{
	using vec=vector<C>;int cnt,rt,k;
	struct _{int ch[2];vec v,bd[2];}T[maxn];
	
	inline void upd(vec& v,vec& u,int o){rep(i,0,k)o?Max(v[i],u[i]):Min(v[i],u[i]);}
	inline void upd(_& v){
		rep(c,0,2)if(v.ch[c])rep(o,0,2)upd(v.bd[o],T[v.ch[c]].bd[o],o);};
	
	void build(vector<vec>& v,int _k){cnt=1;k=_k;rt=build(v,0,sz(v)-1,0);}
	int build(vector<vec>& v,int l,int r,int o){
		if(l>r)return 0;int u=cnt++,m=(l+r)/2;
		nth_element(v.begin()+l,v.begin()+m,v.begin()+r+1,
		[&](vec a,vec b){return a[o]<b[o];});
		T[u]={{build(v,l,m-1,(o+1)%k),
				build(v,m+1,r,(o+1)%k)},v[m],{v[m],v[m]}};
		upd(T[u]);return u;}
	
	inline C dis(vec& a,vec& b){
	//	C d=0;rep(i,0,k)d+=sq(a[i]-b[i]);return d;}
		C d=0;rep(i,0,k)d+=abs(a[i]-b[i]);return d;}
	inline C dismax(vec& a,_& b){
		C d=0;
		rep(i,0,k){
		//	d+=max(sq(a[i]-b.bd[0][i]),sq(a[i]-b.bd[1][i]));}
			d+=max(abs(a[i]-b.bd[0][i]),abs(a[i]-b.bd[1][i]));}
		return d;}
	inline C dismin(vec& a,_& b){
		C d=0;
		rep(i,0,k){
			if(b.bd[0][i]<=a[i]&&a[i]<=b.bd[1][i])continue;
		//	d+=min(sq(a[i]-b.bd[0][i]),sq(a[i]-b.bd[1][i]));}
			d+=min(abs(a[i]-b.bd[0][i]),abs(a[i]-b.bd[1][i]));}
		return d;}

	pair<C,vec> que(vec& v,int o){
		C d=o?numeric_limits<C>::min():numeric_limits<C>::max();vec z;
		que(rt,v,d,z,o);return mp(d,z);}
	void que(int u,vec& v,C& d,vec& z,int& o){//0 min|1 max
		if(!u||o?dismax(v,T[u])<=d:dismin(v,T[u])>=d)return;
		if(v!=T[u].v&&(o?Max(d,dis(v,T[u].v)):Min(d,dis(v,T[u].v))))z=T[u].v;
		rep(c,0,2)if(T[u].ch[c])que(T[u].ch[c],v,d,z,o);}
	
	void qmaxk(int u,vec& v,priority_queue<C,vector<C>,greater<C>>& q,int n){
		if(sz(q)<n||dis(v,T[u].v)>q.top())q.push(dis(v,T[u].v));if(sz(q)>n)q.pop();
		rep(c,0,2)if(T[u].ch[c]&&dismax(v,T[T[u].ch[c]])>q.top())que(T[u].ch[c],v,q,n);}
};
KDTREE_static<ll> kdt;


const int maxn = 1000006;
template<class C>
struct KDTREE_dynamic{
	using vec=vector<C>;
	int M[maxn],hd,tl;struct _{int ch[2];vec v,bd[2];int a,s,e;}T[maxn];int k,rt,r;
	
	KDTREE_dynamic(){hd=1;tl=0;T[0]={{0,0},{},{{},{}},0,0,0};rt=0;}
	
	int _new(){int r=M[hd];if(!r)r=hd;(hd+=1)%=maxn;return r;}
	void _del(int u,vector<vec>& v){
		if(T[u].e)v.pb(T[u].v);M[tl]=u;(tl+=1)%=maxn;
		rep(c,0,2)if(T[u].ch[c])_del(T[u].ch[c],v);}

	void upd(vec &v,vec &u,int o){rep(i,0,k)o?Max(v[i],u[i]):Min(v[i],u[i]);}
	void upd(int v){
		T[v].a=1;T[v].s=T[v].e;int a=0;
		rep(c,0,2)if(T[v].ch[c]){
			rep(o,0,2)upd(T[v].bd[o],T[T[v].ch[c]].bd[o],o);
			T[v].a+=T[T[v].ch[c]].a,T[v].s+=T[T[v].ch[c]].s;
			Max(a,T[T[v].ch[c]].a);}
		if(T[v].a>2*T[v].s||a*4>T[v].a*3)r=v;}
	
	void build(vector<vec>& v,int _k){k=_k;rt=build(v,0,sz(v)-1,0);}
	int build(vector<vec>& v,int l,int r,int o){
		if(l>r)return 0;int u=_new(),m=(l+r)/2;
		nth_element(v.begin()+l,v.begin()+m,v.begin()+r+1,
		[&](vec a,vec b){return a[o]<b[o];});
		T[u]={{build(v,l,m-1,(o+1)%k),
				build(v,m+1,r,(o+1)%k)},v[m],{v[m],v[m]},1,1,1};
		upd(u);return u;}
	
	int rebuild(int u,vec& v,int o){
		if(r==u){vector<vec> a;_del(u,a);return build(a,0,sz(a)-1,o);}
		int c=T[u].v[o]<v[o];T[u].ch[c]=rebuild(T[u].ch[c],v,(o+1)%k);
		upd(u);return u;}
	
	void insert(vec v){
		if(!rt){rt=_new();T[rt]={{0,0},v,{v,v},1,1,1};return;}
		r=0;insert(rt,v,0);if(r)rt=rebuild(rt,v,0);}
	void insert(int u,vec& v,int o){
		int c=T[u].v[o]<v[o];
		if(T[u].ch[c]){insert(T[u].ch[c],v,(o+1)%k);upd(u);return;}
		T[u].ch[c]=_new();T[T[u].ch[c]]={{0,0},v,{v,v},1,1,1};upd(u);}
	
	void erase(vec v){r=0;erase(rt,v,0);if(r)rt=rebuild(rt,v,0);}
	void erase(int u,vec& v,int o){
		int c=T[u].v[o]<v[o];
		if(T[u].v==v&&T[u].e){T[u].e=0;return;}
		erase(T[u].ch[c],v,(o+1)%k);upd(u);}
	
	C dis(vec& v,vec& u){C d=0;rep(i,0,k)d+=abs(v[i]-u[i]);return d;}
	C dismax(vec& v,_& u){
		C d=0;
		rep(i,0,k)d+=max(abs(v[i]-u.bd[0][i]),abs(v[i]-u.bd[1][i]));
		return d;}
	C dismin(vec& v,_& u){
		C d=0;
		rep(i,0,k){
			if(u.bd[0][i]<=v[i]&&v[i]<=u.bd[1][i])continue;
			d+=min(abs(v[i]-u.bd[0][i]),abs(v[i]-u.bd[1][i]));}
		return d;}

	pair<C,vec> que(vec v,int o){//0 min|1 max
		C d=(o?numeric_limits<C>::min():numeric_limits<C>::max());vec z;
		que(rt,v,d,z,o);return mp(d,z);}
	void que(int& u,vec& v,C& d,vec& z,int& o){
		if(!u||(o?dismax(v,T[u])<=d:dismin(v,T[u])>=d))return;
		if(T[u].e&&(o?Max(d,dis(v,T[u].v)):Min(d,dis(v,T[u].v))))z=T[u].v;
		rep(c,0,2)if(T[u].ch[c])que(T[u].ch[c],v,d,z,o);}
	
	void dfs(int u)
	{
		dd(u);dd(T[u].ch[0]);de(T[u].ch[1]);
		dd(T[u].bd[0][0]);
		dd(T[u].bd[0][1]);
		dd(T[u].bd[1][0]);
		de(T[u].bd[1][1]);
		if(T[u].e)cout<<"("<<T[u].v[0]<<","<<T[u].v[1]<<")"<<endl;
		rep(c,0,2)if(T[u].ch[c])dfs(T[u].ch[c]);
	}

};
KDTREE_dynamic<ll> kdt;

template<class C>
struct KDTREE_pointer
{
	using vec=vector<C>;
	struct _{_*ch[2];vec v,bd[2];int a,s,e;};_*rt,*r;int k;
	KDTREE_pointer(){init();}
	
	void init(int _k=0){k=_k;rt=0;}
	
	void upd(vec &v,vec &u,int o){rep(i,0,k)(o?Max(v[i],u[i]):Min(v[i],u[i]));}
	void upd(_*v){
		v->a=1;v->s=v->e;int a=0;
		rep(c,0,2)if(v->ch[c]){
			rep(o,0,2)upd(v->bd[o],v->ch[c]->bd[o],o);
			v->a+=v->ch[c]->a;v->s+=v->ch[c]->s;Max(a,v->ch[c]->a);}
		if(v->a>2*v->s||a*4>v->a*3)r=v;}
	void del(_*u,vector<vec>& v){
		if(u->e)v.pb(u->v);rep(c,0,2)if(u->ch[c])del(u->ch[c],v);delete(u);}

	void build(vector<vec>& v){rt=build(v,0,sz(v)-1,0);}
	_*build(vector<vec>& v,int l,int r,int o){
		if(l>r)return 0;int m=(l+r)/2;_*u;
		nth_element(v.begin()+l,v.begin()+m,v.begin()+r+1,
		[&](vec a,vec b){return a[o]<b[o];});
		u=new _({{build(v,l,m-1,(o+1)%k),build(v,m+1,r,(o+1)%k)},
				v[m],{v[m],v[m]},1,1,1});
		upd(u);return u;}
	
	_*rebuild(_*u,vec& v,int o){
		if(u==r){vector<vec> a;del(u,a);return build(a,0,sz(a)-1,o);}
		int c=u->v[o]<v[o];u->ch[c]=rebuild(u->ch[c],v,(o+1)%k);upd(u);return u;}
	
	void insert(vec v){
		if(!rt){rt=new _({{0,0},v,{v,v},1,1,1});return;}
		r=0;insert(rt,v,0);if(r)rt=rebuild(rt,v,0);}
	void insert(_*u,vec& v,int o){
		int c=u->v[o]<v[o];
		if(u->ch[c])insert(u->ch[c],v,(o+1)%k);
		else u->ch[c]=new _({{0,0},v,{v,v},1,1,1});
		upd(u);}
		(x.a==y.a&&x.b==y.b&&x.c<y.c);}
	
	void erase(vec v){
		r=0;erase(rt,v,0);if(r)rt=rebuild(rt,v,0);}
	void erase(_*u,vec& v,int o){
		if(!u)return;if(u->v==v&&u->e){u->e=0;upd(u);return;}
		erase(u->ch[u->v[o]<v[o]],v,(o+1)%k);upd(u);}
	
	C dis(vec& a,vec& b){
	//	C d=0;rep(i,0,k)d+=sq(a[i]-b[i]);return d;}
		C d=0;rep(i,0,k)d+=abs(a[i]-b[i]);return d;}	
	C dismax(vec& a,_* b){
		C d=0;
	//	rep(i,0,k)d+=max(sq(a[i]-b->bd[0][i]),sq(a[i]-b->bd[1][i]));
		rep(i,0,k)d+=max(abs(a[i]-b->bd[0][i]),abs(a[i]-b->bd[1][i]));
	//	de(d);
		return d;}
	C dismin(vec& a,_* b){
		C d=0;rep(i,0,k){
			if(b->bd[0][i]<=a[i]&&a[i]<=b->bd[1][i])continue;
	//		d+=min(sq(a[i]-b->bd[0][i]),sq(a[i]-b->bd[1][i]));}
			d+=min(abs(a[i]-b->bd[0][i]),abs(a[i]-b->bd[1][i]));}
		return d;}
	
	pair<C,vec> que(vec v,int o){//0 min|1 max
		C d=(o?numeric_limits<C>::min():numeric_limits<C>::max());vec z;
		que(rt,v,z,d,o);return mp(d,z);;}
	void que(_*u,vec& v,vec &z,C& d,int& o){
		if(!u||(o?(dismax(v,u)<=d):(dismin(v,u)>=d)))return;
		if(u->e&&(o?Max(d,dis(v,u->v)):Min(d,dis(v,u->v))))z=u->v;
		rep(c,0,2)if(u->ch[c])que(u->ch[c],v,z,d,o);}
	
	bool cot(vec& a,vec& b,vec& c){
		rep(i,0,k)if(a[i]>c[i]||c[i]>b[i])return false;return true;}
	bool cot(vec& a,vec& b,_*u){
		rep(i,0,k)if(a[i]>u->bd[0][i]||u->bd[1][i]>b[i])return false;return true;}

	int sum(vec a,vec b){return sum(rt,a,b);}
	int sum(_*u,vec& a,vec& b){
		if(!u)return 0;if(cot(a,b,u))return u->s;
		return cot(a,b,u->v)+sum(u->ch[0],a,b)+sum(u->ch[1],a,b);}

	void dfs(_*u)
	{
		cout<<u<<" ";
		if(u->e){
			cout<<u->v[0]<<" "<<u->v[1]<<endl;
			dd(u->bd[0][0]);dd(u->bd[0][1]);
			dd(u->bd[1][0]);de(u->bd[1][1]);
		}
		rep(c,0,2)if(u->ch[c])cout<<"c"<<c<<" "<<u->ch[c]<<endl;
		rep(c,0,2)if(u->ch[c]){
			dfs(u->ch[c]);
		}
	}
	
};
KDTREE_pointer<int> kdt;
*/

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

const int maxn=2e5+5;
int d[maxn];
struct item{int a,b,c,d,t;};
bool operator<(item x,item y){
	return mp(x.a,mp(x.b,x.c))<mp(y.a,mp(y.b,y.c));}
bool operator==(item& x,item& y){
	if(x.a==y.a&&x.b==y.b&&x.c==y.c){
		x.d+=y.d;return true;}
	return false;}

struct BIT{
	BIT(){}
	void init(int n){N=n;assert(N<maxn);mst(a,0);}
	int lowbit(int x){return x&(-x);}
	void upd(int p,int v){for(;p<=N;a[p]+=v,p+=lowbit(p));}
	int sum(int p){int s=0;for(;p>0;s+=a[p],p-=lowbit(p));return s;}
	int sum(int l,int r){return sum(r)-sum(l-1);}
	int N,a[maxn];}B;


void cdq(int l,int r,vector<item>& v)
{
	if(l>=r)return;
	int m=(l+r)>>1,hd=l;vector<item> t;
	cdq(l,m,v);cdq(m+1,r,v);
	repb(i,m+1,r){
		for(;hd<=m&&v[hd].b<=v[i].b;hd++)B.upd(v[hd].c,v[hd].d),t.pb(v[hd]);
		v[i].t+=B.sum(v[i].c);t.pb(v[i]);}
	rep(i,l,hd)B.upd(v[i].c,-v[i].d);
	rep(i,hd,m+1)t.pb(v[i]);
	repb(i,l,r)v[i]=t[i-l];
}

int main()
{
//	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);

	int n,k,a,b,c;vector<item> v;
	B.init(200000);
	Cin(n);Cin(k);
	repb(i,1,n)
	{
		Cin(a);Cin(b);Cin(c);
		v.pb({a,b,c,1,0});
	}
	sort(all(v));v.erase(unique(all(v)),v.end());
	cdq(0,sz(v)-1,v);
	rep(i,0,sz(v))d[v[i].t+v[i].d-1]+=v[i].d;
	rep(i,0,n)printf("%d\n",d[i]);
	
}
