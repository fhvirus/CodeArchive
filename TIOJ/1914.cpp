#pragma GCC optimize("Ofast")
#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n){static char buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]='\n';if(OP>65516)write(1,OB,OP),OP=0;}
inline int min(int a, int b){ return a < b ? a : b;}

const int N = 225, INF = 1e9+7;
int t, n, m, a[N], dp[N][N];

void solve(){
    n = R(), m = R();
    for(int i = 0; i < n; ++i) a[i] = R();

    for(int i = 0; i < n; ++i){
        dp[i][i] = 1;
        for(int j = i + 1; j < n; ++j)
            dp[i][j] = INF;
    }

    for(int len = 2; len <= n; ++len){
        for(int l = 0; l + len - 1 < n; ++l){
            int r = l + len - 1;
            for(int m = l; m < r; ++m){
                dp[l][r] = min(
                    dp[l][r],
                    dp[l][m] + dp[m + 1][r] - (a[l] == a[r] ? 1 : 0)
                );
            }
        }
    }
    
    W(dp[0][n-1]);
}

int main(){
    for(t = R(); t; --t) solve();
    write(1,OB,OP);
    return 0;
}
