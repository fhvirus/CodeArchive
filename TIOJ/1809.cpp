#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
#define FOR(i,n) for(int i=0;i<n;++i)
const int S = 1<<20;
inline char readchar(){
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
char outbuf[S<<4];
int outp;

#include<algorithm>
const int N = 1e6;
int n, m, q;
long long eek[N];

int main(){
	n = R(), m = R(), q = R();
	for(int a, b, i = 0; i < m; ++i){
		a = R(), b = R();
		if(a > b) std::swap(a, b);
		eek[i] = 10000000ll * a + b;
	}
	std::sort(eek, eek + m);
	m = std::unique(eek, eek + m) - eek;
	for(int c, d; q; --q){
		c = R(), d = R();
		if(c > d) std::swap(c, d);
		if(std::binary_search(eek, eek + m, 10000000ll * c + d)){
			outbuf[outp++] = 'y';
			outbuf[outp++] = 'e';
			outbuf[outp++] = 's';
			outbuf[outp++] = '\n';
		} else {
			outbuf[outp++] = 'n';
			outbuf[outp++] = 'o';
			outbuf[outp++] = '\n';
		}
		// if(outp > S - 5) fwrite(outbuf, 1, outp, stdout), outp = 0;
	}
	fwrite(outbuf, 1, outp, stdout);
}