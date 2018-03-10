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
}e[maxn+5];
map<pair<int,int> , int> M;
int n,m,Q,len,tot=1;
vector<pair<int,int> > q[maxn+5];
vector<int>g[maxn*4+5];
int f[maxn+5],sz[maxn+5];
int find(int x)
{
    if(f[x]==x) return x;
    int father=find(f[x]);
    val[x]=val[x]^val[f[x]];
    return f[x]=father;
}
void change(int k,int l,int r,int x,int y,int id)
{
    if(l>r) return;
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
            val[u]=val[x]^val[y]^w;
        }
        else
        {
            w^=val[x]^val[y];
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
void solve(int k,int l,int r,int dep)
{
    if(l>r) return;
    ins(k);
}
int main()
{
    freopen("ce.in","r",stdin);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;++i)
    {
        e[++len].input();
        e[len].l=1;
        e[len].r=-1;
        M[mp(e[len].u,e[len].v)]=len;
    }
    scanf("%d",&Q);
    for(int i=1;i<=Q;++i)
    {
        int op,x,y,d;
        scanf("%d",&op);
        if(op==1)
        {
            scanf("%d%d%d",&x,&y,&d);
            e[++len]={x,y,d,tot,-1};
            M[mp(x,y)]=len;
        }
        else
            if(op==2)
            {
                scanf("%d%d",&x,&y);
                e[M[mp(x,y)]].r=tot;
                ++tot;
            }
            else
            {
                scanf("%d%d",&x,&y);
                q[tot].push_back(mp(x,y));
            }
    }
    for(int i=1;i<=len;++i) change(1,1,tot,e[i].l,e[i].r,i);
    for(int i=1;i<=n;++i) f[i]=i,sz[i]=1;
    solve(1,1,tot,0);
    return 0;
}
