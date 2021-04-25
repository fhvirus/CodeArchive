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
const int N = 1e4, M = 4 * 1e4;
int n, m;
int head[N], to[M<<1], prv[M<<1];
int low[N], pre[N], t;
int stk[N], top;
int bcc[N], bcccnt, id[N], bcchead[N];

inline int min(int a, int b){
	return a < b ? a : b;
}

void dfs(int u, int b){
	low[u] = pre[u] = ++t;
	stk[top++] = u;
	for(int e = head[u], v; e != -1; e = prv[e]){
		v = to[e];
		if(pre[v] == 0){
			dfs(v, e^1);
			low[u] = min(low[u], low[v]);
		} else if(pre[v] < pre[u] and e != b){
			low[u] = min(low[u], pre[v]);
		}
	}
	if(low[u] == pre[u]){
		++bcccnt;
		bcchead[bcccnt] = u;
		int v;
		do bcc[v = stk[--top]] = bcccnt, bcchead[bcccnt] = min(bcchead[bcccnt], v);
		while(v != u);
	}
}

int main(){
	n = R(), m = R();
	FOR(i, n) head[i] = -1, id[i] = i;
	for(int a, b, i = 0; m; --m){
		a = R(), b = R();
		to[i] = b, prv[i] = head[a], head[a] = i++;
		to[i] = a, prv[i] = head[b], head[b] = i++;
	}
	dfs(0, -1);
	std::sort(id, id + n, [](int a, int b){
		return bcchead[bcc[a]] != bcchead[bcc[b]] ? bcchead[bcc[a]] < bcchead[bcc[b]] : a < b;
	});
	int jizz = 1;
	printf("1: 0 ");
	for(int i = 1; i < n; ++i){
		if(bcc[id[i]] != bcc[id[i-1]]){
			printf("\n%d: ", ++jizz);
		}
		printf("%d ", id[i]);
	}
}