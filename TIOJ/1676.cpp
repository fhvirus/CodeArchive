#pragma GCC optimize("Ofast")
#include<unistd.h>
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline long long R(){static char c;long long a;while(((c=RC())<'0'||c>'9')&&c!='-'&&c!=-1);if(c=='-'){a=0;while((c=RC())>='0'&&c<='9')a*=10,a-=c^'0';}else{a=c^'0';while((c=RC())>='0'&&c<='9')a*=10,a+=c^'0';}return a;}
inline void W(long long n){char OB[20],OP=0,buf[20],p;if(n==0)OB[OP++]='0';p=0;if(n<0){OB[OP++]='-';while(n)buf[p++]='0'-(n%10),n/=10;}else{while(n)buf[p++]='0'+(n%10),n/=10;}for(--p;p>=0;--p)OB[OP++]=buf[p];write(1,OB,OP);}

#define ll long long

const int N = 5e5 + 225;
int n, K;
ll c[N], sum[N], dp[N];
int sc[N], l, r;

inline ll f(ll j, ll i){
    return -i * i + 2 * j * i + sum[j] + dp[j] - j * j;
}
inline bool eek(ll i, ll j, ll k){
    ll ai = 2 * i, bi = sum[i] + dp[i] - i * i;
    ll aj = 2 * j, bj = sum[j] + dp[j] - j * j;
    ll ak = 2 * k, bk = sum[k] + dp[k] - k * k;
    return (bi - bk) * (aj - ai) <= (bi - bj) * (ak - ai) and 
           (i + K) * (ak - aj) >= bj - bk;
}

int main(){
    n = R(), K = R();
    for(int i = n; i >= 1; --i) c[i] = R();
    for(int i = 1; i <= n; ++i) sum[i] = sum[i-1] + c[i];
    sc[r++] = 0;
    for(int i = 1; i <= n; ++i){
        if(sc[l] < i - K) ++l;
        while(r - l > 1 and f(sc[l], i) <= f(sc[l + 1], i)) ++l;
        dp[i] = f(sc[l], i);
        while(r - l > 1 and eek(sc[r - 2], sc[r - 1], i)) --r;
        sc[r++] = i;
    }
    W(dp[n]);
    return 0;
}
