#include<bits/stdc++.h>
using namespace std;
const int maxn=10000,inf=1e9;
struct Edge
{
    int from,to,flow;
}edge[maxn*250+5];
vector <int> h[maxn+5];
int head[maxn*100+5],nx[maxn*250+5];
int ch[maxn*100+5][2];
int a[maxn+5];
int step[maxn*100];//从源点到点x的距离
int iter[maxn*100];//定点x的第几条边开始有用
int n,m,S,T,len,sz;
void addedge(int from,int to,int cap)
{
    ++len;
    edge[len]={from,to,cap};
    nx[len]=head[from];
    head[from]=len;
    ++len;
    edge[len]={to,from,0};
    nx[len]=head[to];
    head[to]=len;
}
void bfs(int S)
{
    memset(step,-1,sizeof(step));
    step[S]=0;
    queue<int> q;
    q.push(S);
    while(!q.empty())
    {
        int v=q.front();
        q.pop();
        for(int i=head[v];i!=-1;i=nx[i])
        {
            Edge &e=edge[i];
            if(e.flow>0&&step[e.to]<0)
            {
                step[e.to]=step[v]+1;
                q.push(e.to);
            }
        }
    }
}
int dfs(int v,int t,int f)
{
    if(v==t) return f;
    for(int i=iter[v];i!=-1;i=nx[i])
    {
        iter[v]=i;
        Edge &e=edge[i];
        if(e.flow>0&&step[e.to]>step[v])
        {
            int d=dfs(e.to,t,min(e.flow,f));
            if(d>0)
            {
                e.flow-=d;
                edge[i^1].flow+=d;
                return d;
            }
        }
    }
    return 0;
}
int maxflow(int S,int T)
{
    int flow=0;
    for(;;)
    {
        bfs(S);
        if(step[T]<0) return flow;
        for(int i=0;i<=sz;++i) iter[i]=head[i];
        int f;
        while((f=dfs(S,T,inf))>0)
            flow+=f;
    }
}
int change(int last,int l,int r,int x,int id)
{
    int k=++sz;
    ch[k][0]=ch[last][0],ch[k][1]=ch[last][1];
    addedge(k,last,inf);
    if(l==r)
    {
        addedge(k,id,inf);
        return k;
    }
    int mid=(l+r)>>1;
    if(x<=mid) ch[k][0]=change(ch[last][0],l,mid,x,id),addedge(k,ch[k][0],inf);else ch[k][1]=change(ch[last][1],mid+1,r,x,id),addedge(k,ch[k][1],inf);
    return k;
}
int siz[maxn+5],son[maxn+5];
int root[maxn+5],l[maxn+5],r[maxn+5],dfn[maxn+5];
int dfstime=0;
void pre(int k)
{
    siz[k]=1;
    l[k]=++dfstime;
    dfn[dfstime]=k;
    for(int i=0;i<h[k].size();++i)
    {
        int u=h[k][i];
        pre(u);
        if(siz[u]>siz[son[k]]) son[k]=u;
        siz[k]+=siz[u];
    }
    r[k]=dfstime;
}
void ins(int k,int &root)
{
    for(int i=l[k];i<=r[k];++i)
        root=change(root,1,n,a[dfn[i]],dfn[i]);
}
void dsu(int k)
{
    for(int i=0;i<h[k].size();++i) dsu(h[k][i]);
    root[k]=change(root[son[k]],1,n,a[k],k);
    for(int i=0;i<h[k].size();++i)
    {

        int u=h[k][i];
        if(u!=son[k])
            ins(u,root[k]);
    }
}
void work(int k,int l,int r,int x,int y,int id)
{
    if(l>r||k==0||l>y||r<x) return;
    if(x<=l&&r<=y)
    {
        addedge(id,k,inf);
        return;
    }
    if(l==r) return;
    int mid=(l+r)>>1;
    work(ch[k][0],l,mid,x,y,id);
    work(ch[k][1],mid+1,r,x,y,id);
}

int main()
{
    len=-1;
    scanf("%d%d",&n,&m);
    for(int i=2;i<=n;++i)
    {
        int fa;
        scanf("%d",&fa);
        h[fa].push_back(i);
    }
    for(int i=1;i<=n;++i) scanf("%d",&a[i]);
    memset(head,-1,sizeof(head));
    S=0;
    sz=n+m;
    pre(1);
    dsu(1);
    for(int i=1;i<=m;++i)
    {
        int l,r,d,t;
        scanf("%d%d%d%d",&l,&r,&d,&t);
        work(root[d],1,n,l,r,n+i);
        addedge(S,n+i,t);
    }
    T=++sz;
    for(int i=1;i<=n;++i) addedge(i,T,1);
    printf("%d\n",maxflow(S,T));
    return 0;
}
