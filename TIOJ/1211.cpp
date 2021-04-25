#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
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

const int N = 10001;
int n, m;

int dsu[N];
inline void initDSU(){
	for(int i = 1; i <= n; ++i)
		dsu[i] = i;
}
inline int Find(int a){
	return dsu[a] == a ? a : dsu[a] = Find(dsu[a]);
}
inline void Union(int a, int b){
	if(Find(a) == Find(b)) return;
	dsu[Find(b)] = Find(a);
}

#include<algorithm>
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
		int ans = 0;
		for(int i = 0; i < m; ++i){
			while(Find(E[i].u) == Find(E[i].v)) ++i;
			Union(E[i].u, E[i].v);
			ans += E[i].c;
		}
	}
	return 0;
}