#include<bits/stdc++.h>
using namespace std;

#define maxn 10000
#define maxm 10000
const int inf=0x3f3f3f3f;

template<class T>
struct isap
{
    isap(){};
    int cnt,u,v,e,s,t,d,N[maxn],now[maxn],dpth[maxn],vtn[maxn],pre[maxn];
    int vt[maxm],ne[maxm];T cap[maxm];
    T maxflow,tflow;
    void init(int _s,int _t,int _d){s=_s;t=_t;d=_d;cnt=2;maxflow=0;memset(N,0,sizeof(N));};
    void link(int u,int v,T c){vt[cnt]=v;ne[cnt]=N[u];cap[cnt]=c;now[u]=N[u]=cnt++;}
    void build(int u,int v,T c){link(u,v,c);link(v,u,0);}
    T run()
    {
        memset(dpth,0,sizeof(dpth));memset(vtn,0,sizeof(vtn));vtn[0]=d;
        for(u=s;dpth[s]<d;)
        {
            if(u==t)
            {
                for(v=s,tflow=inf;v!=t;tflow=min(cap[now[v]],tflow),v=vt[now[v]]);
                for(v=s;v!=t;v=vt[now[v]]){cap[now[v]]-=tflow;cap[now[v]^1]+=tflow;}
                u=s;maxflow+=tflow;
            }
            else
            {
                for(e=now[u];e;e=ne[e])if(cap[e]>0&&dpth[vt[e]]+1==dpth[u])break;
                if(e){now[u]=e;pre[vt[e]]=u;u=vt[e];}
                else
                {
                    if(--vtn[dpth[u]]==0)break;
                    for(e=N[u],v=d;e;e=ne[e])if(cap[e]>0)v=min(v,dpth[vt[e]]);
                    dpth[u]=v+1;++vtn[dpth[u]];now[u]=N[u]; 
                    if(u!=s)u=pre[u];
                }
            }
        }
        return maxflow;
    }
};

int main(){};
