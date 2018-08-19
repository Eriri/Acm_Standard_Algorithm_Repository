#include<bits/stdc++.h>

const int bsize = 1<<15 ;
char buf[bsize],*ps=buf,*pe=buf+1;
#define buf_in if(++ps==pe)pe=(ps=buf)+fread(buf,1,sizeof(buf),stdin)
template<class T>
inline bool CIN(T &ans){
    ans=0;T op=1;
    if(ps==pe)return false;
    do{
        buf_in;
        if(*ps=='-')op=-1;
    }while(!isdigit(*ps)&&ps!=pe);
    if(ps==pe)return false;
    do{
        ans=(ans<<1)+(ans<<3)+*ps-48;
        buf_in;
    }while(isdigit(*ps)&&ps!=pe);
    ans*=op;
    return true;}

int main(){}
