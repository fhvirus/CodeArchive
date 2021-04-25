#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
const int S = 1<<18;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) ? EOF : *p++;
}
inline int R(){
	int ans = 0; char c = readchar();
	while((c<'0'||c>'9')&&c!=EOF) c=readchar();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return ans;
}

const int N = 10001, M = 1e6;
int n, m, ans;

short dsu[N];
inline int Find(int a){
	return dsu[a] == a ? a : dsu[a] = Find(dsu[a]);
}

#include<algorithm>
// short u[M], v[M], c[M], id[M];
struct edge{
	short u, v, c;
	bool operator< (const edge &rhs) const{
		return c < rhs.c;
	}
} E[1000000];

int main(){
	while(true){
		n = R(); m = R();
		if(n==0 and m==0) break;
		for(int i = 0; i < m; ++i){
			E[i].u = R(); E[i].v = R(); E[i].c = R();
		}
		std::sort(E, E + m);
		for(int i = 0; i <= n; ++i) dsu[i] = i;
		ans = 0;

		for(int i = 0; i < m and n > 1; ++i){
			if(Find(E[i].u) == Find(E[i].v)) continue;
			dsu[dsu[E[i].v]] = dsu[E[i].u], --n;
			ans += E[i].c;
		}
		if(n == 1) printf("%d\n", ans);
		else puts("-1");
	}
	return 0;
}