/*
题意：
给定n,m，有n个位置排成一行，每个位置可以填上0~m中的一个数，表示该位置的炸弹的爆炸半径
要求每个炸弹的爆炸半径里没有其它炸弹
问有多少种合法的填数方案，答案可能很大对1e9+7取模
n<=10000,m<=100
分析：
dp[i][j]表示填了前i个位置，第i个位置对后面的爆炸半径是j的方案数
dp[i][0]+=dp[i-1][0](不放)
dp[i][j]+=dp[i-1][j+1](不放)
dp[i][j]+=dp[i-j-1][k](1<=j<=m,0<=k<=j)(放一个爆炸半径为j的炸弹)
*/
#include<bits/stdc++.h>
using namespace std;
const int maxn=10000,maxm=100,mod=1e9+7;
int dp[maxn+5][maxm+5],sum[maxn+5][maxm+5];
int n,m,ans;
void work(int &a,int b)
{
    a=(a+b)%mod;
}
int main()
{
    int T;
    scanf("%d",&T);
    for(int cas=1;cas<=T;++cas)
    {
        printf("Case %d: ",cas);
        scanf("%d%d",&n,&m);
        for(int i=0;i<=n+1;++i)
            for(int j=0;j<=m+1;++j)
                dp[i][j]=sum[i][j]=0;
        dp[0][0]=1;
        for(int i=0;i<=m;++i) sum[0][i]=1;
        for(int i=1;i<=n;++i)
        {
            dp[i][0]=dp[i-1][0];
            for(int j=0;j<=m;++j) work(dp[i][j],dp[i-1][j+1]);
            for(int j=1;j<=m;++j)
                if(i-j-1>=0) work(dp[i][j],sum[i-j-1][j]);
                else work(dp[i][j],1);
            sum[i][0]=dp[i][0];
            for(int j=1;j<=m;++j) sum[i][j]=sum[i][j-1],work(sum[i][j],dp[i][j]);
        }
        ans=0;
        for(int i=0;i<=m;++i) work(ans,dp[n][i]);
        printf("%d\n",ans);
    }
    return 0;
}
/*
2
3 2
4 2
*/
