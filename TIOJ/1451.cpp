#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma loop_opt(on)
#include<cstdio>
const int S = 1<<20;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) ? EOF : *p++;
}
inline int R(){
	int ans = 0; char c = readchar();
	while(c<'0') c=readchar();
	while(c>='0') ans=ans*10+(c^'0'), c=readchar();
	return ans;
}

const int N = 100001;
int n, m;
int head[N], to[N], prv[N];
int pre[N], low[N], t, scc[N];
int stk[N], top;
bool inStack[N];
int in[N];

inline int min(int a, int b){
	return a < b ? a : b;
}

void tarjan(int u){
	low[u] = pre[u] = ++t;
	stk[top++] = u, inStack[u] = true;
	for(int i = head[u], v; i != -1; i = prv[i]){
		v = to[i];
		if(pre[v] == 0)
			tarjan(v), low[u] = min(low[u], low[v]);
		else if(inStack[v])
			low[u] = min(low[u], pre[v]);
	}
	if(low[u] == pre[u]){
		int v;
		do{
			v = stk[--top];
			inStack[v] = false;
			scc[v] = u;
		} while(v != u);
	}
}

int main(){
	n = R(), m = R();
	for(int i = 1; i <= n; ++i)
		head[i] = -1;
	for(int a, b, i = 0; i < m; ++i){
		a = R(), b = R();
		to[i] = b, prv[i] = head[a], head[a] = i;
	}
	for(int i = 1; i <= n; ++i)
		if(pre[i] == 0) tarjan(i);
	for(int i = 1; i <= n; ++i)
		for(int v = head[i]; v != -1; v = prv[v])
			if(scc[to[v]] != scc[i]) in[scc[to[v]]]++;

	int ans = 0;
	for(int i = 1; i <= n; ++i)
		if(scc[i] == i and in[i] == 0) ++ans;
	printf("%d", ans);
}