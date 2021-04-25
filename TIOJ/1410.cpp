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
	int ans = 0, c = readchar();
	while((c<'0'||c>'9')&&c!=EOF) c=readchar();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return ans;
}
inline int max(int a, int b){
	return a > b ? a : b;
}

const int N = 1e6;
int n, sum[(N<<1)+1], des[N<<1], l[N], r[N], e;

#include<algorithm>
#include<cstring>

int main(){
	while(true){
		n = R();
		if(n == 0) break;
		e = 0;
		for(int i = 0; i < n; ++i)
			des[e++] = l[i] = R(),
			des[e++] = r[i] = R();

		std::sort(des, des + e);
		e = std::unique(des, des + e) - des;
		memset(sum, 0, e<<2);
		for(int i = 0; i < n; ++i)
			++sum[std::lower_bound(des, des+e, l[i]) - des],
			--sum[std::lower_bound(des, des+e, r[i]) - des + 1];

		int ans = sum[0];
		for(int i = 1; i < e; ++i)
			sum[i] += sum[i-1], ans = max(ans, sum[i]);

		printf("%d\n", ans);
	}
	return 0;
}