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
	int ans = 0, c = readchar();
	while((c<'0'||c>'9')&&c!=EOF) c=readchar();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return ans;
}
#define int64_t long long
inline int64_t p(int64_t x, int e){
	int64_t r = 1;
	while(e) (e&1)&&(r*=x), x*=x, e>>=1;
	return r;
}

int64_t f(int a){
	return (p(3, a) + ((a&1)?-3:3))>>2;
}

int n, a;
int main(){
	for(n = R(); n; --n){
		a = R();
		printf("%lld\n", f(a));
	}
	return 0;
}