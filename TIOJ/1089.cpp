#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
inline char readchar(){
	const int S = 1<<14;
	static char buf[S], *p = buf, *q = buf;
	if(p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) return EOF;
	return *p++;
}
inline short R(){
	short ans = 0, c = readchar();
	while((c<'0'||c>'9')&&c!=EOF) c=readchar();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return ans;
}
#define MAXN 1001
#define N 10000
short match[MAXN], vis[MAXN];
short n, k, t;
short to[N], head[MAXN], prv[N];
bool dfs(short u){
	if(vis[u] == t) return false;
	vis[u] = t;
	for(short v = head[u]; v != -1; v = prv[v])
		if(!match[to[v]] or dfs(match[to[v]])){
			match[u] = to[v];
			match[to[v]] = u;
			return true;
		}
	return false;
}

int main(){
	short ans = 0, i, r, c;
	n = R(); k = R();
	for(i = 1; i <= n; ++i){
		match[i] = match[i + n] = 0;
		vis[i] = vis[i + n] = 0;
	}
	for(i = 0; i < k<<1; ++i) head[i] = -1;
	for(i = 0;k;--k){
		r = R(); c = R();
		to[i] = c+n;
		prv[i] = head[r]; head[r] = i++;
	}
	for(i = 1; i <= n; ++i)
		if(match[i] == 0){
			t++;
			ans += dfs(i);
		}
	printf("%d", ans);
	return 0;
}