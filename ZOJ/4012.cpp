#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=100000,inf=1e9;
int n,m,cur,ans,root;
ll x[maxn+50],y[maxn+50];
struct P
{
    ll mn[2],mx[2],d[2];
    int lch,rch;
    ll& operator[](int x) {return d[x];}
    friend bool operator<(P x,P y) {return x[cur]<y[cur];}
}p[maxn+50];
struct kdtree
{
    P t[2*maxn+50];
    int ans;
    void update(int k)
    {
        int l=t[k].lch,r=t[k].rch;
        for (int i=0;i<2;i++)
        {
            t[k].mn[i]=t[k].mx[i]=t[k][i];
            if(l) t[k].mn[i]=min(t[k].mn[i],t[l].mn[i]);
            if(r) t[k].mn[i]=min(t[k].mn[i],t[r].mn[i]);
            if(l) t[k].mx[i]=max(t[k].mx[i],t[l].mx[i]);
            if(r) t[k].mx[i]=max(t[k].mx[i],t[r].mx[i]);
        }
    }
    int build(int l,int r,int now)
    {
        cur=now;
        int mid=(l+r)/2;
        nth_element(p+l,p+mid,p+r+1);
        t[mid]=p[mid];
        for(int i=0;i<2;i++) t[mid].mx[i]=t[mid].mn[i]=t[mid][i];
        if(l<mid) t[mid].lch=build(l,mid-1,now^1);
        if(r>mid) t[mid].rch=build(mid+1,r,now^1);
        update(mid);
        return mid;
    }
    bool check(ll a,ll b,P x)
    {
        ll t;
        t=-b*x.mn[0]+b*a;
        if(x.mn[1]*a<=t&&t<=x.mx[1]*a) return true;
        t=-b*x.mx[0]+b*a;
        if(x.mn[1]*a<=t&&t<=x.mx[1]*a) return true;
        t=(b-x.mn[1])*a;
        if(x.mn[0]*b<=t&&t<=x.mx[0]*b) return true;
        t=(b-x.mx[1])*a;
        if(x.mn[0]*b<=t&&t<=x.mx[0]*b) return true;
        return false;
    }
    void query(int k,ll a,ll b)
    {
         //printf("ce : %lld %lld ---- (%lld,%lld) (%lld,%lld)\n",t[k][0],t[k][1],t[k].mn[0],t[k].mn[1],t[k].mx[0],t[k].mx[1]);
        if(!check(a,b,t[k])) return;

        if(t[k][0]*b%a==0&&t[k][0]<=a&&t[k][1]==-t[k][0]*b/a+b) ++ans;
        if(t[k].lch) query(t[k].lch,a,b);
        if(t[k].rch) query(t[k].rch,a,b);
    }
    int solve(ll a,ll b)
    {
        ans=0;
        query(root,a,b);
        return ans;
    }
}kdtree;
int main()
{
    freopen("ce.in","r",stdin);
    //freopen("ce.out","w",stdout);
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&n,&m);
        for(int i=1;i<=n;++i)
        {
            scanf("%lld%lld",&x[i],&y[i]);
            p[i][0]=x[i],p[i][1]=y[i];
        }
        root=kdtree.build(1,n,0);
        while(m--)
        {
            ll a,b;
            scanf("%lld%lld",&a,&b);
            printf("%d\n",kdtree.solve(a,b));
        }
    }
    return 0;
}
