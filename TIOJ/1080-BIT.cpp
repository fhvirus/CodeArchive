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

#include<algorithm>
#include<cstring>
using namespace std;
#define lowbit(x) (x&(-x))
#define N 100001
int n, a[N], bit[N], e, t;
long long ans;

long long sum(int p){
	long long s = 0;
	for(;p>0;p-=lowbit(p)) s += bit[p];
	return s;
}

void add(int p){
	for(;p<=n;p+=lowbit(p)) ++bit[p];
}

int main(){
	while(true){
		if((n=R()) == 0) break;
		FOR(i,n) a[i] = bit[i] = R();
		sort(bit, bit+n);
		e = unique(bit, bit+n) - bit;
		FOR(i,n) a[i] = lower_bound(bit, bit+e, a[i]) - bit + 1;
		memset(bit, 0, sizeof(bit));
		ans = 0;
		FOR(i,n){
			ans += i - sum(a[i]);
			add(a[i]);
		}
		printf("Case #%d: %lld\n", ++t, ans);
	}
}