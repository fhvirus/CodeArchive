#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma loop_opt(on)
#include<cstdio>
#define FOR(i,n) for(int i=1;i<=n;++i)
const int S = 1<<16;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) ? EOF : *p++;
}
inline int R(){
	int ans = 0, c = readchar();
	while(c<'-') c=readchar();
	if(c=='-'){while((c = readchar()) >= '0'); return -1;};
	while(c>='0') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return ans;
}
char outbuf[S], eek[20];
int outp, eekp;
inline void W(int n){
    if(n == 0) outbuf[outp++] = '0';
    eekp = 0;
    while(n) eek[eekp++] = n % 10 + '0', n /= 10;
    for(--eekp; eekp >= 0; --eekp) outbuf[outp++] = eek[eekp];
    outbuf[outp++] = '\n';
    if(outp > S-15) fwrite(outbuf, 1, outp, stdout), outp = 0;
}

const int N = 101, INF = 2147483647;
int n, adj[N][N], in;
int wa[N], wb[N], mb[N], va[N], vb[N], t;

inline int min(int a, int b){
	return a < b ? a : b;
}
inline int max(int a, int b){
	return a > b ? a : b;
}

bool dfs(int u){
	va[u] = t;
	FOR(i, n) if(vb[i] != t and wa[u] + wb[i] == adj[u][i]){
		vb[i] = t;
		if(mb[i] == 0 or dfs(mb[i])){
			mb[i] = u;
			return true;
		}
	}
	return false;
}

inline void upd(){
	int jizz = INF;
	FOR(i, n) if(va[i] == t)
		FOR(j, n) if(vb[j] != t)
			jizz = min(jizz, wa[i] + wb[j] - adj[i][j]);
	FOR(i, n){
		if(va[i] == t) wa[i] -= jizz;
		if(vb[i] == t) wb[i] += jizz;
	}
}

int main(){
	while((n = R()) != 0){
		t = 0;
		FOR(i, n){
			wa[i] = wb[i] = 0;
			mb[i] = 0;
			va[i] = vb[i] = 0;
			FOR(j, n)
				in = max(R(), 0), adj[i][j] = in, wa[i] = max(wa[i], in);
		}
		FOR(i, n){
			while(true){
				++t;
				if(!dfs(i)) upd();
				else break;
			}
		}
		int ans = 0;
		FOR(i, n) ans += adj[mb[i]][i];
		W(ans);
	}
	fwrite(outbuf, 1, outp, stdout);
}