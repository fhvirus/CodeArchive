#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
#define FOR(i,n) for(int i=0;i<n;++i)
const int S = 1<<18;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) ? EOF : *p++;
}
inline int R(){
	int ans = 0, c = readchar(), minus = false;
	while((c<'0'||c>'9')&&c!='-'&&c!=EOF) c=readchar();
	if(c=='-') minus = true, c = readchar();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return minus ? -ans : ans;
}

#include<algorithm>
const int N = 20000;

struct BIG{
	#define BASE 1000000000000000
	long long a[4000], len;
	void mul(int b){
		int i;
		for(i = 0; i < len; ++i) a[i] *= b;
		for(i = 0; i < len; ++i) a[i+1] += a[i] / BASE, a[i] %= BASE;
		if(a[i] and len <= i) len = i + 1;
	}
	void print(){
		printf("%lld", a[len-1]);
		for(int i = len - 2; i >= 0; --i)
			printf("%015lld", a[i]);
		puts("");
	}
} ans;
int n, a[N], b[N];
int main(){
	n = R();
	FOR(i, n) a[i] = R();
	FOR(i, n) b[i] = R();
	std::sort(a, a + n);
	std::sort(b, b + n);
	ans.a[0] = 1; ans.len = 1;
	FOR(i, n) ans.mul(a[i] + b[n - i - 1]);
	ans.print();
}