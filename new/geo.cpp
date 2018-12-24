#include <bits/stdc++.h>
using namespace std;
#define rep(i,s,t) for(int i=(s);i<(t);++i)
#define per(i,s,t) for(int i=((t)-1);i>=s;--i)
#define repb(i,s,t) for(int i=(s);i<=(t);++i)
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(), (x).end()
#define sz(x) ((int)x.size())
#define mst(a, b) memset(a, b, sizeof(a))
#define fi first
#define se second
#define ft front()
#define bk back()
#define pft pop_front
#define pbk pop_back
#define discrete(x) sort(all(x));x.erase(unique(all(x)), x.end());

#define dd(x) DD(#x, (x))
#define de(x) DE(#x, (x))
template <class T> inline void DD(string s, const T &x) {cout << s << '=' << x << ' ';}
template <class T> inline void DE(string s, const T &x) {cout << s << '=' << x << '\n';}

typedef long long ll;
typedef double db;
typedef pair<int,int> pii;
typedef pair<db,db> pdd;
typedef vector<vector<db> > mat;
typedef complex<double> cpd; //*counter rotate
typedef db(func)(db);
typedef int(isok)(db);

const int inf= 0x3f3f3f3f;
const ll infl= 4557430888798830399ll;
const db infd= 1. / 0.;
const db eps = 1e-10;
const db pi  = acos(-1.);
const ll mod = 1e9 + 7;

template<class T>inline int sgn(T x){return (x>eps)-(x<-eps);}
template<class T>inline db sq(T x){return x*x;}
template<class T>inline bool Max(T&x,T y){if(x<y){x=y;return true;}return false;}
template<class T>inline bool Min(T&x,T y){if(y<x){x=y;return true;}return false;}

db det(mat v){
    db ans=1.,c;
    rep(i,0,sz(v))rep(j,i+1,sz(v))if(sgn(v[j][i])){
        ans=-ans;swap(v[i],v[j]);c=v[j][i]/v[i][i];
        rep(k,i,sz(v))v[j][k]-=v[i][k]*c;}
    rep(i,0,sz(v))ans*=v[i][i];return ans;}

mat operator*(mat a,mat b){
    int n=sz(a);mat c;c.resize(n,vector<db>(n));
    rep(i,0,n)rep(j,0,n)rep(k,0,n)c[i][j]+=a[i][k]*b[k][j];
    return c;}

db simpson(db a,db b,func f){return (f(a)+4.*f(.5*(a+b))+f(b))*(b-a)/6.;}

db asr(db a,db b,db S,func f){
    if(a>b)return 0.;
    db L=simpson(a,.5*(a+b),f),R=simpson(.5*(a+b),b,f),dS=(L+R-S)/15.;
    if(sgn(dS)==0)return L+R+dS;
    return asr(a,.5*(a+b),L,f)+asr(.5*(a+b),b,R,f);}

// o={-1,min|+1,max} t={0,left|1,right}
pair<db,db>search_extreme(db l,db r,func f,int o,int t=0,db D=eps){
    db d,lv,rv;
    while(r-l>D){
        d=(r-l)/3.;lv=f(l+d);rv=f(r-d);
        if(sgn(lv-rv)==0)t?l+=d:r-=d;
        else if(sgn(lv-rv)==o)r-=d;
	else l+=d;}return mp(.5*(l+r),f(.5*(l+r)));}

// o={-1,dec|+1,inc} t={0,left|1,right}
db binary_search(db l,db r,db s,func f,int o,int t=0,db D=eps){
    while(r-l>D){
        if(sgn(f(.5*(l+r))-s)==0)t?l=.5*(l+r):r=.5*(l+r);
        else if(sgn(f(.5*(l+r))-s)==o)r=.5*(l+r);
        else l=.5*(l+r);}return .5*(l+r);}

// o={0,n--y|1,y--n}
db binary_judge(db l,db r,isok f,int o,int D=eps){
    while(r-l>D)f(.5*(l+r))==o?l=.5*(l+r):r=.5*(l+r);
	return .5*(l+r);}

