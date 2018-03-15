#include<bits/stdc++.h>
using namespace std;
#define mp make_pair
const int maxn=1e5;
typedef long long ll;
const ll inf=100000000000000000LL;
typedef pair<int,ll> Point;
ll a[maxn+5],b[maxn+5],dp[maxn+5];
vector<int> g[maxn+5];
int n;
set<Point> s[maxn+5];
double cross(Point a,Point b,Point c)
{
    /*
    此题做叉积爆了longlong，要用double来判正负
    */
    ll x=b.first-a.first,y=b.second-a.second;
    ll xx=c.first-b.first,yyy=c.second-b.second;
    return (double)x*yyy-(double)y*xx;
}
void insert(set<Point> &s,Point p)
{
    /*
    向凸包s中加入一个点p
    */
    set<Point>::iterator it=s.lower_bound(p);
    set<Point>::iterator jt=it;
    if(it!=s.begin()) --jt;
    if(it!=s.begin()&&it!=s.end()&&cross(*jt,p,*it)<=0) return;
    if(it!=s.begin())
    {
        it=jt;
        while(it!=s.begin())
        {
            jt=it;
            --jt;
            if(cross(*jt,*it,p)<=0) s.erase(it--);else break;
        }
    }
    jt=s.lower_bound(p);
    if(jt!=s.end()) it=jt++;
    while(jt!=s.end())
    {
        if(cross(p,*it,*jt)<=0) s.erase(it++);else break;
        jt=it;
        ++jt;
    }
    s.insert(p);
}
ll query(set<Point> &s,ll k)
{
    /*
    在凸包s中查找斜率为k的时候的最优值
    注意在容器上二分的姿势
    */
    if(s.empty()) return 0;
    ll l=s.begin()->first,r=s.rbegin()->first,mid;
    while(l<r)
    {
        mid=(l+r+1)>>1;
        set<Point>::iterator it=s.lower_bound(mp(mid,-inf)),jt=it--;
        if(k*(jt->first-it->first)>=jt->second-it->second) l=mid;else r=mid-1;
    }
   Point res=*s.lower_bound(mp(l,-inf));
    return (-k)*res.first+res.second;
}
void dfs(int k,int fa)
{
    for(auto u:g[k])
    {
        if(u==fa) continue;
        dfs(u,k);
        if(s[k].size()<s[u].size()) s[k].swap(s[u]);//启发式合并
        for(auto x:s[u])
            insert(s[k],x);
        set<Point>().swap(s[u]);
    }
    dp[k]=query(s[k],-a[k]);
    insert(s[k],mp(b[k],dp[k]));
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i) scanf("%lld",&a[i]);
    for(int i=1;i<=n;++i) scanf("%lld",&b[i]);
    for(int i=1;i<n;++i)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        g[u].push_back(v),g[v].push_back(u);
    }
    dfs(1,0);
    for(int i=1;i<=n;++i) printf("%lld ",dp[i]);
    return 0;
}
