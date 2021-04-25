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

int main(){
	int t, n, m, a[1000], b, ans;
	bool flag;
	t = R();
	for(; t; --t){
		n = R(), m = R();
		flag = false;
		FOR(i,n) a[i] = R();
		FOR(i,m){
			b = R();
			if(!flag){
				FOR(j,n) if(b == a[j]){ flag = true; ans = b; break;}
			}
		}
		if(flag){
			puts("YES");
			printf("1 %d\n", ans);
		} else {
			puts("NO");
		}
	}
	return 0;
}