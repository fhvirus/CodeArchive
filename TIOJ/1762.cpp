#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
#define FOR(i,n) for(int i=1;i<=n;++i)
const int S = 1<<20;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) ? EOF : *p++;
}
inline short R(){
	short ans = 0; char c = readchar();
	while((c<'0'||c>'9')&&c!=EOF) c=readchar();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return ans;
}

#include<cstring>
const int N = 1001;
int n, m, r;
short a[N][N];
int tmp[N], ans;
inline int max(int a, int b){
	return a > b ? a : b;
}

int main(){
	n = R(), m = R(), r = R();
	FOR(i, n) FOR(j, m) a[i][j] = R();
	FOR(u, n){
		memset(tmp, 0, (n + 1)<<2);
		for(int d = u; d <= n; ++d){
			FOR(p, m) tmp[p] += a[d][p];
			for(int front = 1, back = 1, sum = 0; front <= m; ++front){
				sum += tmp[front];
				while(sum > r) sum -= tmp[back], ++back;
				ans = max(ans, (front - back + 1) * (d - u + 1));
			}
		}
	}
	printf("%d\n", ans);
}