#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=1<<23;
//const long long P=50000000001507329LL; // 190734863287 * 2 ^ 18 + 1
//const int P=1004535809; // 479 * 2 ^ 21 + 1
const ll P=998244353; // 119 * 2 ^ 23 + 1
const ll G=3;

ll len=0;
ll L,w[2][maxn+50],R[maxn+50];
ll A[maxn<<1];
ll n;
char s[1000000+5];
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
    for(ll x=1;x<=m;x<<=1) L++;
    for(int i=0;i<len;i++) R[i]=(R[i>>1]>>1)|((i&1)<<(L-1));
    w[0][0]=w[0][len]=1;
    ll t=Pow(G,(P-1)/len,P);
    for(int i=1;i<len;i++) w[0][i]=w[0][i-1]*t%P;
    for(int i=0;i<=len;i++) w[1][i]=w[0][len-i];
}
void NTT(ll *a,int r)
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
int main()
{
    scanf("%s",s);
    int lens=strlen(s);
    n=0;
    for(int i=0;i<lens;++i) n=(n*10LL+s[i]-'0')%(P-1);
    scanf("%lld",&len);
    Init(len-1);
    ll w=Pow(G,(P-1)/len,P);
    for(int i=0;i<len;++i)
    {
        A[i]=Pow(1+Pow(w,i,P),n,P);
    }
    NTT(A,1);
    ll res=0;
    for(int i=0;i<len;++i) res^=A[i];
    printf("%lld\n",res);
    return 0;
}
