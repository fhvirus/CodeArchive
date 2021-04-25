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
inline int readint(){
	int ans = 0, c = readchar();
	while((c<'0'||c>'9')&&c!=EOF) c=readchar();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return ans;
}
inline short R(){
	short ans = 0; char c = readchar();
	while((c<'0'||c>'9')&&c!=EOF) c=readchar();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return ans;
}
inline int min(int a, int b){
	return a < b ? a : b;
}

const int N = 1e7 + 2;
const short INF = 32767;

int n, l, r, ans, jizz;
short h[(N<<1) + 1];
int z[(N<<1) + 1];

int main(){
	n = readint()*2 - 1;
	for(int i = 0; i < n; i += 2){
		h[i] = R();
		h[i+1] = INF;
	}

	z[0] = 0; l = r = 0;
	for(int i = 1; i < n; ++i){
		jizz = r >= i ? min(z[(l<<1)-i], r - i) : 0;
		for(;i - jizz >= 0 and i + jizz < n and h[i - jizz] == h[i + jizz]; ++jizz);
		if(i + jizz > r){ l = i; r = i + jizz;}
		ans = ans > jizz ? ans : jizz;
		z[i] = jizz;
	}

	printf("%d", ans-2);
}