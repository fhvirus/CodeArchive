#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma loop_opt(on)
#include<cstdio>
const int S = 1<<20;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) ? EOF : *p++;
}
inline int R(){
	int ans = 0, c = readchar();
	while(c<'0') c=readchar();
	while(c>='0') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return ans;
}
inline int min(int a, int b){
	return a < b ? a : b;
}

int n, a;
int stk[1000000], top;
long long ans;

int main(){
	n = R();
	for(int i = 0; i < n; ++i){
		a = R();
		while(top > 0 and stk[top-1] < a)
			--top, ans += (top == 0 ? a : min(a, stk[top-1]));
		stk[top++] = a;
	}
	--top;
	for(int i = 0; i < top; ++i) ans += stk[i];
	printf("%lld\n", ans);
}