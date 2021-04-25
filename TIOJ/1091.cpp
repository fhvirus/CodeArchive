#pragma GCC optimize("Ofast")
#include<unistd.h>
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n){char OB[12],OP=0,buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];write(1,OB,OP);}


const int M = 105, N = 1005, INF = 30000;
#define min(a,b) (a<b?a:b)
#define For(i,n) for(int i = 0; i < n; ++i)
char a[M], b[N];
short m, n, dp[N][M];
short z[M], aa[M], bb[M];

int main(){
    a[0] = b[0] = ' '; m = n = 1;
    while((a[m] = RC()) >= 'A') ++m; --m;
    while((b[n] = RC()) < 'A'); ++n;
    while((b[n] = RC()) >= 'A') ++n; --n;

    For(i,M) dp[0][i] = INF;
    dp[0][0] = 0;
    
    // KMP
    int cur = 0;
    for(int i = 2; i <= m; ++i){
        while(cur == m or (cur != 0 and a[cur+1] != a[i])) cur = z[cur];
        if(a[cur+1] == a[i]) ++cur;
        z[i] = cur;
    }

    // PreCalc
    for(int j = 0; j < m; ++j){
        // A
        cur = j;
        while(cur != 0 and a[cur + 1] != 'A') cur = z[cur];
        if(a[cur + 1] == 'A') ++cur;
        aa[j] = cur;
        // B
        cur = j;
        while(cur != 0 and a[cur + 1] != 'B') cur = z[cur];
        if(a[cur + 1] == 'B') ++cur;
        bb[j] = cur;
    }

    int roll = 0;
    for(int i = 0; i < n; ++i){
        for(int j = 0; j <= m; ++j){
            // dp[1 - roll][j] = INF;
            dp[i + 1][j] = INF;
        }
        for(int j = 0; j < m; ++j){
            dp[i + 1][j] = min(dp[i + 1][j], dp[i][j] + 1);
            cur = j;
            if(b[i + 1] == 'A'){
                dp[i + 1][aa[j]] = min(dp[i + 1][aa[j]], dp[i][j]);
            } else {
                dp[i + 1][bb[j]] = min(dp[i + 1][bb[j]], dp[i][j]);
            }
        }
        // for(int j = 0; j < m; ++j){
        //     dp[1 - roll][j] = min(dp[1 - roll][j], dp[roll][j] + 1);
        //     cur = j;
        //     if(b[i + 1] == 'A'){
        //         dp[1 - roll][aa[j]] = min(dp[1 - roll][aa[j]], dp[roll][j]);
        //     } else {
        //         dp[1 - roll][bb[j]] = min(dp[1 - roll][bb[j]], dp[roll][j]);
        //     }
        // }
        // roll = 1 - roll;
    }
    
    int ans = INF;
    // For(i,m) ans = min(ans, dp[1 - roll][i]);
    For(i,m) ans = min(ans, dp[n][i]);
    W(ans);
    return 0;
}
