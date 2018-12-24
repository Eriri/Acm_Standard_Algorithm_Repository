#include<bits/stdc++.h>
using namespace std;
#define rep(i,s,t) for(int i=(s);i<(t);++i)
#define per(i,s,t) for(int i=((t)-1);i>=(s);--i)
#define repb(i,s,t) for(int i=(s);i<=(t);++i)
#define lepb(i,s,t) for(int i=(t);i>=(s);--i)
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define sz(x) ((int)x.size())
#define mst(a,b) memset(a,b,sizeof(a))
#define mcpy(des,sor) memcpy(des,sor,sizeof(sor))
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
const db pi = acosl(-1.0);
const ll mod = 1e9+7;

/*
struct TRIE{TRIE(){init();}
	int rt,cnt,ch[maxn][26],f[maxn];bool tag[maxn];
	void init(){mst(ch,0);mst(f,0);mst(tag,0);rt=0;cnt=1;}
	void insert(char str[]){
		int u=rt;
		for(int i=0;str[i];u=ch[u][str[i]-'a'],i++)
			if(!ch[u][str[i]-'a'])ch[u][str[i]-'a']=cnt++;
		tag[u]=true;}
	void build(){
		queue<int> q;int u;q.push(rt);f[rt]=maxn-1;
		while(!q.empty()){
			u=q.front();q.pop();tag[u]|=tag[f[u]];
			rep(i,0,26){
				if(!ch[u][i])ch[u][i]=ch[f[u]][i];
				else f[ch[u][i]]=ch[f[u]][i],q.push(ch[u][i]);}}}};

struct SAM{SAM(){init();}
    int rt,now,cnt,l[maxn],ch[maxn][26],f[maxn];
    void init(){mst(l,0);mst(ch,0);mst(f,0);rt=1;cnt=2;}
    void insert(char str[]){
    	now=rt;for(int i=0;str[i];++i)extend(str[i]-'a');}
	void extend(int c){
		int p=now,np=ch[p][c],q,nq;
		if(np){
        	if(l[np]==l[p]+1)now=np;
        	else{
        		l[nq=now=cnt++]=l[p]+1;f[nq]=f[np];f[np]=nq;
        		mcpy(ch[nq],ch[np]);while(ch[p][c]==np)ch[p][c]=nq,p=f[p];}}
		else{
			l[np=now=cnt++]=l[p]+1;
			while(!ch[p][c])ch[p][c]=np,p=f[p];
			if(!p)f[np]=rt;
			else{
				q=ch[p][c];
				if(l[q]==l[p]+1)f[np]=q;
				else{
					l[nq=cnt++]=l[p]+1;f[nq]=f[q];f[q]=f[np]=nq;
					mcpy(ch[nq],ch[q]);while(ch[p][c]==q)ch[p][c]=nq,p=f[p];}}}}
   void build(TRIE& t){
   	   queue<pii> q;bool v[maxn];int x,y,z;
   	   mst(v,0);q.push(mp(rt,t.rt));v[t.rt]=1;
   	   while(!q.empty()){
   	   	   x=q.front().fi;y=q.front().se;q.pop();
   	   	   rep(i,0,26)if(!v[z=t.ch[y][i]]){
   	   	   	   now=x;extend(i);q.push(mp(now,z));v[z]=1;}}}};

struct HASH{//233 377 919 123457
	HASH(){init();};
	ll b,m,v[maxn],d[maxn];
	void init(ll _b=233,ll _m=1e9+7,int n=maxn){
		b=_b;m=_m;v[0]=0;d[0]=1;rep(i,1,n)d[i]=d[i-1]*b%m;}
	void run(char s[]){
		for(int i=1;s[i];i++)v[i]=(v[i-1]*b%m+s[i])%m;}
	ll get(int l,int r){
		return (v[r]-v[l-1]*d[r-l+1]%m+m)%m;}};

struct SUFFIX_ARRAY{
	struct element{int i,k[2];}A[maxn],B[maxn];char S[maxn]; 
	int n,m,c[maxn],ra[maxn],sa[maxn],he[maxn];
	void construct(char str[],int len,int up){
		mst(ra,0);n=len;m=up;A[0].k[0]=A[0].k[1]=-1;
		repb(i,1,len)A[i].i=i,S[i]=A[i].k[0]=str[i],A[i].k[1]=0;
		radix_sort();
		for(int j=1;j<n;j<<=1){
			repb(i,1,n)A[i].i=i,A[i].k[0]=ra[i],A[i].k[1]=i+j<=n?ra[i+j]:0;
			radix_sort();}
		repb(i,1,n)sa[ra[i]]=i;}
	void radix_sort(){
		lepb(p,1,0){
			mst(c,0);
			repb(i,1,n)++c[A[i].k[p]];
			repb(i,1,m)c[i]+=c[i-1];
			lepb(i,n,1)B[c[A[i].k[p]]--]=A[i];	//stable
			repb(i,1,n)A[i]=B[i];}
		repb(i,1,n){
			ra[A[i].i]=ra[A[i-1].i];
			if(A[i].k[0]!=A[i-1].k[1]||A[i].k[1]!=A[i-1].k[1])ra[A[i].i]++;}}
	void calculate(){
		int h=0;
		for(int i=1;i<=n;he[ra[i++]]=h,h?h--:0)
			for(;S[i+h]==S[sa[ra[i]-1]+h];h++);}};

*/

int main()
{

}
