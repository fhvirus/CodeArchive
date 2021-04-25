#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma loop_opt(on)
#include<cstdio>
inline int R(){
	int ans = 0; char c = getchar_unlocked();
	while(c<'0') c=getchar_unlocked();
	while(c>='0') ans=(ans<<3)+(ans<<1)+(c^'0'), c=getchar_unlocked();
	return ans;
}
char eek[20], eekp;
inline void W(int n){
    if(n == 0){putchar_unlocked('0'); return;}
    eekp = 0;
    while(n) eek[eekp++] = n % 10 + '0', n /= 10;
    for(--eekp; eekp >= 0; --eekp) putchar_unlocked(eek[eekp]);
}

const int N = 10010;
short n, head[N], to[N<<1], prv[N<<1], match[N], t, vis[N], ans;

bool dfs(int u){
	if(vis[u] == t) return false;
	vis[u] = t;
	for(int v = head[u]; v != -1; v = prv[v])
		if(match[to[v]] == 0 or dfs(match[to[v]])){
			match[u] = to[v];
			match[to[v]] = u;
			return true;
		}
	return false;
}

int main(){
	n = R();
	for(int i = 1; i <= n; ++i)
		head[i] = -1;
	for(int a, b, c = 0, i = 0; i < n-1; ++i){
		a = R(), b = R();
		to[c] = b, prv[c] = head[a], head[a] = c++;
		to[c] = a, prv[c] = head[b], head[b] = c++;
	}
	for(int i = 1; i <= n; ++i)
		if(match[i] == 0)
			++t, ans += dfs(i);
	W(ans);
}