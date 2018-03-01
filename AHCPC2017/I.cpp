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
    void output()
    {
        printf("w %lld    t %lld     p %lld\n",w,t,p);
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
    void output()
    {
        printf("id : %d   time :  %lld     number :  %d\n",id,t,num);
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
    tag[k]=0;
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
int cal(int id,long long t)
{
    if(a[id+1].p>a[id].p) return a[id].p+t;else return a[id].p-t;
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
        for(int i=1;i<=m;++i) a[i].input(),a[i].from=0;
        q.clear();
        q.insert({1,abs(a[1].p-1),1});
        set<wjmzbmr>::iterator it;
        int nowb=2,lastdead=0;
        long long turn=0;
        wjmzbmr now;
       /* for(int i=77645;i<=77665;++i)
        {
            printf("%d :    ",i);
            a[i].output();
        }*/
        while(!q.empty())
        {
            wjmzbmr u=*q.begin();
                        q.erase(q.begin());
            //u.output();
           // if(u.num==77660&&u.id==1) cout<<clock()<<endl;
            if(u.id==1)
            {
                if(u.num==m)
                {
                    ans=u.t;
                    break;
                }
                a[u.num].from=u.t;
                q.insert({0,u.t+a[u.num].t,u.num});
                nowb=u.num+1;
                now={1,u.t+abs(a[nowb].p-a[u.num].p),nowb};
                q.insert(now);
                turn=0;
            }
            else
                if(query(1,1,n,a[u.num].p)<=a[u.num].from)
                {

                    change(1,1,n,max(1LL,a[u.num].p-a[u.num].w),min(a[u.num].p+a[u.num].w,1LL*n),u.t);
                    int position=cal(nowb-1,u.t-a[nowb-1].from-turn);
                   // if(u.t==4)
                    //{
                       // printf("ok lastdead %d    position : %d \n",lastdead,position);
                        //printf(nowb-1,u.t-a[now])
                    if(lastdead!=u.t&&position>=a[u.num].p-a[u.num].w&&position<=a[u.num].p+a[u.num].w)
                    {
                       // printf("ce : ");
                       // u.output();
                        ++turn;
                        lastdead=u.t;
                        set<wjmzbmr>::iterator itt=q.find(now);
                        //printf("cece : ");
                        wjmzbmr tmp=(*itt);
                        //tmp.output();
                        q.erase(itt);
                        now.t++;
                        q.insert(now);
                    }
                }

        }
       printf("%lld\n",ans);
    }
    cout<<clock()<<endl;
    return 0;
}
