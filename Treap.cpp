#include<bits/stdc++.h>
using namespace std;
#define maxn 10000

struct treap
{
    treap(){};
    treap(int k,int v,int s):key(k),val(v),sz(s){lr[0]=lr[1]=NULL;};
    int key,val,sz;
    treap* lr[2];
}*T[maxn];
void resize(treap* n)
{
    if(!n)return;
    int sz=0;
    if(n->lr[0])sz+=n->lr[0]->sz;
    if(n->lr[1])sz+=n->lr[1]->sz;
    n->sz=sz+1;return;
}
treap* rotate(treap* n,int d)//0->left:root=new root->right;
{
    treap* t=n->lr[d];
    n->lr[d]=t->lr[d^1];t->lr[d^1]=n;
    resize(n);resize(t);return t;
}
treap* maintain(treap* n)
{
    if(n->lr[0]&&n->lr[0]->val<n->val)n=rotate(n,0);
    if(n->lr[1]&&n->lr[1]->val<n->val)n=rotate(n,1);
    resize(n);return n;
}
treap* insert(int key,int val,treap* n)
{
    if(n->lr[key>n->key])
		n->lr[key>n->key]=insert(key,val,n->lr[key>n->key]);
    else n->lr[key>n->key]=new treap(key,val,1);
    return n=maintain(n);
}
treap* remove(int key,treap* n)
{
    if(n->key>key)n->lr[0]=remove(key,n->lr[0]);
    else if(n->key<key)n->lr[1]=remove(key,n->lr[1]);
    else
    {
        if(!n->lr[0]&&!n->lr[1])n=NULL;
        else if(n->lr[0]&&!n->lr[1])n=n->lr[0];
        else if(!n->lr[0]&&n->lr[1])n=n->lr[1];
        else{
            n=rotate(n,0);
            n->lr[1]=remove(key,n->lr[1]);
        }
    }
    resize(n);return n;
}

int main(){};
