#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
#define FOR(i,n) for(int i=0;i<n;++i)
typedef unsigned int uint;
inline char readchar(){
	const int S = 1<<20;
	static char buf[S], *p = buf, *q = buf;
	if(p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) return EOF;
	return *p++;
}
inline int R(){
	int ans = 0, c = readchar();
	while((c<'0'||c>'9')&&c!=EOF) c=readchar();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return ans;
}
inline uint popcount(uint u){
    u = (u & 0x55555555) + ((u >> 1) & 0x55555555);
    u = (u & 0x33333333) + ((u >> 2) & 0x33333333);
    u = (u & 0x0F0F0F0F) + ((u >> 4) & 0x0F0F0F0F);
    u = (u & 0x00FF00FF) + ((u >> 8) & 0x00FF00FF);
    u = (u & 0x0000FFFF) + ((u >> 16) & 0x0000FFFF);
    return u;
}

uint n;
double dp[1<<20], a[20];
vector<uint> v[21];

int main(){
	n = R();
	dp[0] = 1;
	for(uint i = 0; i < (1<<n); ++i) v[popcount(i)].push_back(i);
	for(int i = 1; i <= n; ++i){
		FOR(j,n) a[j] = R()/100.0;
		for(int j: v[i]) FOR(k,n)
			if(j & (1<<k)) dp[j] = max(dp[j], dp[j^(1<<k)] * a[k]);
	}
	printf("%.2lf", dp[(1<<n)-1]*100);
}