#include<bits/stdc++.h>
using namespace std;

int StringRepresetation(string s,bool flag)//min->false max->true
{
    int i,j,k,len;
    len=s.length();
    for(i=0,j=1,k=0;i<len&&j<len&&k<len;)
    {
        if(s[(i+k)%len]==s[(j+k)%len])++k;
        else
        {
            if(flag?s[(i+k)%len]>s[(j+k)%len]:s[(j+k)%len]<s[(i+k)%len])
            {
                i=i+k+1;
            }
            else
            {
                j=j+k+1;
            }
            if(i==j)++j;
            k=0;
        }
    }
    return i<j?i:j;
}

int main()
{
    int ans;
    string s;
    cin>>s;
    ans=StringRepresetation(s);
    cout<<ans;
}