namespace D2{

struct vec{vec(){}
	vec(int O){cin>>x>>y;len=hypot(x,y),ang=atan2(y,x);}
	vec(db X,db Y):x(X),y(Y),len(hypot(X,Y)),ang(atan2(Y,X)){}
	vec(db T, db R, int o):x(R*cos(T)),y(R*sin(T)),len(R),ang(atan2(y,x)){}
	vec norm();vec trunc(db);vec rot(db);db x,y,len,ang;};

vec operator-(vec v){return vec(-v.x,-v.y);}
vec operator~(vec v){return vec(-v.y,v.x);} // left
vec operator+(vec a,vec b){return vec(a.x+b.x,a.y+b.y);}
vec operator-(vec a,vec b){return vec(a.x-b.x,a.y-b.y);}
vec operator*(vec a,db b){return vec(a.x*b,a.y*b);}
vec operator/(vec a,db b){return vec(a.x/b,a.y/b);}
db operator*(vec a,vec b){return a.x*b.x+a.y*b.y;}
db operator^(vec a,vec b){return a.x*b.y-a.y*b.x;}
//counter +|clockwise -
bool operator<(vec a,vec b){return sgn(a.x-b.x)<0||(!sgn(a.x-b.x)&&sgn(a.y-b.y)<0);}
bool operator==(vec a,vec b){return !sgn(a.x-b.x)&&!sgn(a.y-b.y);}
vec vec::norm(){assert(sgn(len));return vec(x/len,y/len);}
vec vec::trunc(db l) {assert(sgn(len));return *this*(l/len);}
vec vec::rot(db t) {return vec(x*cos(t)-y*sin(t),x*sin(t)+y*cos(t));}//left

struct line{line(){}
    line(vec a,vec b):s(a),t(b),d(b-a){if(!sgn(d.y))d=vec(d.x,0.);assert(sgn(d.len));}//(-pi,pi]
    db dis(vec);bool on(vec);int pos(vec);vec proj(vec);vec s,t,d;};

bool operator<(line p,line q){return sgn(p.d.ang-q.d.ang)<0||(!sgn(p.d.ang-q.d.ang)&&p.pos(q.s)<0);}
bool operator==(line p,line q){return !sgn(p.d.ang-q.d.ang);}
db line::dis(vec p){return ((s-p)^(t-p))/d.len;}// left +|right -
bool line::on(vec p){return !sgn((s-p)^(t-p))&&sgn((s*t)-(s*p)-(p*t)+(p*p))<1;}// on seg
int line::pos(vec p){return sgn((s-p)^(t-p));}// left +|right -
vec line::proj(vec p){return p-~d.trunc(dis(p));}

/*line ABC(db a,db b,db c){//Ax+By+C>0 line(s,t).pos(p)=1
        if(sgn(c)&&sgn(a)&&sgn(b))return line(vec(0.,-c/b),vec(-c/a,0.));
        if(sgn(c)&&sgn(a)&&!sgn(b))return line(vec(-c/a,0.),vec(-c/a,1.));
        if(sgn(c)&&!sgn(a)&&sgn(b))return line(vec(0.,-c/b),vec(1.,-c/b));
        if(!sgn(c)&&sgn(a)&&sgn(b))return line(vec(0.,0.),vec(-b,a));
        if(!sgn(c)&&sgn(a)&&!sgn(b))return line(vec(0.,0.),vec(0.,1.));
        if(!sgn(c)&&!sgn(a)&&sgn(b))return line(vec(0.,0.),vec(1.,0.));}*/

inline db area(vec a,vec b,vec c){return (a^b)+(b^c)+(c^a);}
inline int judge(vec a,vec b,vec c){return sgn((a^b)+(b^c)+(c^a));}
inline db arc(db a,db b,db c){return acos((sq(a)+sq(b)-sq(c))/(2.*a*b));}
inline db seg(db a,db r) {return r*r*(a-sin(a))/2.;}
inline db len1(vec a,vec b){return hypot(fabs(a.x-b.x),fabs(a.y-b.y));}
inline db len2(vec a,vec b){return sq(a.x-b.x)+sq(a.y-b.y);}
inline db ang1(vec v,vec o){return atan2(v.y-o.y,v.x-o.x);}
inline bool up_seg(vec s,vec t,vec p){return (sgn((t-s)*(p-s))>=0&&sgn((s-t)*(p-t))>=0);}
inline bool on_seg(vec s,vec t,vec p){return !judge(s,t,p)&&sgn((s-p)*(t-p))<1;}

struct cir{cir(){}
    cir(db X,db Y,db R):x(X),y(Y),r(R),o(vec(X,Y)){};
   	cir(vec O,db R):x(O.x),y(O.y),r(R),o(O){};
   	bool on(vec);bool out(cir);bool in(cir);db x,y,r;vec o;};

bool cir::on(vec p){return !sgn(len2(p,o)-sq(r));}
bool cir::out(cir c){return sgn(len2(o,c.o)-sq(r+c.r))>=0;}//out-touch count
bool cir::in(cir c){return sgn(r-c.r-len1(o,c.o))>=0;}//in-touch count
bool operator<(cir a,cir b){return a.o<b.o||(a.o==b.o&&sgn(a.r-b.r)<0);}

// strict X|touch T|end L|inf I|connect C|no N
int cross_judge(line p,line q){
    int a=sgn((p.s^p.t)+(p.t^q.s)+(q.s^p.s))*sgn((p.s^p.t)+(p.t^q.t)+(q.t^p.s));
    int b=sgn((q.s^q.t)+(q.t^p.s)+(p.s^q.s))*sgn((q.s^q.t)+(q.t^p.t)+(p.t^q.s));
    if(a+b==-2)return 'X';if(a+b==-1)return 'T';if(a||b)return 'N';if(sgn(p.d^q.d)) return 'L';
    int in=sgn((q.s-p.s)*(q.t-p.s))<0||sgn((q.s-p.t)*(q.t-p.t))<0||
			sgn((p.s-q.s)*(p.t-q.s))<0||sgn((p.s-q.t)*(p.t-q.t))<0;
   	int on=(p.s==q.s)+(p.s==q.t)+(p.t==q.s)+(p.t==q.t);
    if(in||on==2)return 'I';if(on)return 'C';return 'N';}

// has 1|no or inf 0
int intersect_point(line p,line q,vec &v){
    if(!sgn(p.d^q.d))return 0;
   	v=(q.t*area(p.s,p.t,q.s)+q.s*area(p.s,q.t,p.t))/
		(area(p.s,p.t,q.s)+area(p.s,q.t,p.t));return 1;}

// fast
vec isp(line p,line q){
    return (q.t*area(p.s,p.t,q.s)+q.s*area(p.s,q.t,p.t))/
			(area(p.s,p.t,q.s)+area(p.s,q.t,p.t));}

// number of points
int intersect_point(line l,cir c,vector<vec> &v){
    v.clear();db lo=fabs(l.dis(c.o));
    if(sgn(lo-c.r)>0)return 0;
    if(sgn(lo-c.r)==0){v.pb(l.proj(c.o));return 1;}
    db ld=sqrt(c.r*c.r-lo*lo);vec p=l.proj(c.o);
	v.pb(p-l.d.trunc(ld));v.pb(p+l.d.trunc(ld));return 2;}

//-1 inf
int intersect_point(cir a,cir b,vector<vec> &v){
    v.clear();if(a.o==b.o&&sgn(a.r-b.r)==0)return -1;
    db k=sq(a.o.x-b.o.x)+sq(a.o.y-b.o.y)-sq(a.r+b.r);
    if(sgn(k)>0)return 0;
    if(sgn(k)==0){v.pb(a.o+(b.o-a.o).trunc(a.r));return 1;}
    db d=len1(a.o,b.o),t=arc(a.r,d,b.r);vec z=(b.o-a.o).trunc(a.r);
    v.pb(a.o+z.rot(-t));v.pb(a.o+z.rot(t));return 2;}

// no same point|on boarder
bool in_convex_hull(vec p,vector<vec> &v){
    if(sz(v)==1)return p==v[0];
    int c=0;
    rep(i,0,sz(v)){
        c+=sgn((v[i]-p)^(v[(i+1)%sz(v)]-p));
        if(abs(c)!=i+1)return on_seg(v[i],v[(i+1)%sz(v)],p);}
    return 1;}

bool in_convex_hull_strict(vec p,vector<vec> &v){
    if(sz(v)<3)return 0;
    int c=0;
    rep(i,0,sz(v)){
        c+=sgn((v[i]-p)^(v[(i+1)%sz(v)]-p));
        if(abs(c)!=i+1)return 0;}return 1;}

bool in_polygon(vec p,vector<vec> v){
    if(sz(v)==1)return p==v[0];
    db t=0;vec a,b;
    rep(i,0,sz(v)){
       	a=v[i]-p,b=v[(i+1)%sz(v)]-p;
        if(!sgn(a.len)||!sgn(b.len))return 1;
        t+=sgn(a^b)*(acos(a*b/a.len/b.len));}
    return sgn(t) != 0;}

// judge == ang<180 non-zero area unique | != ang<=180 zero area
//< <= counter | > >= clockwise
// judge 1->counter
vector<vec> convex_hull(vector<vec> a){
    int n= 0, m;vector<vec> c;discrete(a);
    if(sz(a)<3)return a;c.resize(2*sz(a));
    for(int i=0;i<sz(a);c[n++]=a[i++])
      	while(n>1&&judge(c[n-2],c[n-1],a[i])<=0)n--;
    reverse(all(a));m=n;
    for(int i=0;i<sz(a);c[m++]=a[i++])
       	while(m>n&&judge(c[m-2],c[m-1],a[i])<=0)m--;
    c.resize(m-1);return c;}

namespace convex_hull_disjoint{
struct event{
    vec p;line l;int s, w;
    bool operator<(const event &e)const{
		return p<e.p||(p==e.p&&s>e.s)||(p==e.p&&s==e.s&&w<e.w);}};
bool solve(vector<vec> &a,vector<vec> &b){
    if(sz(a)==1)return !in_convex_hull(a[0],b);
    if(sz(b)==1)return !in_convex_hull(b[0],a);
    vector<line> L[2];vector<event> e;
    rep(i,0,sz(a)){
        e.pb({min(a[i],a[(i+1)%sz(a)]),line(a[i],a[(i+1)%sz(a)]),+1,0});
        e.pb({max(a[i],a[(i+1)%sz(a)]),line(a[i],a[(i+1)%sz(a)]),-1,0});}
    rep(i,0,sz(b)){
        e.pb({min(b[i],b[(i+1)%sz(b)]),line(b[i],b[(i+1)%sz(b)]),+1,1});
        e.pb({max(b[i],b[(i+1)%sz(b)]),line(b[i],b[(i+1)%sz(b)]),-1,1});}
    sort(all(e));
    for(auto x:e){
        if(x.s==+1){
            for(auto y:L[!x.w])
                if(cross_judge(y, x.l)!='N')return false;
            L[x.w].pb(x.l);}
        if(x.s == -1) {
            rep(i,0,sz(L[x.w]))if(L[x.w][i].s==x.l.s&&L[x.w][i].t==x.l.t){
                L[x.w].erase(L[x.w].begin()+i);break;}}}
    return !(in_convex_hull(a[0],b)||in_convex_hull(b[0],a));}
}// namespace convex_hull_disjoint

db lvmd(line l,vec v){
    db d=min(len2(l.s,v),len2(l.t,v));
   	if(up_seg(l.s,l.t,v))d=min(d,sq(area(l.s,l.t,v))/len2(l.s,l.t));
    return sqrt(d);}

db llmd(line p,line q){
    db d=min(min(lvmd(p,q.s),lvmd(p,q.t)),min(lvmd(q,p.s),lvmd(q,p.t)));
	return d;}

// counter convex hull
db chmd(vector<vec> &a,vector<vec> &b){
    if(!convex_hull_disjoint::solve(a,b))return 0.;
    if(sz(a)==1&&sz(b)==1)return len1(a[0], b[0]);
    else if(sz(a)==1){
		db d=infd;rep(i,0,sz(b))d=min(d,lvmd(line(b[i],b[(i+1)%sz(b)]),a[0]));return d;} 
	else if(sz(b) == 1) {
        db d=infd;rep(i,0,sz(a))d=min(d,lvmd(line(a[i],a[(i+1)%sz(a)]),b[0]));return d;}
    int p=min_element(all(a))-a.begin(),q=max_element(all(b))-b.begin(),n=sz(a)+sz(b);
    db d=len1(a[p],b[q]),s;
    while(n--){
        d=min(d,llmd(line(a[p],a[(p+1)%sz(a)]),line(b[q],b[(q+1)%sz(b)])));
        s=(a[(p+1)%sz(a)]-a[p])^(b[(q+1)%sz(b)]-b[q]);
        if(sgn(s)<=0)(p+=1)%=sz(a);if(sgn(s)>=0)(q+=1)%=sz(b);}
    return d;}

// only add|C correct after 3 add
struct dynamic_convex_hull{
    dynamic_convex_hull(){init();}
    typedef set<vec>::iterator svi;
    inline svi pre(svi p,set<vec> &S){return p==S.begin()?S.end():--p;}
    inline svi nxt(svi p,set<vec> &S){return p==S.end()?S.end():++p; }
    void init(){U.clear();D.clear();C=A=0.;}
    void add(vec v){add(v,U,+1);add(v,D,-1);}
    void add(vec v,set<vec> &S,int o){
        if(sz(S)==0)S.insert(v);
        if(sz(S)==1){C+=len1(*S.begin(),v);S.insert(v);}
        svi it=S.lower_bound(v);vec a,b;
        if(it!=S.end()&&v==*it)return;
        if(it!=S.end()&&it!=S.begin()){
            a=*it,b=*pre(it,S);if(judge(a,v,b)!=o)return;
            C-=len1(a,b);A+=.5*fabs(area(a,b,v));}
        for(;it!=S.end()&&nxt(it,S)!=S.end();it=S.erase(it)){
            a=*it;b=*nxt(it,S);if(judge(v,a,b)!=o)break;
			C-=len1(a,b);A+=.5*fabs(area(a,b,v));}
        for(--it;it!=S.end()&&it!=S.begin();it=S.erase(it),--it){
           	a=*pre(it,S);b=*it;if(judge(a,b,v)!=o)break;
			C-=len1(a,b);A+=.5*fabs(area(a,b,v));}
        S.insert(v);
		it=pre(S.lower_bound(v),S);if(it!=S.end())C+=len1(*it,v);
        it=nxt(S.lower_bound(v),S);if(it!=S.end())C+=len1(*it,v);
        return;}
    bool in(vec v){return in(v,U,-1)&&in(v,D,+1);}
    bool in(vec v,set<vec> &S,int o){
        if(sz(S)==0)return false;if(sz(S)==1)return v==*S.begin();
        auto it=S.lower_bound(v);
        if(it!=S.end())return it==S.begin()?*it==v:judge(*pre(it,S),v,*it)!=o;
        return false;}
    set<vec> U,D;db C,A;};

// unique|sz>3|no 3 coliner|n^3
namespace convex_hull_count {
const int maxn=150;
bool a[maxn][maxn][maxn];
ll path,f[maxn][maxn];
int v[maxn][maxn],l[maxn][maxn],n,maxlen;
int dfs(int i,int j,int s){
	if(v[i][j]==s)return f[i][j];
	f[i][j]=l[i][j]=(i!=s);v[i][j]=s;int lt=1;
	rep(k,s+1,n)if(a[i][j][k]&&a[j][k][s])
		(f[i][j]+=dfs(j,k,s))%=mod,lt=max(lt,l[j][k]);
	l[i][j]+=lt;
	return f[i][j];}
void solve(vector<vec> p){
	discrete(p);mst(a,0);mst(v,-1);
	path=maxlen=0;n=sz(p);
	rep(i,0,n)rep(j,0,n)rep(k,0,n)if(i!=j&&j!=k&&i!=k)
		a[i][j][k]=judge(p[i],p[j],p[k])>0;
	rep(i,0,n)rep(j,i+1,n)(path+=dfs(i,j,i))%=mod,
		maxlen=max(maxlen,l[i][j]+1);}
} 

// n^2
namespace cir_cover_max_vec{
vector<pair<db,int> > A;db a,t;int C,c;
void solve(db r,vector<vec> &v){
    C=sz(v)>0;
   	rep(i,0,sz(v)){
        A.clear();c=1;
        rep(j,0,sz(v))if(j!=i&&sgn(len1(v[i],v[j])-2.*r)<=0){
            if(v[i]==v[j]){c+=1;continue;}
            a=atan2(v[j].y-v[i].y,v[j].x-v[i].x);t=acos(.5*len1(v[i],v[j])/r);
            if(sgn(a-t+pi)>=0&&sgn(a+t-pi)<=0)A.pb(mp(a-t,1)),A.pb(mp(a+t,-1));
            else if(sgn(a-t+pi)<0)A.pb(mp(a-t+2.*pi,1)),A.pb(mp(-pi,1)),A.pb(mp(a+t,-1));
            else if(sgn(a+t-pi)>0)A.pb(mp(a-t,1)),A.pb(mp(-pi,1)),A.pb(mp(a+t-2.*pi,-1));}
        sort(all(A),[](pair<db,int> x,pair<db,int> y){
            return sgn(x.fi-y.fi)<0||(sgn(x.fi-y.fi)==0&&x.se>y.se);});
        rep(j,0,sz(A))c+=A[j].se,C=max(C,c);}}
} 

db max_area_tri(vector<vec> v,vec& a,vec& b,vec& c){//in convex hull
	db A=0.;if(sz(v)<3)return 0.;
	rep(i,0,sz(v))for(int j=(i+1)%sz(v),k=(j+1)%sz(v);j!=i;(j+=1)%=sz(v)){
		while(fabs(area(v[i],v[j],v[(k+1)%sz(v)]))>
				fabs(area(v[i],v[j],v[k])))(k+=1)%=sz(v);
		if(Max(A,fabs(area(v[i],v[j],v[k]))))a=v[i],b=v[j],c=v[k];}
	reverse(all(v));
	rep(i,0,sz(v))for(int j=(i+1)%sz(v),k=(j+1)%sz(v);j!=i;(j+=1)%=sz(v)){
		while(fabs(area(v[i],v[j],v[(k+1)%sz(v)]))>
				fabs(area(v[i],v[j],v[k])))(k+=1)%=sz(v);
		if(Max(A,fabs(area(v[i],v[j],v[k]))))a=v[i],b=v[j],c=v[k];}
	return A;}

db nearest_pair(int l,int r,vector<vec> &v){
    if(l==r)return infd;
    int m=(l+r)>>1;db x=v[m].x;vector<vec> p;
    db sol=min(nearest_pair(l,m,v),nearest_pair(m+1,r,v));
    inplace_merge(v.begin()+l,v.begin()+m+1,v.begin()+r+1,[](vec a,vec b){return a.y<b.y;});
    rep(i,l,r+1)if(fabs(v[i].x-x)<=sol)p.pb(v[i]);
    rep(i,0,sz(p))rep(j,i+1,min(i+9,sz(p)))sol=min(sol,(p[i]-p[j]).len);
    return sol;}

db nearest_pair(vector<vec> v){
    sort(all(v),[](vec a,vec b){return a.x<b.x;});
    return nearest_pair(0,sz(v)-1,v);}

db get_area(db r, vec a, vec b) {
    db la=max(a.len,b.len),li=min(a.len,b.len),l=len1(a,b);
    if(!sgn(la)||!sgn(li)||!sgn(l))return 0.;
    db t=acos((a*b)/(la*li)),d=fabs(a^b)/l,it,ot;vec c=b-a;
    if(d>=r)return .5*r*r*t;if(la<=r)return .5*la*li*sin(t);
    if(li<=r){
        ot=acos(d/la)-acos(d/r),it=t-ot;
        return .5*r*(r*ot+li*sin(it));}
    if(sgn((a*c)*(b*c))<0){
       	it= 2.*acos(d/r),ot=t-it;
        return .5*r*r*(ot+sin(it));}
    return .5*r*r*t;}

// be careful with precision
db intersection_area(cir c,vector<vec> p){
    db area=0;
    rep(i,0,sz(p))p[i]=p[i]-c.o;
    rep(i,0,sz(p))area+=sgn(p[i]^p[(i+1)%sz(p)])*get_area(c.r,p[i],p[(i+1)%sz(p)]);
    return fabs(area);}

db union_area(vector<cir> c){
    sort(all(c),[](cir a,cir b){return a.r>b.r;});
    vector<cir> z;vector<vec> v;vector<pair<db, db> > itv;
    bool cover;db d, a, ta, sa, ea, area= 0.;vec t;
    rep(i,0,sz(c)){
        cover= false;
        rep(j,0,sz(z))if(z[j].in(c[i])){cover=true;break;}
        if(!cover) z.pb(c[i]);}
    rep(i,0,sz(z)){
        itv.clear();
        rep(j,0,sz(z)){
            t=z[j].o-z[i].o;d=t.len;a=t.ang;
            if(j!=i&&sgn(d-(z[i].r+z[j].r))<0){
                ta=arc(z[i].r,d,z[j].r);sa=a-ta;ea=a+ta;
                if(sa<-pi)itv.pb(mp(sa+2.*pi,+pi));
				if(ea>+pi)itv.pb(mp(-pi,ea-2.*pi));
               	itv.pb(mp(max(-pi, sa), min(pi, ea)));}}
        if(!sz(itv)){area+=pi*z[i].r*z[i].r;continue;}
        sort(all(itv));itv.pb(mp(itv[0].fi+2.*pi,itv[0].se+2.* pi));
        rep(j,0,sz(itv)-1){
           	if(sgn(itv[j+1].fi-itv[j].se)>0)
                area+=seg(itv[j+1].fi-itv[j].se,z[i].r),
               	area+=.5*((z[i].o+vec(itv[j].se,z[i].r,0))^(z[i].o+vec(itv[j+1].fi,z[i].r,0)));
         	else itv[j+1].fi=itv[j].fi,itv[j+1].se=max(itv[j+1].se,itv[j].se);}}
    return area;}

// 0 line | 1 cir | z=base a=ori
int inverse(cir &z,cir &a,cir &b,line &l){
    vec s,t;
    if(!sgn((z.o-a.o).len-z.r)){
       	s=z.o+(a.o-z.o).trunc(.5*sq(z.r)/a.r);t=s+(~(a.o-z.o));l=line(s,t);return 0;}
    s=t=a.o-z.o;s=s.trunc(s.len+a.r);t=t.trunc(t.len-a.r);
    s=z.o+s.trunc(sq(z.r)/s.len);t=z.o+t.trunc(sq(z.r)/t.len);
    b=cir((s+t)*.5,.5*(s-t).len);return 1;}

// no collinear
vec circum_center(vec a,vec b,vec c){
    mat d= {{a.x,a.y,1},{b.x,b.y,1.},{c.x,c.y,1.}};
    mat x= {{sq(a.x)+sq(a.y),a.y,1.},{sq(b.x)+sq(b.y),b.y,1.},{sq(c.x)+sq(c.y),c.y,1.}};
    mat y= {{a.x,sq(a.x)+sq(a.y),1.},{b.x,sq(b.x)+sq(b.y),1.},{c.x,sq(c.x)+sq(c.y),1.}};
   	return vec(det(x),det(y))/(2.*det(d));}

vec incircle_center(vec a,vec b,vec c){
    db A=len1(b,c),B=len1(a,c),C=len1(a,b);
    return (a*A+b*B+c*C)/(A+B+C);}

vec ortho_center(vec a,vec b,vec c){
    mat d={{a.x,a.y,1.},{b.x,b.y,1.},{c.x,c.y,1.}};
    mat x={{b*c,1.,a.y},{c*a,1.,b.y},{a*b,1.,c.y}};
   	mat y={{b*c,a.x,1.},{c*a,b.x,1.},{a*b,c.x,1.}};
    return vec(det(x),det(y))/(2.*det(d));}

vec centroid(vector<vec> v){
    db a=0.,cx=0.,cy=0.;
    rep(i,0,sz(v)){
        a+=v[i]^v[(i+1)%sz(v)];
        cx+=(v[i].x+v[(i+1)%sz(v)].x)*(v[i]^v[(i+1)%sz(v)]);
        cy+=(v[i].y+v[(i+1)%sz(v)].y)*(v[i]^v[(i+1)%sz(v)]);}
    a=3.*fabsl(a);return vec(cx,cy)/a;}

// o(n)

cir min_circle_cover(vector<vec> v){
	discrete(v);random_shuffle(all(v));
	return cir(0,0,0);}


db cirs_cover_arc(vector<cir> v,cir c){
	vector<vec> t;vec s;db a1,a2,l=0.;vector<pdd>p;
	rep(i,0,sz(v)){
		if(v[i].in(c))return 0.;
		if(c.in(v[i])||c.out(v[i]))continue;
		intersect_point(c,v[i],t);
		a1=ang1(t[0],c.o);a2=ang1(t[1],c.o);if(a1>a2)swap(a1,a2);
		s=c.o+vec((a1+a2)*.5,c.r,0);
		if(sgn(len2(s,v[i].o)-sq(v[i].r))<=0)p.pb(mp(a1,a2));
		else p.pb(mp(-pi,a1)),p.pb(mp(a2,+pi));}
	if(!sz(p))return 2.*pi*c.r;
	auto cmp=[&](pdd &a,pdd &b){return sgn(b.fi-a.se)>0?0:(Max(a.se,b.se),1);};
	sort(all(p));p.erase(unique(all(p),cmp),p.end());
	l+=c.r*(p[0].fi+pi);l+=c.r*(pi-p[sz(p)-1].se);
	rep(i,0,sz(p)-1)l+=c.r*(p[i+1].fi-p[i].se);
	return l;}

// left area|add boarder when necessary
// vec z=vec(1e10,1e10);rep(i,0,4)l.pb(line(z,z.rot(.5*pi))),z=z.rot(.5*pi);
vector<vec> half_plane_intersection(vector<line> l) {
    deque<vec> c;deque<line> q;vector<vec> v;discrete(l);
    rep(i,0,sz(l)){
        while(sz(c)&&l[i].pos(c.bk)<0)c.pbk(),q.pbk();
        while(sz(c)&&l[i].pos(c.ft)<0)c.pft(),q.pft();
       	if(sz(q))c.pb(isp(q.bk,l[i]));q.pb(l[i]);}
    while(sz(c)&&q.bk.pos(c.ft)<0)c.pft(),q.pft();
    while(sz(c)&&q.ft.pos(c.bk)<0)c.pbk(),q.pbk();
    if(sz(q)<3)return v;c.pb(isp(q.ft,q.bk));
    rep(i,0,sz(c))if(!sz(v)||!(c[i]==v.bk))v.pb(c[i]);
    if(v.ft==v.bk)v.pbk();return v;}

bool in_circumcircle(vec a,vec b,vec c,vec d){
#define X(a,b) (a.x-b.x)
#define Y(a,b) (a.y-b.y)
#define Z(a,b) (sq(a.x)+sq(a.y)-sq(b.x)-sq(b.y))
    if(sgn((a^b)+(b^c)+(c^a))>0)swap(a,c);
   	return sgn(	(Y(a,d)*Z(b,d)-Z(a,d)*Y(b,d))*X(c,d)+
				(Z(a,d)*X(b,d)-X(a,d)*Z(b,d))*Y(c,d)+
				(X(a,d)*Y(b,d)-Y(a,d)*X(b,d))*Z(c,d))<=0;}

// make sure out,r>0|point to cir||
int p_tangent(cir a,vec v,vector<line> &l){
    db t=acos(a.r/len1(a.o,v));l.clear();
    if(!sgn(t)){l.pb(line(v,v+~(a.o-v)));return 1;}
    l.pb(line(v,a.o+(v-a.o).trunc(a.r).rot(+t)));
    l.pb(line(v,a.o+(v-a.o).trunc(a.r).rot(-t)));
    return 2;}

int x_tangent(cir a, cir b, vector<line> &l) {
    db k=len2(a.o,b.o)-sq(a.r+b.r);l.clear();
    if(sgn(k)<0)return 0;
    if(sgn(k)==0){
        vec c=a.o+(b.o-a.o).trunc(a.r);l.pb(line(c,c+~(b.o-a.o)));return 1;}
    db t=acos((a.r+b.r)/len1(a.o,b.o));
   	l.pb(line(a.o+(b.o-a.o).trunc(a.r).rot(+t),b.o+(a.o-b.o).trunc(b.r).rot(+t)));
 	l.pb(line(a.o+(b.o-a.o).trunc(a.r).rot(-t),b.o+(a.o-b.o).trunc(b.r).rot(-t)));
 	return 2;}

int a_tangent(cir a,cir b,vector<line> &l){
    db k=len2(a.o,b.o)-sq(a.r-b.r);l.clear();
    if(sgn(k)<0)return 0;if(a.r>b.r)swap(a, b);
    if(!sgn(k)){
        if(!sgn(a.r-b.r))return -1;
        vec c=a.o+(a.o-b.o).trunc(a.r);l.pb(line(c,c+~(a.o-b.o)));
		return 1;}
    if(!sgn(a.r-b.r)){
        vec d=~(a.o-b.o).trunc(a.r);
      	l.pb(line(a.o+d,b.o+d));l.pb(line(a.o-d,b.o-d));
        return 2;}
    db d=len1(a.o,b.o),t=acos((b.r-a.r)/d);
    l.pb(line(a.o+(a.o-b.o).trunc(a.r).rot(+t),b.o+(a.o-b.o).trunc(b.r).rot(+t)));
	l.pb(line(a.o+(a.o-b.o).trunc(a.r).rot(-t),b.o+(a.o-b.o).trunc(b.r).rot(-t)));
 	return 2;}

vec fermat_point(vector<vec> v){
    random_device rd;mt19937 gen(rd());
    uniform_real_distribution<double> dis(0, 1), ang(0, 2. * pi);
    db tp=1e4;vec s0,s1,best;db e0,e1,eb,g;
    auto E=[&](vec &z){db d=0;for(auto p:v)d+=len1(z,p);return d;};
    auto neighbour=[&](vec &z,db step){return z+vec(ang(gen),step*dis(gen),0);};
    s0=accumulate(all(v),vec(0,0))/sz(v);eb=e0=E(best=s0);
    for(db t=tp;t>1;t*=0.9999){
        g=t/tp;s1=neighbour(s0,e0/sz(v)*g);e1=E(s1);
       	if(e1<e0||exp((e0-e1)/t)>=dis(gen))s0=s1;
        if(e1<eb)eb=e1,best=s1;}
    return best;}

} // namespace D2

