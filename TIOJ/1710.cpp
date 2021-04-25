#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
#include<cstring>
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
const int V = 1<<17;
struct BIT{
	short val[V+1];
	void init(){
		memset(val, 0, sizeof(val));
	}
	int query(int p){
		int sum = 0;
		while(p) sum += val[p], p ^= (p & -p);
		return sum;
	}
	void insert(int p){
		while(p <= V) ++val[p], p += (p & -p);
	}
} eek;

const int N = 50000;
int t, n, a[N], minthen[N], maxthen;
long long ans;

int main(){
	t = R();
	for(; t; --t){
		n = R(); ans = 0;

		eek.init();
		for(int i = 0; i < n; ++i){
			a[i] = R();
			minthen[i] = eek.query(a[i]-1);
			eek.insert(a[i]);
		}

		eek.init();
		for(int i = n-1; i >= 0; --i){
			maxthen = eek.query(V - a[i] - 1);
			eek.insert(V - a[i]);
			ans += minthen[i]*maxthen + (i - minthen[i])*(n-i-1 - maxthen);
		}

		printf("%lld\n", ans);
	}
}