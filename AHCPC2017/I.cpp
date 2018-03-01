#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5;
struct bomb
{
    long long from,w,t,p;
    void input()
    {
        scanf("%lld%lld%lld",&w,&t,&p);
    }
}a[maxn+5];
struct wjmzbmr
{
    /*
    id=0 boom
    id=1 install
    */
    int id;
    long long t;
    int num;
    bool operator < (const wjmzbmr &x) const
    {
        if(t!=x.t) return t<x.t;
        return id<x.id;
    }
};
set<wjmzbmr> q;
int n,m;
long long ans;
long long tag[maxn*4+5];
void build(int k,int l,int r)
{
    if(l>r) return;
    if(l==r)
    {
        tag[k]=0;
        return;
    }
    int mid=(l+r)>>1;
    build(k*2,l,mid);
    build(k*2+1,mid+1,r);
}
void change(int k,int l,int r,int x,int y,long long c)
{
    if(l>r||l>y||r<x) return;
    if(x<=l&&r<=y)
    {
        tag[k]=c;
        return;
    }
    if(l==r) return;
    int mid=(l+r)>>1;
    change(k*2,l,mid,x,y,c);
    change(k*2+1,mid+1,r,x,y,c);
}
long long query(int k,int l,int r,int x)
{
    if(l==r) return tag[k];
    int mid=(l+r)>>1;
    if(x<=mid) return max(tag[k],query(k*2,l,mid,x));
    else return max(tag[k],query(k*2+1,mid+1,r,x));
}
int main()
{
    freopen("ce.in","r",stdin);
    int T;
    scanf("%d",&T);
    for(int cas=1;cas<=T;++cas)
    {
        printf("Case #%d: ",cas);
        scanf("%d%d",&n,&m);
        build(1,1,n);
        for(int i=1;i<=m;++i) a[i].input();
        q.clear();
        q.insert({1,abs(a[1].p-1),1});
        set<wjmzbmr>::iterator it;
        int nowb=2,lastdead=0;
        for(it=q.begin();it!=q.end();++it)
        {
            wjmzbmr u=*it;
            if(u.id==1)
            {
                if(u.num==n)
                {
                    ans=u.t;
                    break;
                }
                a[u.num].from=u.t;
                nowb=u.num+1;
                q.insert({1,u.t+a[nowb].t,nowb});
            }
            else
                if(query(1,1,n,a[u.num].p)<=a[u.num].from)
                {
                    change(1,1,n,max(1,a[u.num].p-a[u.num].w),min(a[u.num].p+a[u.num].w,n),u.t);
                    if()
                }
        }
    }
}
