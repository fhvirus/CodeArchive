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
	int ans = 0, c = readchar(), minus = false;
	while((c<'0'||c>'9')&&c!='-'&&c!=EOF) c=readchar();
	if(c=='-') minus = true, c = readchar();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return minus ? -ans : ans;
}

#include<algorithm>
using namespace std;
const int N = 1e5, INF = 8e7;
int na, nb, x, y, ansa, ansb;
struct line{
	int l, r;
	line(){}
	line(int l, int r): l(l), r(r){}
	bool operator<(const line &rhs) const{
		return l != rhs.l ? l < rhs.l : r < rhs.r;
	}
} A[N], B[N];

inline int solve(int n, line a[]){
	if(x == y){
		FOR(i, n) if(a[i].l <= x and a[i].r >= x) return 1;
		return INF;
	}
	int ans = 0, p = x, nxt = x, i = 0;
	while(p < y){
		while(i < n and a[i].l <= p) nxt = max(nxt, a[i].r), ++i;
		if(nxt <= p) return INF;
		++ans, p = nxt;
	}
	return ans;
}

int main(){
	while(true){
		na = R(), nb = R();
		if(na == 0) return 0;
		FOR(i,na) A[i] = {R(), R()};
		FOR(i,nb) B[i] = {R(), R()};
		x = R(), y = R();
		sort(A, A + na);
		sort(B, B + nb);
		ansa = solve(na, A);
		ansb = solve(nb, B);
		if(ansa == INF and ansb == INF) puts("TIE");
		else if(ansa > ansb) puts("B WIN");
		else puts("A WIN");
	}
}