/*
题意：
给定n和m以及a[1]~a[n]，表示目前n个人的票数
现在可以选择一些水军来投票，每个水军给恰好m个不同的人投票
问现在若要让第一个人胜出（即得票数严格大于其他人的票数），至少需要出动多少水军
1<=m<=n<=100000,1<=ai<=1000
分析：
二分答案mid+判定
根据mid得出2~n的得票上界limit，注意到每个人最多只能得到mid票，把余量大于等于mid的人拿出来特判，其它人把余量加起来比较即可
时间复杂度O(nlogn)
*/
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5;
long long a[maxn+50];
int n,m;
bool check(long long mid)
{
    long long limit=a[1]+mid-1;
    for(int i=2;i<=n;++i) if(a[i]>limit) return false;
    int i;
    for(i=2;i<=n;++i) if(limit-a[i]<mid) break;
    --i;
    if(i-2+1>=m-1) return true;
    long long left=m-1-(i-2+1);
    left*=mid;
    for(i=i+1;i<=n;++i) left-=limit-a[i];
    if(left<=0) return true;else return false;
}
int main()
{
    int T;
    scanf("%d",&T);
    for(int cas=1;cas<=T;++cas)
    {
        printf("Case %d: ",cas);
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;++i) scanf("%lld",&a[i]);
        sort(a+2,a+n+1);
        long long l=0,r=100000000,mid;
        while(l<r)
        {
            mid=(l+r)>>1;
            if(check(mid)) r=mid;else l=mid+1;
        }
        if(!check(r)) printf("Impossible\n");else printf("%lld\n",r);
    }
    return 0;
}
/*
2
3 2
2 3 3
4 2
1 2 3 4
*/
