#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
#define FOR(i,n) for(int i=0;i<n;++i)
inline char readchar(){
	const int S = 1<<20;
	static char buf[S], *p = buf, *q = buf;
	if(p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) return EOF;
	return *p++;
}
inline int R(){
	int ans = 0, c = readchar(), minus = false;
	while((c<'0'||c>'9')&&c!='-'&&c!=EOF) c=readchar();
	if(c=='-') minus = true, c = readchar();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return minus ? -ans : ans;
}
inline int max(int a, int b){
	return a > b ? a : b;
}
inline int min(int a, int b){
	return a < b ? a : b;
}

const int N = 1000000;
int t, n, a[N], mn, mx, ans;
bool yes[N];

int main(){
	t = R();
	for(; t; --t){
		n = R();
		FOR(i,n) a[i] = R();

		mx = a[0], mn = a[n-1], ans = 0;
		for(int i = 1; i < n-1; ++i)
			yes[i] = a[i] > mx, mx = max(mx, a[i]);
		for(int i = n-2; i > 0; --i)
			ans += (yes[i] and a[i] < mn), mn = min(mn, a[i]);

		printf("%d\n", ans);
	}
}