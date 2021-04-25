#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
#define FOR(i,n) for(int i=0;i<n;++i)
const int S = 1<<18;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	if(p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) return EOF;
	return *p++;
}
inline int R(){
	int ans = 0; char c = readchar();
	while(c<'0') c=readchar();
	while(c>='0') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return ans;
}
char outbuf[S], eek[20];
int outp, eekp;
inline void W(int n){
    if(n == 0){outbuf[outp++] = '0'; outbuf[outp++] = '\n'; return;}
    if(n < 0) outbuf[outp++] = '-', n = -n;
    eekp = 0;
    while(n) eek[eekp++] = n % 10 + '0', n /= 10;
    for(--eekp; eekp >= 0; --eekp) outbuf[outp++] = eek[eekp];
    outbuf[outp++] = '\n';
    if(outp > S-15) fwrite(outbuf, 1, outp, stdout), outp = 0;
}

#include<vector>
#include<algorithm>
using namespace std;

const int L = 17, N = 1e5+1;
int n, q, a, b;
int head[N], to[N<<1], prv[N<<1];

int depth[N], anc[L][N], s[N], p, u;
void dfs(){
	s[p++] = 1;
	depth[1] = 1;
	while(p > 0){
		u = s[--p];
		for(int v = head[u]; v != -1; v = prv[v])
			if(depth[to[v]] == 0)
				depth[to[v]] = depth[u] + 1,
				anc[0][to[v]] = u,
				s[p++] = to[v];
	}
}
inline void initLCA(){
	dfs();
	for(int i = 1; i < L; ++i)
		for(int j = 1; j <= n; ++j)
			anc[i][j] = anc[i-1][anc[i-1][j]];
}
inline int LCA(int a, int b){
	if(depth[a] > depth[b]) swap(a, b);
	int d = depth[b] - depth[a];
	for(int i = L-1; i >= 0; --i)
		if((1<<i) & d) b = anc[i][b];
	if(a == b) return a;
	for(int i = L-1; i >= 0; --i)
		if(anc[i][a] != anc[i][b]){
			a = anc[i][a];
			b = anc[i][b];
		}
	return anc[0][a];
}

int main(){
	n = R(); q = R();
	int j = 0;
	FOR(i, n + 1) head[i] = -1;
	FOR(i,n-1){
		a = R(); b = R();
		to[j] = b, prv[j] = head[a], head[a] = j++;
		to[j] = a, prv[j] = head[b], head[b] = j++;
	}
	initLCA();
	int s, t, k, d, h, lca;
	for(;q;--q){
		s = R(); t = R(); k = R();
		lca = LCA(s, t); d = depth[s] + depth[t] - (depth[lca] << 1);
		if(k < 0 or k > d) W(-1);
		else if(k == 0) W(s);
		else if(k == d) W(t);
		else{
			h = depth[s] - depth[lca];
			if(k == h) W(lca);
			else if(k < h){
				for(int i = L-1; i >= 0; --i){
					if(k & (1<<i)) s = anc[i][s];
				}
				W(s);
			}
			else if(k > h and k <= d){
				k = d - k;
				for(int i = L-1; i >= 0; --i){
					if(k & (1<<i)) t = anc[i][t];
				}
				W(t);
			}
		}
	}
	fwrite(outbuf, 1, outp, stdout);
	return 0;
}