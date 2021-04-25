#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
#define FOR(i,n) for(int i=0;i<n;++i)
const int S = 1<<20;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	if(p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) return EOF;
	return *p++;
}
inline int R(){
	int ans = 0; char c = readchar();
	while((c<'0'||c>'9')&&c!=EOF) c=readchar();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return ans;
}
char outbuf[S], eek[20];
int outp, eekp;
inline void W(int n){
    if(n == 0){outbuf[outp++] = '0'; outbuf[outp++] = ' '; return;}
    eekp = 0;
    while(n) eek[eekp++] = n % 10 + '0', n /= 10;
    for(--eekp; eekp >= 0; --eekp) outbuf[outp++] = eek[eekp];
    outbuf[outp++] = ' ';
    if(outp > S-15) fwrite(outbuf, 1, outp, stdout), outp = 0;
}

const int N = 1e6+1, E = 2e6;
int n, m, jizz[N], yike[N], s, t;
char c[N];
int Q[N], qfront, qend;
int head[N+1], to[E<<1], prv[E<<1];

int main(){
	n = R(); m = R();
	for(int i = 1; i <= n; ++i) head[i] = -1;
	for(int a, b, i = 0; m; --m){
		a = R(), b = R();
		to[i] = b; prv[i] = head[a]; head[a] = i++;
		to[i] = a; prv[i] = head[b]; head[b] = i++;
	}
	for(int i = 1; i <= n; ++i){
		if(c[i] != 0) continue;
		c[i] = 1;
		Q[qend++] = i;
		while(qfront < qend){
			int u = Q[qfront++];
			(c[u] == 1 ? jizz[s++] : yike[t++]) = u;
			for(int v = head[u]; v != -1; v = prv[v]){
				if(c[to[v]] != 0){
					if(c[to[v]] == c[u]){ puts("-1"); return 0;}
				} 
				else 
					c[to[v]] = -c[u], Q[qend++] = to[v];
			}
		}
	}
	W(s), W(t), outbuf[outp++] = '\n';
	FOR(i,s) W(jizz[i]);
	outbuf[outp++] = '\n';
	FOR(i,t) W(yike[i]);
	fwrite(outbuf, 1, outp, stdout);
}