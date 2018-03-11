#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5;
#define mp make_pair
struct wjmzbmr
{
    int u,v,w,l,r;
    void input()
    {
        scanf("%d%d%d",&u,&v,&w);
    }
}e[maxn*2+5];
map<pair<int,int> , int> M;
int n,m,Q,len,tot,top;
pair<int,int> q[maxn+5];
vector<int> g[maxn*4+5];
int f[maxn+5],sz[maxn+5],val[maxn+5];
int Stack[maxn*2+5];
int base[35][35];
int find(int x)
{
    if(f[x]==x) return x;
    int father=find(f[x]);
    return father;
}
int get_val(int x)
{
    int w=0;
    while (f[x]!=x) w^=val[x],x=f[x];
    return w;
}

void change(int k,int l,int r,int x,int y,int id)
{
    if(x>y) return;
    if(l>r||l>y||r<x) return;
    if(x<=l&&r<=y)
    {
        g[k].push_back(id);
        return;
    }
    if(l==r) return;
    int mid=(l+r)>>1;
    change(k*2,l,mid,x,y,id);
    change(k*2+1,mid+1,r,x,y,id);
}
void ins(int k,int dep)
{
    for(auto id:g[k])
    {
        int x=e[id].u,y=e[id].v,w=e[id].w;
        int u=find(x),v=find(y);
        if(u!=v)
        {
            if(sz[u]>sz[v]) swap(u,v),swap(x,y);
            f[u]=v;
            sz[v]+=sz[u];
           val[u]=0;
           val[u]=get_val(x)^get_val(y)^w;
            Stack[++top]=u;
        }
        else
        {
            w=get_val(x)^get_val(y)^w;
            for(int i=30;i>=0;--i)
                if(w&(1<<i))
                    if(base[dep][i]==0)
                    {
                        base[dep][i]=w;
                        for(int j=30;j>i;--j)
                            if(base[dep][j]&(1<<i)) base[dep][j]^=w;
                        break;
                    }
                    else w^=base[dep][i];
        }
    }
}
void del(int t)
{
    while(top>t)
    {
        int u=Stack[top--];
        sz[f[u]]-=sz[u];
        val[u]=0;
        f[u]=u;
    }
}
void solve(int k,int l,int r,int dep)
{
    if(l>r) return;
    int tmp=top;
    ins(k,dep);
    if(l==r)
    {
        int x=q[l].first,y=q[l].second;
        int ans=get_val(x)^get_val(y);
        for(int i=30;i>=0;--i)
                if(base[dep][i])
                    if(ans&(1<<i)) ans^=base[dep][i];
        printf("%d\n",ans);
        del(tmp);
        return;
    }
    int mid=(l+r)>>1;
    for(int i=0;i<=30;++i) base[dep+1][i]=base[dep][i];
    solve(k*2,l,mid,dep+1);
    for(int i=0;i<=30;++i) base[dep+1][i]=base[dep][i];
    solve(k*2+1,mid+1,r,dep+1);
    del(tmp);
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;++i)
    {
        e[++len].input();
        e[len].l=1;
        e[len].r=-1;
        M[mp(e[len].u,e[len].v)]=len;
    }
    scanf("%d",&Q);
    tot=0;
    for(int i=1;i<=Q;++i)
    {
        int op,x,y,d;
        scanf("%d",&op);
        if(op==1)
        {
            scanf("%d%d%d",&x,&y,&d);
            e[++len]={x,y,d,tot+1,-1};
            M[mp(x,y)]=len;
        }
        else
            if(op==2)
            {
                scanf("%d%d",&x,&y);
                e[M[mp(x,y)]].r=tot;
                M[mp(x,y)]=0;
            }
            else
            {
                scanf("%d%d",&x,&y);
                q[++tot]=mp(x,y);
            }
    }
    for(int i=1;i<=len;++i) if(e[i].r==-1) e[i].r=tot;
    for(int i=1;i<=len;++i) change(1,1,tot,e[i].l,e[i].r,i);
    for(int i=1;i<=n;++i) f[i]=i,sz[i]=1;
    if(tot) solve(1,1,tot,0);
    return 0;
}
