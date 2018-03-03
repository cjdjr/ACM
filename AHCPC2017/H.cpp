/*
题意：
在一个树上每个点i有一些葡萄c[i]，我们现在的目标是取出尽量多的葡萄
取葡萄的规则是选择两个相邻的点，同时取出数量相同的葡萄
有一些点上的葡萄是特殊葡萄，这些葡萄必须全部取完
你需要回答在取完所有特殊葡萄的情况下，取的葡萄总数的最大值
n<=1e5,c[i]<=1e4
分析：
奇偶分组成二分图，就是带下限的最大流了
在稀疏图上dinic跑得巨快……
*/
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5,inf=1e9+1,maxm=3e5+5;
struct Edge
{
    int from,to,cap,flow;
}edge[maxm*2+5];
vector <int> g[maxn+5],gg[maxn+5];
int step[maxn];//从源点到点x的距离
int iter[maxn];//定点x的第几条边开始有用
int c[maxn],type[maxn+5],dep[maxn];
int st[maxn+5],ed[maxn+5];
int n,m,S,T,SS,TT,len;
void addedge(int from,int to,int cap)
{
    //printf("%d %d %d\n",from,to,cap);
    ++len;
    edge[len]={from,to,cap,0};
    g[from].push_back(len);
    ++len;
    edge[len]={to,from,0,0};
    g[to].push_back(len);
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
        for(int i=0;i<g[v].size();++i)
        {
            Edge &e=edge[g[v][i]];
            if(e.cap>e.flow&&step[e.to]<0)
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
    for(int &i=iter[v];i<g[v].size();++i)//这里是引用，i++的同时iter也++，其实相当于上个的used，不过不用判断了
    {
        Edge &e=edge[g[v][i]];
        if(e.cap>e.flow&&step[e.to]>step[v])
        {
            int d=dfs(e.to,t,min(e.cap-e.flow,f));
            if(d>0)
            {
                e.flow+=d;
                edge[g[v][i]^1].flow-=d;
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
        memset(iter,0,sizeof(iter));
        int f;
        while((f=dfs(S,T,inf))>0)
            flow+=f;
    }
}
void dfs(int k)
{
    for(auto &u:gg[k])
    {
        //printf("%d\n",u);
        dep[u]=dep[k]+1;
        if(dep[k]%2==1)
        addedge(k,u,inf);
        else
            addedge(u,k,inf);
        dfs(u);
    }
}
int main()
{
    int t;;
    scanf("%d",&t);
    for(int cas=1;cas<=t;++cas)
    {
        printf("Case #%d: ",cas);
        scanf("%d",&n);
        for(int i=0;i<=n+4;++i) gg[i].clear(),g[i].clear(),st[i]=ed[i]=dep[i]=0;
        len=-1;
        S=0,T=n+1;
        SS=n+2,TT=n+3;
        for(int i=1;i<=n;++i)
        {
            int father;
            scanf("%d%d%d",&father,&c[i],&type[i]);
            type[i]*=c[i];
            gg[father].push_back(i);
        }
        dep[1]=1;
        //printf("ok\n");
        dfs(1);
       // printf("ok\n");
        for(int i=1;i<=n;++i)
            if(dep[i]%2==1) addedge(S,i,c[i]-type[i]),st[S]+=type[i],ed[i]+=type[i];else addedge(i,T,c[i]-type[i]),st[i]+=type[i],ed[T]+=type[i];
        //for(int i=0;i<=n+1;++i) printf("%d : %d\n",i,ed[i]);
        for(int i=0;i<=n+1;++i) if(ed[i]) addedge(SS,i,ed[i]);
        for(int i=0;i<=n+1;++i) if(st[i]) addedge(i,TT,st[i]);
        addedge(T,S,inf);
        int tflow=0;
        for(int i=0;i<=n+1;++i) tflow+=st[i];
        int ans=maxflow(SS,TT);
        if(ans!=tflow) printf("-1\n");else
        {
            g[SS].clear();
            g[TT].clear();
            printf("%lld\n",2LL*maxflow(S,T));
        }
    }
    return 0;
}
/*
1
4
0 2 0
1 3 0
1 1 1
3 5 0
*/
