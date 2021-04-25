#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
#include<algorithm>
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

long long n, e[2000], ans, si, sj;

int main(){
	while((n=R()) != 0){
		FOR(i,n) e[i] = R();
		std::sort(e, e+n);
		FOR(i,n) e[i] *= e[i];
		ans = 0;
		for(int k = 2; k < n; ++k){
			int i = 0, j = k-1;
			while(i < j){
				if(e[i] + e[j] < e[k]) ++i;
				else if(e[i] + e[j] > e[k]) --j;
				else ++ans, ++i, --j;
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}