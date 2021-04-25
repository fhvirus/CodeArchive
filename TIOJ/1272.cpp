#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma loop_opt(on)
#include<cstdio>
const int S = 1<<20;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) ? EOF : *p++;
}
inline int R(){
	int ans = 0; char c = readchar();
	while(c<'0'&&c!=EOF) c=readchar();
	while(c>='0') ans=ans*10+(c^'0'), c=readchar();
	return ans;
}

const int N = 1e5+1;
int n, m, intime[N], outime[N], t;
int head[N], to[N], prv[N];
bool bit[N<<1];
void dfs(int u){
	intime[u] = ++t;
	for(int v = head[u]; v != -1; v = prv[v]) dfs(to[v]);
	outime[u] = ++t;
}
void add(int l, int r){
	for(; l <= N<<1; l += l & -l) bit[l] ^= 1;
	for(; r <= N<<1; r += r & -r) bit[r] ^= 1;
}
bool query(int p){
	bool ans = false;
	for(; p; p -= p & -p) ans ^= bit[p];
	return ans;
}
int main(){
	n = R(), m = R();
	for(int i = 1, cnt, k; i <= n; ++i){
		k = R(), head[i] = -1;
		for(int j = 0, in; j < k; ++j)
			to[cnt] = R(), prv[cnt] = head[i], head[i] = cnt++;
	}
	dfs(1);
	for(bool cmd; m; --m){
		cmd = R(), n = R(); 
		if(cmd) puts(query(intime[n]) ? "1" : "0");
		else add(intime[n], outime[n]+1);
	}
}