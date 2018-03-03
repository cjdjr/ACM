/*
题意：
维护一个只含加法、乘法的算式的结果，支持下列操作：
1、在算式末尾填上一个*num或者+num
2、将算式的某项改成*num或者+num
3、将算式的某项删除掉
4、询问当前算式的值（结果很大，对大质数取模）
一共有n个操作,n<=1e5
分析：
用线段树来维护，就是单点修改，区间查询
修改的话一直走到叶子节点，然后向上update就行了
update仔细讨论一下就行了
时间复杂度O(nlogn)
*/
#include<bits/stdc++.h>
using namespace std;
const int mod=1e8+7;
const int maxn=1e5;
struct st
{
    int sum,pre,suf;
    bool flag;
    char op;
}tree[maxn*4+50];
int n,now;
void update(int k)
{
    int l=k*2,r=k*2+1;
    if(tree[l].flag&&tree[r].flag)
    {
        tree[k].sum=(1LL*tree[l].suf*tree[r].pre%mod+tree[l].sum+tree[r].sum)%mod;
        tree[k].pre=tree[l].pre;
        tree[k].suf=tree[r].suf;
        tree[k].op=tree[l].op;
    }
    else
        if(!tree[l].flag&&!tree[r].flag)
        {
            tree[k].sum=0;
            tree[k].pre=1LL*tree[l].pre*tree[r].pre%mod;
            tree[k].suf=tree[k].pre;
            tree[k].op='*';
        }
        else
            if(tree[l].flag)
            {
                tree[k].sum=tree[l].sum;
                tree[k].pre=tree[l].pre;
                tree[k].suf=1LL*tree[l].suf*tree[r].pre%mod;
                tree[k].op=tree[l].op;
            }
            else
            {
                tree[k].sum=tree[r].sum;
                tree[k].pre=1LL*tree[l].suf*tree[r].pre%mod;
                tree[k].suf=tree[r].suf;
                tree[k].op='*';
            }
    tree[k].flag=tree[l].flag|tree[r].flag;
}
void build(int k,int l,int r)
{
    if(l==r)
    {
        if(l==1) tree[k]={0,0,1,1,'+'};
        else tree[k]={0,1,0,1,'*'};
        return;
    }
    int mid=(l+r)>>1;
    build(k*2,l,mid);
    build(k*2+1,mid+1,r);
    update(k);
}
void change(int k,int l,int r,int id,char op,int num)
{
    if(l==r)
    {
        if(op=='+') tree[k]={0,1,num,1,'*'};
        else tree[k]={0,num,num,0,'*'};
        return;
    }
    int mid=(l+r)>>1;
    if(id<=mid) change(k*2,l,mid,id,op,num);else change(k*2+1,mid+1,r,id,op,num);
    update(k);
}
int main()
{
    int T;
    scanf("%d",&T);
    for(int cas=1;cas<=T;++cas)
    {
        printf("Case %d:\n",cas);
        scanf("%d",&n);
        build(1,1,n+1);
        now=1;
        for(int i=1;i<=n;++i)
        {
            char s[10],op[2];
            int num,id;
            scanf("%s",s);
            if(s[0]=='a')
            {
                scanf("%s%d",op,&num);
                ++now;
                change(1,1,n+1,now,op[0],num);
            }
            else
                if(s[0]=='m')
                {
                    scanf("%d%s%d",&id,op,&num);
                    change(1,1,n+1,id,op[0],num);
                }
                else
                    if(s[0]=='d')
                    {
                        scanf("%d",&id);
                        change(1,1,n+1,id,'*',1);
                    }
                    else;
                        printf("%d\n",(tree[1].sum+tree[1].suf)%mod);
        }
    }
    return 0;
}
/*

1
9
add + 666
add * 222
query
delete 3
add * 333
modify 2 * 233
query
delete 4
query
*/
