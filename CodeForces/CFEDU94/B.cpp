#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma loop_opt(on)
#include<cstdio>
#define FOR(i,n) for(int i=0;i<n;++i)
const int S = 1<<20;
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
using namespace std;
int t, p, f, cnts, cntw, s, w;

int main(){
	t = R();
	for(; t; --t){
		p = R(), f = R();
		cnts = R(), cntw = R();
		s = R(), w = R();
		if(s > w) swap(s, w), swap(cnts, cntw);
		if(p + f > cnts*s + cntw*w) printf("%d\n", cnts + cntw);
		else if(p + f > cnts * s) printf("%d\n", cnts + (p + f - cnts * s) / w);
		else printf("%d\n", (p + f)/s);
	}
}