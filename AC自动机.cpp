#include<bits/stdc++.h>
using namespace std;

struct ACautomaton
{
    ACautomaton(){root=new node();};
    struct node
    {
        node():suc(0),fail(0){memset(next,0,sizeof(next));}
        node *next[26],*fail;//efficient when the sentence only contain
        int suc;			 //letters of alphabet
    }*root,*move,*facr;
    void insert_string(string s)
    {
        move=root;
        for(int i=0;i<s.length();move=move->next[s[i]-'a'],++i)
            if(!move->next[s[i]-'a'])move->next[s[i]-'a']=new node();
        ++move->suc;
    }
    void build_fail_pointer()
    {
        deque<node*> q;
        for(int i=0;i<26;++i)if(root->next[i])
            {root->next[i]->fail=root;q.push_back(root->next[i]);}
        bool flag;
        while(!q.empty())
        {
            move=q.front();q.pop_front();
            for(int i=0;i<26;++i)if(move->next[i])
            {
                q.push_back(move->next[i]);facr=move->fail;flag=false;
                while(facr)
                {
                    if(facr->next[i])
                        {move->next[i]->fail=facr->next[i];flag=true;break;}
                    facr=facr->fail;
                }
                if(!flag) move->next[i]->fail=root;
            }
        }
    }
    int matchingword(string p)
    {
        int i,stas;bool flag;
        for(i=0,move=root,stas=0;i!=p.length();++i)
        {
            flag=false;
            while(move)
            {
                if(move->next[p[i]-'a'])
                {
                    flag=true;move=move->next[p[i]-'a'];
                    /*one time version
                    if(move->suc==-1) break;
                    stas+=move->suc;move->suc=-1;
                    /*more time version
                    stas+=move->suc;
                    */
                    facr=move->fail;
                    while(facr)
                    {
                        /*one time version
                        if(facr->suc==-1) break;
                        stas+=facr->suc;facr->suc=-1;
                        /*more time version
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
}; 

int main(){}
