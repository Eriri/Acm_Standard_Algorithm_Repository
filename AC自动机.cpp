#include<bits/stdc++.h>
using namespace std;

struct node
{
    node():suc(0),fail(0){memset(next,0,sizeof(next));}
    node *next[26],*fail;//efficient when the sentence only contain 
    int suc;			 //letters of alphabet
}*root,*move,*facr;

deque<node*> q;

void insert_string(string s)
{
	move=root;
	for(int i=0;i<s.length();++i)
	{
		if(move->next[s[i]-'a']==NULL) move->next[s[i]-'a']=new node();
		move=move->next[s[i]-'a'];
	}
	++move->suc;
}

void inital_fail_pointer()
{
    for(int i=0;i<26;++i)
    {
        if(root->next[i]!=NULL)
        {
            root->next[i]->fail=root;
            q.push_back(root->next[i]);
        }
    }
}

void build_fail_pointer()
{
	bool flag;
    while(!q.empty())
    {
        move=q.front();
        q.pop_front();
        for(int i=0;i<26;++i)
        {
            if(move->next[i]!=NULL)
            {
                q.push_back(move->next[i]);
                facr=move->fail;
                flag=false;
                while(facr!=NULL)
                {
                    if(facr->next[i]!=NULL)
                    {
                        move->next[i]->fail=facr->next[i];
                        flag=true;
                        break;
                    }
                    facr=facr->fail;
                }
                if(!flag) move->next[i]->fail=root;
            }
        }
    }
}

int matchingword(string p)
{
    int i,stas;
	bool flag;
    for(i=0,move=root,stas=0;i!=p.length();++i)
    {
        flag=false;
        while(move)
        {
            if(move->next[p[i]-'a'])
            {
                flag=true;
                move=move->next[p[i]-'a'];
                
                //one time version
                /*
                if(move->suc==-1) break;
                stas+=move->suc;
                move->suc=-1;
				*/
                
                //more time version
                /*
				stas+=move->suc; 
				*/
				       
				facr=move->fail;
                while(facr)
                {
                     //one time version
                    /*
                    if(facr->suc==-1) break;
                    stas+=facr->suc;
                    facr->suc=-1;
                    */
                    
                    //more time version
                    /*
                    stas+=facr->suc;
                    */
                    
                    facr=facr->fail;
                    
                }
                break;
            }
            else move=move->fail;
        }
        if(!flag) move=root;
    }
    return stas;
}

int main()
{
    int n,stas;
    string p;
    
    root=new node();
    scanf("%d",&n);
    for(int i=0;i<n;++i)
    {
        cin>>p;
        insert_string(p);
    }
    inital_fail_pointer();
    build_fail_pointer();
    
    cin>>p;
    stas=matchingword(p);
    
    printf("%d\n",stas);
}
