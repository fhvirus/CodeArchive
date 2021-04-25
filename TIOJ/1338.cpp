#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma loop_opt(on)
#include"lib1338.h"
int n;
long long g[21][1000005], m[21][1000005];
inline long long gcd(long long a, long long b){
    while(b){
        a %= b;
        a ^= b, b ^= a, a ^= b;
    }
    return a;
}
inline long long min(long long a, long long b){
    return a < b ? a : b;
}
void init(int N, long long C[]){
    n = N;
    for(int i = 0; i < n; ++i) g[0][i] = m[0][i] = C[i];
    for(int i = 1; i < 21; ++i)
        for(int j = 0; j + (1<<i) - 1 < n; ++j)
            g[i][j] = gcd(g[i-1][j], g[i-1][j + (1 << (i-1))]),
            m[i][j] = min(m[i-1][j], m[i-1][j + (1 << (i-1))]);
}
int query(int L, int R){
    int len = 31 - __builtin_clz(R - L);
    int gc = gcd(g[len][L], g[len][R - (1<<len)]),
        mn = min(m[len][L], m[len][R - (1<<len)]);
    return gc == mn;
}