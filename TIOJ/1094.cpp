#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
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
inline int max(int a, int b, int c){
	return a > b ? (a > c ? a : c) : (b > c ? b : c);
}

int n, a, ans;

int main(){
	while(true){
		n = R();
		if(n == 0) break;
		ans = 0;
		for(int i = 0; i < n; ++i){
			a = R();
			ans = max(ans, ans ^ a, a);
		}
		printf("%d\n", ans);
	}
}