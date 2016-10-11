#include<bits/stdc++.h>
using namespace std;

#define maxn 500000

struct SAM
{
    SAM(){};
    int root,last,cnt;
    int len[maxn],trans[maxn][26],par[maxn];
    void init()
    {
        memset(len,0,sizeof(len));
        memset(trans,0,sizeof(trans));
        memset(par,0,sizeof(par));
        root=1;cnt=2;
    }
    void insert(char str[])
    {
        last=root;
        for(int i=0;str[i];++i)extend(str[i]-'a');
    }
    void extend(int c)
    {
        int p=last,np=cnt++,q,nq;
        for(len[np]=len[p]+1;p&&!trans[p][c];trans[p][c]=np,p=par[p]);
        if(!p)par[np]=root;
        else
        {
            q=trans[p][c];
            if(len[q]==len[p]+1)par[np]=q;
            else
            {
                nq=cnt++;len[nq]=len[p]+1;
                memcpy(trans[nq],trans[q],sizeof(trans[q]));
                par[nq]=par[q];par[q]=par[np]=nq;
                for(;p&&trans[p][c]==q;trans[p][c]=nq,p=par[p]);
            }
        }
        last=np;
    }
};

int main(){};