namespace D3{

struct vec{vec(){}
    vec(int o){cin>>x>>y>>z;len=hypot(hypot(x,y),z);t=0.;
        if(sgn(len))t=acos(z/len);p=atan2(y, x);}
    vec(db X,db Y,db Z):x(X),y(Y),z(Z),len(hypot(hypot(X,Y),Z)){
        t=0.;if(sgn(len))t=acos(z/len);p=atan2(y,x);}
    vec(db T,db P,db R,int o):x(R*sin(T)*cos(P)),y(R*sin(T)*sin(P)),z(R*cos(T)),len(R),t(T),p(P){};
    vec norm();vec trunc(db);vec rot(vec, db);db cen_ang(vec);db x,y,z,len,t,p;};

vec operator-(vec a){return vec(-a.x,-a.y,-a.z);}
vec operator+(vec a, vec b){return vec(a.x+b.x,a.y+b.y,a.z+b.z);}
vec operator-(vec a, vec b){return vec(a.x-b.x,a.y-b.y,a.z-b.z);}
// counter,len=sin(t)
vec operator^(vec a,vec b){
    return vec(a.y*b.z-a.z*b.y,a.z*b.x-a.x*b.z,a.x*b.y-a.y*b.x);}
vec operator*(vec a, db b){return vec(a.x*b,a.y*b,a.z*b);}
vec operator/(vec a, db b){return vec(a.x/b,a.y/b,a.z/b);}
db operator*(vec a, vec b){return a.x*b.x+a.y*b.y+a.z*b.z;}
bool operator<(vec a, vec b){
    return sgn(a.x-b.x)<0||(!sgn(a.x-b.x)&&sgn(a.y-b.y)<0)||(!sgn(a.x-b.x)&&!sgn(a.y-b.y)&&sgn(a.z-b.z)<0);}
bool operator==(vec a, vec b) {return !sgn(a.x-b.x)&&!sgn(a.y-b.y)&&!sgn(a.z-b.z);}
vec vec::norm(){assert(sgn(len));return vec(x/len,y/len,z/len);}
vec vec::trunc(db l){assert(sgn(len));return *this*(l/len);}
// k is norm|counter
vec vec::rot(vec k,db t){return (*this)*cos(t)+(k^(*this))*sin(t)+k*(k*(*this))*(1.-cos(t));}
db vec::cen_ang(vec v){return acos(cos(t)*cos(v.t)+sin(t)*sin(v.t)*cos(fabs(p-v.p)));}

inline db dv(vec a,vec b,vec c,vec d){return ((a-d)^(b-d))*(c-d);}
inline db len1(vec a,vec b){return hypot(fabs(a.x-b.x),hypot(fabs(a.y-b.y),fabs(a.z-b.z)));}
inline db len2(vec a, vec b){return sq(a.x-b.x)+sq(a.y-b.y)+sq(a.z-b.z);}
inline bool up_seg(vec s,vec t,vec p){return sgn((t-s)*(p-s))>=0&&sgn((s-t)*(p-t))>=0;}
inline bool on_seg(vec s,vec t,vec p){return !sgn(((s-p)^(t-p)).len)&&sgn((s-p)*(t-p))<1;}

vec operator*(mat a,vec b){ // 4*4
    return vec(a[0][0]*b.x+a[0][1]*b.y+a[0][2]*b.z+a[0][3],
               a[1][0]*b.x+a[1][1]*b.y+a[1][2]*b.z+a[1][3],
			   a[2][0]*b.x+a[2][1]*b.y+a[2][2]*b.z+a[2][3]);}

mat trans_mat(db dx,db dy,db dz){ //(x,y,z)->(x+dx,y+dy,z+dz)
    return {{1,0,0,dx},{0,1,0,dy},{0,0,1,dz},{0,0,0,1}};}

mat scale_mat(db a,db b,db c) { //(x,y,z)>->(ax,by,cz)
    return {{a,0,0,0},{0,b,0,0},{0,0,c,0},{0,0,0,1}};}

mat rot_mat(db x,db y,db z,db t){ // rot t with(x,y,z)|counter
    db d=sqrt(sq(x)+sq(y)+sq(z)),s=sin(t),c=cos(t);x/=d;y/=d;z/=d;
    return {{c+(1-c)*sq(x),(1-c)*x*y-s*z,(1-c)*x*z+s*y,0},
            {(1-c)*y*x+s*z,c+(1-c)*sq(y),(1-c)*y*z-s*x,0},
			{(1-c)*z*x-s*y,(1-c)*z*y+s*x,c+(1-c)*sq(z),0},
			{0,0,0,1}};}

struct line{line(){}
    line(vec a,vec b):s(a),t(b),d(b-a),n(d.norm()){}
   	bool cop(line l){return !sgn((d^(l.t-s))*(l.s-s));}
    db dis(vec p){return ((s-p)^(t-p)).len/d.len;}
    db dis(line p){return sgn((d^p.d).len)?fabs((s-p.s)*(d^p.d).norm()):((p.s-s)^n).len;}
    vec proj(vec p){return p+(d^((s-p)^(t-p)))/d.len;}
    bool on(vec p){return !sgn(dis(p))&&sgn((s-p)*(t-p))!=1;}
    vec s,t,d,n;};

struct plane{plane(){}
    plane(vec A,vec B,vec C):a(A),b(B),c(C){d=((B-A)^(C-A)).norm();h=d*a;} //(p-a)*d=0
    plane(vec A,vec P):a(A),d(P.norm()),h(P.norm()*A){
        vector<vec> v;
        if(sgn(d.x))v.pb(vec(h/d.x,0.,0.));else v.pb(vec(A.x-1.,A.y,A.z));
        if(sgn(d.y))v.pb(vec(0.,h/d.y,0.));else v.pb(vec(A.x,A.y-1.,A.z));
        if(sgn(d.z))v.pb(vec(0.,0.,h/d.z));else v.pb(vec(A.x,A.y,A.z-1.));
        rep(i,0,2)if(v[i]==A)swap(v[i],v[2]);
        b=v[0];c=v[1];}
    int pos(vec p){return sgn(((a-p)^(b-p))*(c-p));}
    db dis(vec p){return fabs(((a-p)^(b-p))*(c-p))/((b-a)^(c-a)).len;}
    vec proj(vec p) {return p+d*(((a-p)^(b-p))*(c-p)/((b-a)^(c-a)).len);}
    bool on(vec p){
        return p==a||p==b||p==c||(!sgn(dv(a,b,c,p))&&1<abs(
        sgn(((a-p)^(b-p))*d)+sgn(((b-p)^(c-p))*d)+sgn(((c-p)^(a-p))*d)));}
    vec a,b,c,d;db h;};

struct sphere{sphere(){}
    sphere(db X,db Y,db Z,db R):x(X),y(Y),z(Z),r(R),vol(4.*pi*R*R*R/3.),area(4.*pi*R*R),o(vec(X,Y,Z)){}
    sphere(vec O,db R):x(O.x),y(O.y),z(O.z),r(R),vol(4.*pi*R*R*R/3.),area(4.*pi*R*R),o(O){}
    db cap_vol(db h){return pi*h*h*(3.*r-h)/3.;}
    db cap_area(db h){return 2.*pi*r*h;} // base area not include
    db int_r(sphere s){
        db d=len1(o,s.o);
        if(sgn(d-(r+s.r))>=0||sgn(d-fabs(r-s.r))<=0)return 0.;
        return .5*sqrt((-d+r-s.r)*(-d-r+s.r)*(-d+r+s.r)*(d+r+s.r))/d;}
    db x,y,z,r,vol,area;vec o;};

//-1 inf|0 no|1 one
int intersect_point(plane p, line l, vec &v) {
    if(!sgn(p.d*l.n))return p.pos(l.s)?0:-1;
    db d=((p.a-l.s)*p.d)/(p.d*l.n);
    v=l.s+l.n*d;return 1;}

int intersect_point(line p,line q,vec &v){// proj vec on p when not cop|-1 inf
    if(!sgn((p.d^q.d).len))return sgn(p.dis(q.s))?0:-1;
    vec z=q.d^p.d;db k=(((p.s-q.s)^q.d)*z)/(z*z);
    v=p.s+p.d*k;return 1;}

int intersect_line(plane p,plane q,line &l){
    if(!sgn(1.-sq(p.d*q.d))){
        if(!sgn(p.dis(q.a)))return -1;return 0;}
    db cp=(p.h-q.h*(p.d*q.d))/(1.-sq(p.d*q.d));
    db cq=(q.h-p.h*(p.d*q.d))/(1.-sq(p.d*q.d));
    vec o=(p.d*cp)+(q.d*cq),d=p.d^q.d;l=line(o,o+d);return 1;}

db llmd(line p,line q){
    db d=min(min(len1(p.s,q.s),len1(p.s,q.t)),min(len1(p.t,q.s),len1(p.t,q.t)));
    if(up_seg(p.s,p.t,q.s))d=min(d,fabs(p.dis(q.s)));
    if(up_seg(p.s,p.t,q.t))d=min(d,fabs(p.dis(q.t)));
    if(up_seg(q.s,q.t,p.s))d=min(d,fabs(q.dis(p.s)));
    if(up_seg(q.s,q.t,p.t))d=min(d,fabs(q.dis(p.t)));
    if(!sgn((p.d^q.d).len)){
        vec a,b;intersect_point(p, q, a);intersect_point(q, p, b);
        if(p.on(a)&&q.on(b))d=min(d,len1(a,b));}return d;}

bool in_plane_strict(vector<vec> &v,vec p){ // sz>=3|strict in
    if(sgn(((p-v[0])^(p-v[1]))*(p-v[2])))return 0;
    int c=0;vec a,b,n=((v[1]-v[0])^(v[2]-v[0])).norm();
    rep(i,0,sz(v)){
        c+=sgn(((v[i]-p)^(v[(i+1)%sz(v)]-p))*n);
        if(abs(c)!=i+1)return 0;}return 1;}

bool in_plane_all(vector<vec> &v,vec p) { // sz>=3|border include
    if(sgn(((p-v[0])^(p-v[1]))*(p-v[2])))return 0;
    int c=0;vec n=((v[1]-v[0])^(v[2]-v[0])).norm();
    rep(i,0,sz(v)){
        c+=sgn(((v[i]-p)^(v[(i+1)%sz(v)]-p))*n);
        if(abs(c)!=i+1)return line(v[i],v[(i+1)%sz(v)]).on(p);}
    return 1;}

vec circum_center(vec a,vec b,vec c){ // no collinear
    vec ca=c-a,ba=b-a;
    return a+(((ba^ca)^ba)*sq(ca)+(ca^(ba^ca))*sq(ba))/(2.*sq(ba^ca));}

vec circum_center(vec v0, vec v1, vec v2, vec v3) { // no cop
    vec u1=v1-v0,u2=v2-v0,u3=v3-v0;
    return v0+((u2^u3)*len2(v0,v1)+(u3^u1)*len2(v0,v2)+(u1^u2)*len2(v0,v3))/(2.*(u1*(u2^u3)));}

namespace convex_hull_static {
const int maxn= 10000;
vector<vec> v;int cnt;map<int,map<int,int> > E;set<int> I;
struct face {
    int d[3];
    int pos(int p){return sgn(dv(v[d[0]],v[d[1]],v[d[2]],v[p]));}
    vec norm(){return ((v[d[1]]-v[d[0]])^(v[d[2]]-v[d[0]])).norm();}
}F[maxn];
int cal(){vector<vec>z;for(auto i:I)z.pb(F[i].norm());discrete(z);return sz(z);}
void add(vector<int> a,int id){I.insert(id);rep(i,0,3)F[id].d[i]=a[i],E[a[i]][a[(i+1)%3]]=id;}
int del(int o,int p){
    if(F[o].pos(p)<1)return 1;
    rep(i,0,3)E[F[o].d[i]].erase(F[o].d[(i+1)%3]);
    rep(i,0,3){
        int a=F[o].d[(i+1)%3],b=F[o].d[i];
        if(E[a].count(b)&&del(E[a][b],p))add({b,a,p},cnt++);}
    I.erase(o);return 0;}
int add(int p){for(auto i:I)if(F[i].pos(p)>0)return del(i,p);return 0;}
bool find(){
    rep(i,2,sz(v))if(sgn(((v[0]-v[i])^(v[1]-v[i])).len)){
        swap(v[i],v[2]);
        rep(j,i+1,sz(v))if(sgn(dv(v[0],v[1],v[2],v[j]))){swap(v[j], v[3]);return 1;}}
    return 0;}
void init(vector<vec> &V){
    int p,s;cnt=1;I.clear();E.clear();v=V;
    discrete(v);random_shuffle(all(v));if(!find())return;
    rep(i,0,4)rep(j,i+1,4)rep(k,j+1,4){
        p=6-i-j-k;s=sgn(dv(v[i],v[j],v[k],v[p]))<0;
        add({i,s?j:k,s?k:j},cnt++);}
    rep(i,4,sz(v))add(i);}
}

namespace convex_hull {
struct face{face(){}
    face(vec a,vec b,vec c){d[0]=a,d[1]=b,d[2]=c;};
    vec d[3];};
map<pair<vec,vec>,face*>e;set<face*> fs;
int cal(){
    vector<vec> z;
    for(auto fp:fs)z.pb(((fp->d[1]-fp->d[0])^(fp->d[2]-fp->d[0])).norm());
    discrete(z);return sz(z);}
void ins(vec &v) {
    face *a,*b;vector<pair<vec,vec> >del;vector<face*>add;
    for(auto vp:e){
        a=vp.se;b=e[mp(vp.fi.se,vp.fi.fi)];
        if(sgn(dv(a->d[0],a->d[1],a->d[2],v))>0){
            del.pb(vp.fi);fs.erase(a);
            if(sgn(dv(b->d[0],b->d[1],b->d[2],v)<=0))
                add.pb(new face(vp.fi.fi,vp.fi.se,v));}}
    for(auto vp:del)e.erase(vp);
    for(auto fp:add){
        fs.insert(fp);
        e[mp(fp->d[0],fp->d[1])]=e[mp(fp->d[1],fp->d[2])]=e[mp(fp->d[2],fp->d[0])]=fp;}}
void init(vector<vec> v){
    int z,t;face *f;
    random_shuffle(all(v));e.clear();fs.clear();
    rep(i,3,sz(v))if(sgn(dv(v[0],v[1],v[2],v[i]))){swap(v[3], v[i]);break;}
    rep(i,0,4)rep(j,i+1,4)rep(k,j+1,4){
        z=6-i-j-k;t=sgn(dv(v[i],v[j],v[k],v[z]))<0;
        fs.insert(f=new face(v[i],t?v[j]:v[k],t?v[k]:v[j]));
        e[mp(f->d[0],f->d[1])]=e[mp(f->d[1],f->d[2])]=e[mp(f->d[2],f->d[0])]=f;}
    rep(i,4,sz(v))ins(v[i]);}
}

sphere min_ball_cover_sa(vector<vec> v){
    random_device rd;mt19937 gen(rd());
    uniform_real_distribution<double> dis(0,1);
    vec s0,s1,best;db tp=10,e0,e1,eb;
    auto E=[&](vec &z){db d=0;for(auto p:v)d=max(d,len2(z,p));return sqrt(d);};
    auto neighbour=[&](vec &z,db step){
    	db d2=0;vec t;for(auto p:v)if(d2<len2(z,p))t=p,d2=len2(z,p);return z+(t-z).trunc(step);};
    eb=e0=E(best=s0=accumulate(all(v),vec(0,0,0))/sz(v));
    for(db t=tp;t>1e-10;t*=0.9999){
        e1=E(s1=neighbour(s0,t));
        if(e1<e0||exp((e0-e1)/t)>=dis(gen))s0=s1;
        if(e1<eb)eb=e1,best=s1;}
    return sphere(best,eb);}

} // namespace D3

int main()
{
	
}
