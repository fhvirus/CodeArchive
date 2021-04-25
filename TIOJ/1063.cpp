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
	int ans = 0;
	char c = readchar();
	while((c<'0'||c>'9')&&c!='-'&&c!=EOF) c=readchar();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return ans;
}
inline int max(int a, int b){
	return a > b ? a : b;
}
inline int min(int a, int b){
	return a < b ? a : b;
}

int m, n, g[201][201], l[201], r[201];
int stack[201], sp;
int ans;

int main(){
	m = R(); n = R();
	FOR(i,m)FOR(j,n) g[i][j] = (R()==1) ? g[i-1][j] + 1 : 0;

	FOR(i,m){
		g[i][0] = -8e7;
		stack[(sp=1)-1] = 0;
		FOR(j,n){
			while(g[i][stack[sp-1]] >= g[i][j])
				r[stack[--sp]] = j;
			l[j] = stack[sp-1];
			stack[sp++] = j;
		}

		while(sp > 0)
			r[stack[--sp]] = n+1;

		FOR(j,n) ans = max(ans, g[i][j] * (r[j]-1-l[j]));
	}
	printf("%d", ans);
}