#pragma GCC optimize("Ofast")
#include<unistd.h>
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n){char OB[12],OP=0,buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];write(1,OB,OP);}

#define ll long long
#include<algorithm>
using namespace std;

const int N = 3001, M = 998244353;
int C[N][N];
inline void init(int n){
    for(int i = 0; i <= n; ++i) C[i][0] = 1;
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= i; ++j){
            C[i][j] = (C[i-1][j] + C[i-1][j-1]);
            C[i][j] -= C[i][j] >= M ? M : 0;
        }
}
inline ll mpow(ll x, int e){
    ll ans = 1;
    while(e) (e&1) and (ans = ans * x % M), x = x * x % M, e >>= 1;
    return ans;
}

int n, m, k;
int a[N], b[N];
int ans, ansa[N], ansb[N];

signed main(){
    n = R(), m = R(), k = R();
    for(int i = 1; i <= n; ++i) a[i] = R();
    for(int i = 1; i <= m; ++i) b[i] = R();
    sort(a + 1, a + n + 1);
    sort(b + 1, b + m + 1);
    init(n > m ? n : m);

    for(int r = 1; r <= k; ++r){
        for(int i = 1; i <= n; ++i) ansa[i] = (ll) C[i-1][r-1] * C[n-i][k-r] % M;
        for(int i = 1; i <= m; ++i) ansb[i] = (ll) C[i-1][r-1] * C[m-i][k-r] % M;
        int bptr = 1; ll pre = 0;
        for(int i = 1; i <= n; ++i){
            while(b[bptr] < a[i] and bptr <= m){
                pre = (pre + ansb[bptr]);
                pre -= pre >= M ? M : 0;
                ++bptr;
            }
            ans = (ans + pre * ansa[i] % M);
            ans -= ans >= M ? M : 0;
        }
    }
    W((ll) ans * mpow((ll) C[n][k] * C[m][k] % M, M-2) % M);
	return 0;
}
