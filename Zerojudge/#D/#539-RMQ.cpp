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
inline int max(int a, int b){
	return a > b ? a : b;
}


const int N = 1<<19;
struct max_segment_tree{
private:
	int val[N<<1];
public:
	inline void init(int n){
		FOR(i,n) val[i+N] = R();
		for(int i = N-1; i > 0; --i)
			val[i] = max(val[i<<1], val[i<<1|1]);
	}
	inline void modify(int p, int v){
		for(val[p+=N] = v; p > 1; p >>= 1)
			val[p>>1] = max(val[p], val[p|1]);
	}
	inline int query(int l, int r){ // [l,r)
		int res = -2147483648;
		for(l += N, r += N; l < r; l >>= 1, r >>= 1){
			if(l&1) res = max(res, val[l++]);
			if(r&1) res = max(res, val[--r]);
		}
		return res;
	}
} mst;

int n, m, a, b;

int main(){
	n = R(); mst.init(n);
	m = R();
	for(; m; --m){
		a = R(); b = R();
		printf("%d\n", mst.query(a < b ? a-1 : b-1, a > b ? a : b));
	}
}