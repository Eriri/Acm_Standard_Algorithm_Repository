#include<bits/stdc++.h>
using namespace std;

struct treap
{
	treap(){lr[0]=lr[1]=NULL;};
	treap(int v):val(v),key(rand()),size(1){lr[0]=lr[1]=NULL;};
	int val,key,size;
	void update(){size=1+(lr[0]?lr[0]->size:0)+(lr[1]?lr[1]->size:0);};
	treap* lr[2];
}*root;

treap* build(int a[],int size)
{
	stack<treap*> s;treap *node,*t;
	sort(a,a+size);
	for(int i=0;i<size;++i,s.push(node))
	{
		for(node=new treap(a[i]),t=NULL;!s.empty();t=s.top(),s.pop())
		{
			if(s.top()->key>node->key)s.top()->update();
			else
			{
				node->lr[0]=s.top()->lr[1];node->update();
				s.top()->lr[1]=node;s.top()->update();break;
			}
		}
		node->lr[0]=t;node->update();
	}
	for(;!s.empty();s.pop()){root=s.top();root->update();}
	return root;
}

struct rs{rs(treap* a,treap* b){pair[0]=a;pair[1]=b;};treap* pair[2];};

int size(treap* t){return t?t->size:0;}

rs split(treap* t,int k)
{
	if(!t)return rs(NULL,NULL);
	int d=(size(t->lr[0])>=k);
	k-=(d?0:size(t->lr[0])+1);
	rs r=split(t->lr[d^1],k);
	t->lr[d^1]=r.pair[d];t->update();r.pair[d]=t;
	return r;
}

treap* merge(rs r)
{
	if(!r.pair[0])return r.pair[1];
	if(!r.pair[1])return r.pair[0];
	int d=r.pair[0]->key<r.pair[1]->key;
	if(d)r.pair[d^1]->lr[d]=merge(rs(r.pair[d^1]->lr[d],r.pair[d]));
	else r.pair[d^1]->lr[d]=merge(rs(r.pair[d],r.pair[d^1]->lr[d]));
	r.pair[d^1]->update();
	return r.pair[d^1];
}

int find(int k)
{
	rs L=split(root,k-1);
	rs R=split(L.pair[1],1);
	int ans=R.pair[0]?R.pair[0]->val:-1;
	root=merge(rs(L.pair[0],merge(R)));	
	return ans;
}

int get(treap* n,int v)
{
	if(!n)return 0;
	return (v<=n->val)?get(n->lr[0],v):(get(n->lr[1],v)+size(n->lr[0])+1);
}

void insert(int v)
{
	int k=get(root,v);treap* n=new treap(v);
	rs r=split(root,k);
	root=merge(rs(merge(rs(r.pair[0],n)),r.pair[1]));
}

void remove(int v)
{
	int k=get(root,v);
	rs L=split(root,k);rs R=split(L.pair[1],1);
	root=merge(rs(L.pair[0],R.pair[1]));
}

int main(){};
