#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=1e6;
//const long long P=50000000001507329LL; // 190734863287 * 2 ^ 18 + 1
//const int P=1004535809; // 479 * 2 ^ 21 + 1
const ll P=998244353; // 119 * 2 ^ 23 + 1
const ll G=3;

ll len=0;
ll L,w[2][maxn+50],R[maxn+50];
ll fac[maxn+5],inv[maxn+5];
int n;
vector<ll> A[maxn+5];

ll Pow(ll a,ll b,ll p)
{
    ll ret=1;
    for(;b;(a*=a)%=p,b>>=1)
        if(b&1)
            (ret*=a)%=p;
    return ret;
}
ll Inv(ll x)
{
    return Pow(x,P-2,P);
}
void Init(int m)
{
    /*预处理0~m位*/
    L=0;
    for(len=1;len<=(m<<1);len<<=1) L++;
    for(int i=0;i<len;i++) R[i]=(R[i>>1]>>1)|((i&1)<<(L-1));
    w[0][0]=w[0][len]=1;
    ll t=Pow(G,(P-1)/len,P);
    for(int i=1;i<len;i++) w[0][i]=w[0][i-1]*t%P;
    for(int i=0;i<=len;i++) w[1][i]=w[0][len-i];
}
void NTT(vector<ll> &a,int r)
{
    for(int i=0;i<len;i++)
        if(i<R[i])
            swap(a[i],a[R[i]]);
    for(int i=1;i<len;i<<=1)
        for(int j=0;j<len;j+=(i<<1))
            for(int k=0;k<i;k++)
            {
                ll x=a[j+k],y=w[r][len/(i<<1)*k]*a[j+k+i]%P;
                a[j+k]=(x+y)%P; a[j+k+i]=(x-y+P)%P;
            }
    if(r==1)
        for(int i=0,inv=Inv(len);i<len;i++) a[i]=a[i]*inv%P;
}
void mul(vector<ll> &a,vector<ll> b)
{
    int n=a.size(),m=b.size();
    int limit=max(n,m);
    for(len=1;len<=limit;len<<=1);
    Init(len-1);
    a.resize(len),b.resize(len);
    NTT(a,0);
    NTT(b,0);
    for(int i=0;i<len;++i) a[i]=a[i]*b[i]%P;
    NTT(a,1);
    a.resize(n+m-1);
}
queue<int> q;
int main()
{
    scanf("%d",&n);
    fac[0]=1;
    for(int i=1;i<=100000;++i)fac[i]=fac[i-1]*i%P;
    inv[0]=1;
    for(int i=1;i<=100000;++i) inv[i]=Inv(fac[i]);

    bool flag=1;
    for(int i=1;i<=n;++i)
    {
        int x;
        scanf("%d",&x);
        if(x>1) flag=0;
        A[i].resize(x+1);
        A[i][0]=0;
        for(int j=1;j<=x;++j) A[i][j]=fac[x-1]*inv[x-j]%P*inv[j-1]%P*inv[j]%P;
        q.push(i);
    }
    if(flag==0) printf("499122177 ");
    else
        if(n&1) printf("1 ");
        else printf("0 ");
    cout<<clock()<<endl;
    while(q.size()>1)
    {
        int x=q.front();q.pop();
        int y=q.front();q.pop();
        mul(A[x],A[y]);
        q.push(x);
    }
    ll ans=0;
    for(int i=0;i<A[q.front()].size();++i)
        if(i&1) ans=(ans+A[q.front()][i]*fac[i]%P)%P;
    printf("%lld\n",ans);
    cout<<clock()<<endl;
    return 0;
}
