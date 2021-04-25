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
	while(c<'0' and c != EOF) c=readchar();
	while(c>='0') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return ans;
}

const int N = 5e5;
int n, m, h[N];
inline void add(int a, int b){
	if(a > b) a ^= b, b ^= a, a ^= b;
	int jizz = ((long long) a * 131 + b) % 1004535809;
	h[a] = (h[a] + jizz) % 1004535809;
	h[b] = (h[b] - jizz + 1004535809) % 1004535809;
}
inline void sub(int a, int b){
	if(a > b) a ^= b, b ^= a, a ^= b;
	int jizz = ((long long) a * 131 + b) % 1004535809;
	h[b] = (h[b] + jizz) % 1004535809;
	h[a] = (h[a] - jizz + 1004535809) % 1004535809;
}
char outbuf[S];
int outp;

int main(){
	n = R(), m = R();
	for(int cmd, a, b, k; m; --m){
		cmd = R();
		if(cmd == 0) add(R(), R());
		else if(cmd == 1) sub(R(), R());
		else {
			long long sum = 0;
			k = R();
			for(; k; --k)
				sum = (sum + h[R()]) % 1004535809;
			outbuf[outp++] = (sum == 0 ? '1' : '0');
			outbuf[outp++] = '\n';
			if(outp > S-4) fwrite(outbuf, 1, outp, stdout), outp = 0;
		}
	}
	fwrite(outbuf, 1, outp, stdout);
}