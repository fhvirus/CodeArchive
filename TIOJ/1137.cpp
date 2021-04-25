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
	int ans = 0, c = readchar();
	while((c<'0'||c>'9')&&c!=EOF) c=readchar();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return ans;
}
inline int min(int a, int b){
	return a < b ? a : b;
}

const int N = 10001;
int n, m, T;
int to[200000], head[N], prv[200000];

int pre[N], low[N], t, cuts;
bool isCut[N];
void dfs(int u, int p){
	pre[u] = low[u] = ++t;
	int cnt = 0, v;
	for(int i = head[u]; i != -1; i = prv[i]){
		v = to[i];
		if(pre[v] == 0){
			++cnt;
			dfs(v, u);
			low[u] = min(low[u], low[v]);
			if(low[v] >= pre[u]){
				isCut[u] = true;
			}
		} else if(pre[v] < pre[u] and v != p){
			low[u] = min(low[u], pre[v]);
		}
	}
	if(p == 0 and cnt == 1)
		isCut[u] = false;
	if(isCut[u]) cuts++;
}

int main(){
	T = R();
	for(;T;--T){
		n = R(); m = R();
		cuts = 0; t = 0;
		for(int i = 1; i <= n; ++i){
			pre[i] = 0;
			isCut[i] = false;
			head[i] = -1;
		}
		for(int a, b, i = 0; m; --m){
			a = R(); b = R();
			to[i] = b; prv[i] = head[a]; head[a] = i++;
			to[i] = a; prv[i] = head[b]; head[b] = i++;
		}
		dfs(1, 0);
		if(cuts == 0) puts("0\n0");
		else {
			printf("%d\n", cuts);
			for(int i = 1; i <= n; ++i)
				if(isCut[i]) printf("%d ", i);
			puts("");
		}
	}
}