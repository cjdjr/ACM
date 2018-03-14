#include<bits/stdc++.h>
using namespace std;
#define mp make_pair
const int maxn=15,mod=1e9+7;
int dp[maxn+5][maxn+5][1<<15];
int n,m,num;
pair<int,int> b[maxn*2+5];
int a[maxn+5][maxn+5];
int sum[maxn+5][maxn+5];
int bin[16];
int cal(int s,int i)
{
    return (s<<i)%bin[m];
}
bool check(int x,int y,int len)
{
    if(y+len-1>m) return false;
    if(sum[x][y+len-1]-sum[x][y-1]==0) return true;else return false;
}
void work(int &x,int y)
{
    x=(x+y)%mod;
}
int main()
{
    scanf("%d%d%d",&n,&m,&num);
    bin[0]=1;
    for(int i=1;i<=16;++i) bin[i]=bin[i-1]<<1;
    for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j)
        {
            scanf("%d",&a[i][j]),a[i][j]^=1;
            sum[i][j]=sum[i][j-1]+a[i][j];
        }
    for(int i=1;i<=num;++i) scanf("%d%d",&b[i].first,&b[i].second);
    dp[0][m][bin[m]-1]=1;
    for(int i=0;i<=n;++i)
        for(int j=1;j<=m;++j)
            for(int s=0;s<bin[m];++s)
            {
                if(dp[i][j][s]==0) continue;
                pair<int,int> nx;
                if(j<m) nx=mp(i,j+1);else nx=mp(i+1,1);
                work(dp[nx.first][nx.second][cal(s,1)^a[nx.first][nx.second]],dp[i][j][s]);
                for(int k=1;k<=num;++k)
                {
                    pair<int,int> tmp=b[k];
                    if(!check(nx.first,nx.second,tmp.second)) continue;
                    if(tmp.first==2&&((s>>(m-tmp.second))&(bin[tmp.second]-1))) continue;
                    work(dp[nx.first][nx.second+tmp.second-1][cal(s,tmp.second)^(bin[tmp.second]-1)],dp[i][j][s]);
                }
            }
    int ans=0;
    for(int s=0;s<bin[m];++s) work(ans,dp[n][m][s]);
    printf("%d\n",ans);
    return 0;

}
