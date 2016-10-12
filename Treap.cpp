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
void resize(treap* node)
{
    if(!node)return;
    int sz=0;
    if(node->lr[0])sz+=node->lr[0]->sz;
    if(node->lr[1])sz+=node->lr[1]->sz;
    node->sz=sz+1;return;
}
treap* rotate(treap* node,int d)//0->left:root=new root->right;
{
    treap* t=node->lr[d];
    node->lr[d]=t->lr[d^1];t->lr[d^1]=node;
    resize(node);resize(t);return t;
}
treap* maintain(treap* node)
{
    if(node->lr[0]&&node->lr[0]->val<node->val)node=rotate(node,0);
    if(node->lr[1]&&node->lr[1]->val<node->val)node=rotate(node,1);
    resize(node);return node;
}
treap* insert(int key,int val,treap* node)
{
    if(node->lr[key>node->key])
		node->lr[key>node->key]=insert(key,val,node->lr[key>node->key]);
    else node->lr[key>node->key]=new treap(key,val,1);
    return node=maintain(node);
}
treap* remove(int key,treap* node)
{
    if(node->key>key)node->lr[0]=remove(key,node->lr[0]);
    else if(node->key<key)node->lr[1]=remove(key,node->lr[1]);
    else
    {
        if(!node->lr[0]&&!node->lr[1])node=NULL;
        else if(node->lr[0]&&!node->lr[1])node=node->lr[0];
        else if(!node->lr[0]&&node->lr[1])node=node->lr[1];
        else{
            node=rotate(node,0);
            node->lr[1]=remove(key,node->lr[1]);
        }
    }
    resize(node);return node;
}

int main(){};
