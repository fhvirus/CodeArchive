#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma loop_opt(on)
#include<cstdio>
const int S = 1<<18;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) ? EOF : *p++;
}
inline int R(){
	int ans = 0, c = readchar();
	while(c<'0') c=readchar();
	while(c>='0') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return ans;
}

#include<algorithm>
const int N = 1000;
int t, n;
struct point{
	int x, y;
	bool operator<(const point &rhs) const{
		return x != rhs.x ? x < rhs.x : y < rhs.y;
	}
} p[N];
struct edge{
	int c, a, b;
	bool operator<(const edge &rhs) const{
		return c < rhs.c;
	}
} e[N<<1];
int ptr;

int dsu[N];
inline int Find(int a){
	return a == dsu[a] ? a : dsu[a] = Find(dsu[a]);
}
inline void Union(int a, int b){
	(Find(a) != Find(b)) && (dsu[dsu[b]] = dsu[a]);
}

int last[N+1];

int main(){
	t = R();
	for(; t; --t){
		n = R();
		for(int i = 0; i <= 1000; ++i) last[i] = -1;
		for(int i = 0; i < n; ++i)
			p[i].x = R(), p[i].y = R(), dsu[i] = i;
		std::sort(p, p + n);

		ptr = 0;
		for(int i = 0; i < n; ++i){
			if(i > 0 and p[i].x == p[i-1].x)
				e[ptr++] = {p[i].y - p[i-1].y, i, i-1};
			if(last[p[i].y] != -1)
				e[ptr++] = {p[i].x - p[last[p[i].y]].x, i, last[p[i].y]};
			last[p[i].y] = i;
		}
		std::sort(e, e + ptr);

		int ans = 0;
		for(int i = 0; i < ptr; ++i){
			if(Find(e[i].a) == Find(e[i].b)) continue;
			Union(e[i].a, e[i].b);
			ans += e[i].c;
		}
		printf("%d\n", ans);
	}
}