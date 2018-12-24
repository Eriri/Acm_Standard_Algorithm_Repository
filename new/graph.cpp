#include<bits/stdc++.h>
using namespace std;
#define rep(i,s,t) for(int i=(s);i<(t);++i)
#define per(i,s,t) for(int i=((t)-1);i>=(s);--i)
#define repb(i,s,t) for(int i=(s);i<=(t);++i)
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define sz(x) ((int)x.size())
#define mst(a,b) memset(a,b,sizeof(a))
#define mstc(a,b,c) memset(a,b,c*sizeof(a[0]))
#define dd(x) cout<<#x<<'='<<x<<' '
#define de(x) cout<<#x<<'='<<x<<'\n'
#define fi first
#define se second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int,int> pii;

const int inf = 0x3f3f3f3f;
const int inf_ = 0x7fffffff;
const ll inff = 4557430888798830399ll;
const double pi = acos(-1.0);
ll mod = 1e9+7;

/*
支配集D:对于任意点要么属于D,要么与D中点相邻
独立集I:I中任意两点不相邻
极大独立集I=>极小支配集D
G中最大团=~G中最大独立集

点覆盖集C:对于任意边至少有一个顶点属于C
G(V)-C是独立集I:~任意边至少有一个顶点属于C=>不会存在两个端点都属于G(V)-C的边
极小点覆盖集C<=>极大点独立集G(V)-C

边独立集:图G的匹配,二分图中最大边独立集=最小点覆盖集=最大匹配
边覆盖集:图G任意点至少与一条边关联

最小割算法:在剩余图中从点s深度优先搜索到的所有点构成集合S
割边集一定满流,满流边不一定是割边
对满流边赋容量1并跑最大流可获得最小割边集数量
或将原图容量变换为cap*(E+1)+1,最大流对E+1取模为最小割边集(割边数量<E)
DAG最小路径覆盖=点数-拆点最大匹配边数
二分图最小点覆盖集:不在任意一个匹配上的点一定不在点覆盖集内

最大匹配后可以由s搜到的点不在所有最大匹配中

0->1,1 0->2,2 2->1,1 1->3,2 2->3,1

struct DIJK{
	DIJK(){init();}
	int N[maxn],vt[maxm],ne[maxm],wei[maxm],dis[maxn],cnt;
	void init(){mst(N,0);cnt=1;}
	void link(int u,int v,int w){assert(cnt<maxm);vt[cnt]=v;wei[cnt]=w;ne[cnt]=N[u];N[u]=cnt++;}
	int run(int s,int t=0){
		priority_queue<pii,vector<pii>,greater<pii> > q;int u,d;
		mst(dis,inf);dis[s]=0;q.push(mp(0,s));
		while(!q.empty()){
			d=q.top().fi;u=q.top().se;q.pop();
			if(d>dis[u])continue;if(u==t)break;
			for(int e=N[u];e;e=ne[e])if(dis[vt[e]]>dis[u]+wei[e])
				q.push(mp(dis[vt[e]]=dis[u]+wei[e],vt[e]));}
		return dis[t];}};

struct ISAP{//[s..t]
    int cnt,u,v,e,s,t,d,tf,flow;
    int N[maxn],now[maxn],dpth[maxn],vtn[maxn],pre[maxn],vt[maxm],ne[maxm],cap[maxm];
    void init(int _s,int _t,int _d){s=_s;t=_t;d=_d;cnt=2;flow=0;mst(N,0);};
    void link(int u,int v,int c){vt[cnt]=v;ne[cnt]=N[u];cap[cnt]=c;N[u]=now[u]=cnt++;}//now[x]
    void build(int u,int v,int c){link(u,v,c);link(v,u,0);}
    void run(){
    	mst(dpth,0);mst(vtn,0);vtn[0]=d;
        for(u=s;dpth[s]<d;){
            if(u==t){
                for(v=s,tf=inf;v!=t;v=vt[now[v]])tf=min(cap[now[v]],tf);
                for(v=s;v!=t;v=vt[now[v]])cap[now[v]]-=tf,cap[now[v]^1]+=tf;
                u=s;flow+=tf;}
            else{
                for(e=now[u];e;e=ne[e])if(cap[e]&&dpth[vt[e]]+1==dpth[u])break;
                if(e){now[u]=e;pre[vt[e]]=u;u=vt[e];}
                else{
                    if(--vtn[dpth[u]]==0)break;
                    for(e=N[u],v=d;e;e=ne[e])if(cap[e]>0)v=min(v,dpth[vt[e]]);
                    dpth[u]=v+1;++vtn[dpth[u]];now[u]=N[u]; 
                    if(u!=s)u=pre[u];}}}}};

struct ISAP_s{
	int cnt,s,t,d,n,flow,G[maxn],V[maxm],C[maxm],N[maxm],H[maxn],D[maxn];
	void init(int _s,int _t,int _d){s=_s;t=_t;d=_d;cnt=2;flow=0;mst(G,0);}
	void link(int u,int v,int c){V[cnt]=v;C[cnt]=c;N[cnt]=G[u];G[u]=cnt++;}
	void build(int u,int v,int c){link(u,v,c);link(v,u,0);}
	int sap(int u,int f){
		int a=0,e,c;
		if(H[s]>=d)return 0;if(u==t)return f;
		for(e=G[u];e&&a<f;e=N[e])if(C[e]&&H[V[e]]+1==H[u])
			c=sap(V[e],min(C[e],f-a)),C[e]-=c,C[e^1]+=c,a+=c;
		if(a==f)return a;if(!--D[H[u]])H[s]=d;
		H[u]++;D[H[u]]++;return a;}
	void run(){
		mst(D,0);mst(H,0);D[0]=d;
		while(H[s]<d)flow+=sap(s,inf);}};

struct KM{
	int lx[maxn],ly[maxn],w[maxn][maxn],to[maxn],slack[maxn],d,n;
	bool vx[maxn],vy[maxn];
	void init(int N){mst(lx,0);mst(ly,0);mst(w,0);mst(to,0);n=N;}
	void link(int u,int v,int _w){w[u][v]=_w;}
	bool dfs(int i){
		vx[i]=true;
		repb(j,1,n){
			if(!vy[j]&&lx[i]+ly[j]==w[i][j]){
				vy[j]=true;
				if(!to[j]||dfs(to[j])){to[j]=i;return true;}}
			else slack[j]=min(slack[j],lx[i]+ly[j]-w[i][j]);}
		return false;}
	void run(){
		mst(ly,0);mst(to,0);
		repb(i,1,n)lx[i]=*max_element(w[i]+1,w[i]+1+n);
		repb(i,1,n){
			while(1){
				mst(slack,inf);mst(vx,0);mst(vy,0);
				if(dfs(i))break;
				d=inf;repb(j,1,n)if(!vy[j])d=min(d,slack[j]);
				repb(j,1,n)if(vx[j])lx[j]-=d;
				repb(j,1,n)if(vy[j])ly[j]+=d;}}}};

struct SCC{
	SCC(){init(0,0);}
	int n,t,ts,dfn[maxn],low[maxn],fa[maxn],s[maxn];vector<int>*N;
	void init(int _n,vector<int>*_N){
		n=_n;N=_N;t=-1;ts=1;mst(dfn,0);mst(low,0);mst(fa,0);}
	void dfs(int u){
		dfn[u]=low[u]=ts++;s[++t]=u;
		for(auto v:N[u]){
			if(!dfn[v])dfs(v),low[u]=min(low[u],low[v]);
			else if(!fa[v])low[u]=min(low[u],dfn[v]);}
		if(dfn[u]==low[u])do fa[s[t]]=u;while(s[t--]!=u);}
	void run(){repb(i,1,n)if(!dfn[i])dfs(i);}};

struct BCC{
	BCC(){init(0,0);}
	int n,m,t,dfn[maxn],low[maxn],fa[maxn],s[maxn];
	vector<int>*N,cut;vector<pii> bridge;
	void init(int _n,vector<int>*_N){
		n=_n;m=0;t=-1;N=_N;mst(dfn,0);mst(low,0);cut.clear();bridge.clear();}
	void dfs(int u,int d,int p){
		int sec=0,son=d>1;dfn[u]=low[u]=d;s[++t]=u;
		for(auto v:N[u]){
			if(!dfn[v]){
				dfs(v,d+1,u);low[u]=min(low[u],low[v]);
				if(low[v]>dfn[u])bridge.pb(mp(u,v));
				if(low[v]>=dfn[u]&&++son==2)cut.pb(u);}
			else if(v!=p||sec++)low[u]=min(low[u],dfn[v]);}
		if(dfn[u]==low[u])do fa[s[t]]=u;while(s[t--]!=u);}
	void run(){repb(i,1,n)if(!dfn[i])dfs(i,1,0);}};

struct DCC{
	DCC(){init(0,0);}
	int n,t,h,m,dfn[maxn],low[maxn],s[maxn],e[maxn],g[maxn];
	vector<int>*N,cut,D[maxn],F[maxn];bool mark[maxn];
	void init(int _n,vector<int>* _N){
		n=_n;N=_N;t=h=-1;m=0;mst(dfn,0);mst(low,0);mst(mark,0);cut.clear();}
	void dfs(int u,int d,int p){
		int sec=0,son=d>1,e;dfn[u]=low[u]=d;s[++t]=u;
		for(auto v:N[u]){
			if(!mark[e=id[u][v]])g[++h]=e,mark[e]=1;
			if(!dfn[v]){
				dfs(v,d+1,u);low[u]=min(low[u],low[v]);
				if(low[v]>=dfn[u]){
					if(++son==2)cut.pb(u);
					m+=1;D[m].clear();D[m].pb(u);F[m].clear();
					do F[m].pb(g[h]);while(g[h--]!=e);
					do D[m].pb(s[t]);while(s[t--]!=v);}}
			else if(v!=p||sec++)low[u]=min(low[u],dfn[v]);}}
	void run(){repb(i,1,n)if(!dfn[i])dfs(i,1,0);gen();}}

struct HLPP{
	HLPP(){init(0,0,0);}
	int N[maxn],E[maxn],V[maxn],D[maxn],vt[maxm],cap[maxm],ne[maxm];
	int cnt,s,t,d,flow;priority_queue<pii> q;bool in[maxn];
	void init(int _s,int _t,int _d){
		s=_s;t=_t;d=_d;cnt=2;flow=0;mst(N,0);mst(E,0);mst(D,0);mst(V,0);mst(in,0);}
	void link(int u,int v,int c){vt[cnt]=v;cap[cnt]=c;ne[cnt]=N[u];N[u]=cnt++;}
	void build(int u,int v,int c){link(u,v,c);link(v,u,0);}
	inline void push(int u){q.push(mp(D[u],u));}
	inline int pop(){int u=q.top().se;q.pop();return u;}
	void run(){
		int u,e,z;D[s]=d;E[s]=~0u>>1;V[0]=d-1;push(s);in[s]=1;
		while(!q.empty()){
			in[u=pop()]=0;if(!E[u]||u==t)continue;
			for(e=N[u];e&&E[u];e=ne[e])if(cap[e]&&(u==s||D[u]==D[vt[e]]+1)){
				z=min(cap[e],E[u]);
				E[u]-=(u!=s)*z;E[vt[e]]+=z;cap[e]-=z;cap[e^1]+=z;
				if(vt[e]!=s&&!in[vt[e]])push(vt[e]),in[vt[e]]=1;}
			if(u!=s&&E[u]){
				if(!--V[D[u]]){
					for(e=1,z=D[u];e<=d;e++)if(D[e]>=z&&e!=s&&e!=t)D[e]=d,E[e]=0;
					continue;}
				for(e=N[u],z=d;e;e=ne[e])if(cap[e])z=min(z,D[vt[e]]+1);
				V[D[u]=z]++;push(u);}}
		flow=E[t];}};


struct MSC{
	MSC(){init(0,0);}
	int n,deg[maxn],rk[maxn],nxt[maxn],mxc[maxn],cn;bool vis[maxn],perfect;
	vector<int>*N,peo,indep;priority_queue<pii> q;
	void init(int _n,vector<int>*_N){
		n=_n;N=_N;mst(vis,0);mst(deg,0);peo.clear();}
	bool run(){
		int u;q.push(mp(0,1));
		while(!q.empty()){
			u=q.top().se;q.pop();
			if(vis[u])continue;
			vis[u]=1;peo.pb(u);
			for(auto v:N[u])
				if(!vis[v])deg[v]+=1,q.push(mp(deg[v],v));}
		reverse(all(peo));rep(i,0,sz(peo))rk[peo[i]]=i;
		return perfect=check();}
	bool check(){
		if(n!=sz(peo))return false;
		auto cmp=[&](int a,int b){return rk[a]<rk[b];};
		repb(i,1,n){
			sort(all(N[i]),cmp);
			nxt[i]=lower_bound(all(N[i]),i,cmp)-N[i].begin();}
		per(i,0,n){
			int u=peo[i],p=nxt[u];
			if(p<sz(N[u])){
				int v=N[u][p],q=nxt[v];
				rep(m,p+1,sz(N[u])){
					while(q<sz(N[v])&&rk[N[v][q]]<rk[N[u][m]])q+=1;
					if(q==sz(N[v])||rk[N[v][q]]!=rk[N[u][m]])return false;}}}
		return true;}
	int maxclique(){//==min color
		cn=0;repb(i,1,n)mxc[i]=sz(N[i])-nxt[i]+1;
		per(i,0,n){
			int u=peo[i],p=nxt[u];
			if(p<sz(N[u])){
				int v=N[u][p],q=nxt[v];
				if(sz(N[v])-q+1<=sz(N[u])-p)mxc[v]=0;}}
		return cn=*max_element(mxc+1,mxc+1+n);}
	vector<int> maxindep(){//==min clique cover
		mst(vis,0);indep.clear();
		rep(i,0,sz(peo))if(!vis[peo[i]]){
			indep.pb(peo[i]);
			for(auto v:N[peo[i]])vis[v]=1;}
		return indep;}};

struct CF{//[s..t] careful with int-overflow
	CF(){init(0,0);}
	int N[maxn],vt[maxm],ne[maxm],cap[maxm],wei[maxm],d[maxn],p[maxn],h[maxn];
	int cnt,s,t,flow,cost;priority_queue<pii,vector<pii>,greater<pii> > q;
	void init(int _s,int _t){s=_s;t=_t;cnt=2;flow=cost=0;mst(N,0);}
	void link(int u,int v,int c,int w){vt[cnt]=v;cap[cnt]=c;wei[cnt]=w;ne[cnt]=N[u];N[u]=cnt++;}
	void build(int u,int v,int c,int w){link(u,v,c,w);link(v,u,0,-w);}
	bool dijk(){
		mst(d,inf);q.push({0,s});d[s]=0;
		while(!q.empty()){
			int u=q.top().se,z=q.top().fi;q.pop();
			if(z>d[u])continue;
			for(int e=N[u];e;e=ne[e])if(cap[e]&&d[u]+wei[e]+h[u]-h[vt[e]]<d[vt[e]])
				p[vt[e]]=e^1,q.push({d[vt[e]]=d[u]+wei[e]+h[u]-h[vt[e]],vt[e]});}
		return d[t]<inf;}
	int add(int u,int f=inf){
		for(int v=u;v!=s;v=vt[p[v]])f=min(f,cap[p[v]^1]);
		for(int v=u;v!=s;v=vt[p[v]])cap[p[v]]+=f,cap[p[v]^1]-=f;
		return f;}
	void run(){
		mst(p,0);mst(h,0);
		for(int f=0;dijk();f=add(t),flow+=f,cost+=f*h[t])
			repb(u,s,t)h[u]+=d[u];}};

struct ZKW{//[s..t] | generate dis from t when negative graph
	ZKW(){init(0,0);}
	int N[maxn],vt[maxm],ne[maxm],cap[maxm],wei[maxm],dis[maxn],vis[maxn],s,t,cnt,flow,cost;
	void init(int _s,int _t){s=_s;t=_t;mst(N,0);cnt=2;flow=cost=0;}
	void link(int u,int v,int c,int w){
		vt[cnt]=v;cap[cnt]=c;wei[cnt]=w;ne[cnt]=N[u];N[u]=cnt++;}
	void build(int u,int v,int c,int w){link(u,v,c,w);link(v,u,0,-w);}
	bool modify(int add=inf){
		repb(u,s,t)if(vis[u])for(int e=N[u];e;e=ne[e])if(!vis[vt[e]]&&cap[e])
			add=min(add,dis[vt[e]]+wei[e]-dis[u]);
		if(add==inf)return 0;repb(u,s,t)if(vis[u])dis[u]+=add;return 1;}
	int dfs(int u,int f=inf){
		if(u==t)return flow+=f,cost+=f*dis[s],f;
		int nf=0,tf;vis[u]=1;
		for(int e=N[u];e&&f>nf;e=ne[e])if(!vis[vt[e]]&&cap[e]&&dis[vt[e]]+wei[e]==dis[u])
			tf=dfs(vt[e],min(cap[e],f-nf)),cap[e]-=tf,cap[e^1]+=tf,nf+=tf;
		return nf;}
	void run(){mst(dis,0);do do mst(vis,0);while(dfs(s));while(modify());}};

namespace mini_cut{//point with S
bool vis[maxn];
template<class T>void solve(T& f,int u,vector<int>& v){
	v.pb(u);vis[u]=1;
	for(int e=f.N[u];e;e=f.ne[e])
		if(f.cap[e]&&!vis[f.vt[e]])solve(f,f.vt[e],v);}
template<class T>vector<int> solve(T& f){
	mst(vis,0);vector<int> v;
	solve(f,f.s,v);sort(all(v));return v;}}

struct HUNGARY{
	HUNGARY(){init(0,0);};
	int n,m,to[maxn],vt[maxn];bool vis[maxn];vector<int> N[maxn];
	void init(int _n,int _m){
		n=_n;m=_m;repb(i,1,n)N[i].clear();mst(to,0);mst(vt,0);}
	void link(int u,int v){N[u].pb(v);}
	bool dfs(int u){
		for(auto v:N[u])if(!vis[v]){
			vis[v]=1;
			if(!to[v]||dfs(to[v])){to[v]=u,vt[u]=v;return 1;}}
		return 0;}
	void run(){repb(i,1,n)if(!vt[i]){mst(vis,0);dfs(i);}}
	set<int> A,B;
	void dfsc(int u){
		A.erase(u);
		for(auto v:N[u])if(!vis[v]){
			vis[v]=1;B.insert(v);
			if(to[v]&&A.count(to[v]))dfsc(to[v]);}}
	void cover(){
		mst(vis,0);A.clear();B.clear();
		repb(i,1,n)A.insert(i);
		repb(i,1,n)if(!vt[i])dfsc(i);}};
*/


int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
}

