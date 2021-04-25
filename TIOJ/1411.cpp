#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
#define FOR(i,n) for(int i=1;i<=n;++i)
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

const int N = 1e6+1;
int n, s, a, ans;

#include<algorithm>
int m[N<<1];

int main(){
	while(true){
		n = R();
		if(n == 0) break;
		ans = 0; s = 0;
		std::fill(m + N - n, m + N + n, -1);
		m[N] = 0;
		FOR(i,n){
			a = R(), s += (a == 0 ? 0 : (a < 0 ? -1 : 1));
			if(m[s+N] == -1) m[s+N] = i;
			else ans = std::max(ans, i - m[s+N]);
		}
		printf("%d\n", ans);
	}
	return 0;
}