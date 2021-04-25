#pragma GCC optimize("Ofast")
#include<unistd.h>
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while(((c=RC())<'0'||c>'9')&&c!='-'&&c!=-1);if(c=='-'){a=0;while((c=RC())>='0'&&c<='9')a*=10,a-=c^'0';}else{a=c^'0';while((c=RC())>='0'&&c<='9')a*=10,a+=c^'0';}return a;}
inline void W(long long n){char OB[20],OP=0,buf[20],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];write(1,OB,OP);}

#include<deque>
using namespace std;

#define ll long long
#define pll pair<ll, ll>
#define ff first
#define ss second

const int N = 1e6 + 225;
int n, a, b, c, x[N];
ll dp[N], pre[N];

inline ll f(pll j, int i){
    return j.ff * pre[i] + j.ss;
}
inline bool jizz(pll i, pll j, pll k){
    return (i.ss - k.ss) * (j.ff - i.ff) <= (i.ss - j.ss) * (k.ff - i.ff);
}

int main(){
    n = R(), a = R(), b = R(), c = R();
    for(int i = 1; i <= n; ++i) x[i] = R(), pre[i] = x[i] + pre[i-1];
    deque<pll> sc;
    sc.push_back({0, 0});
    for(int i = 1; i <= n; ++i){
        // popfront
        while(sc.size() > 1 and f(sc[0], i) <= f(sc[1], i)) sc.pop_front();
        // update dp[i]
        dp[i] = f(sc[0], i) + a * pre[i] * pre[i] + b * pre[i] + c;
        // insert and popback
        pll li = {-2 * a * pre[i], dp[i] + a * pre[i] * pre[i] - b * pre[i]};
        while(sc.size() > 1 and jizz(sc[sc.size() - 2], sc.back(), li)) sc.pop_back();
        sc.push_back(li);
    }
    W(dp[n]);
	return 0;
}
