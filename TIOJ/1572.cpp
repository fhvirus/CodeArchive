#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma loop_opt(on)
#include<cstdio>
#define FOR(i,n) for(int i=0;i<n;++i)
const int S = 1<<18;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) ? EOF : *p++;
}
inline int R(){
	int ans = 0, c = readchar();
	while((c<'0'||c>'9')&&c!=EOF) c=readchar();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return ans;
}
char outbuf[S], eek[20];
int outp, eekp;
inline void W(int n){
    if(n == 0){outbuf[outp++] = '0'; return;}
    eekp = 0;
    while(n) eek[eekp++] = n % 10 + '0', n /= 10;
    for(--eekp; eekp >= 0; --eekp) outbuf[outp++] = eek[eekp];
    if(outp > S-15) fwrite(outbuf, 1, outp, stdout), outp = 0;
}

const int N = 1000001;

int n, m, A, B;
int dist[N];
int to[N<<1], head[N], prv[N<<1];
int Q[N], qh = 0, qt = 0;

int main(){
	n = R(); m = R(); A = R(); B = R();
	for(int i = 0; i <= n; ++i) head[i] = -1;
	for(int a, b, i = 0; m; --m){
		a = R(); b = R();
		to[i] = b; prv[i] = head[a]; head[a] = i++;
		to[i] = a; prv[i] = head[b]; head[b] = i++;
	}

	dist[B] = 1;
	Q[qt++] = B;
	int now, v, i;
	while(qt > qh){
		now = Q[qh++];
		for(v = head[now]; v != -1; v = prv[v]){
			i = to[v];
			if(dist[i]) continue;
			dist[i] = dist[now] + 1;
			Q[qt++] = i;
		}
		if(dist[A]) break;
	}

	W(dist[A]-2);
	outbuf[outp++] = '\n';
	W(A);

	int cur = A, nxt;
	while(cur != B){
		nxt = n+1;
		for(v = head[cur]; v != -1; v = prv[v]){
			i = to[v];
			if(dist[i] == dist[cur] - 1){
				nxt = (nxt < i ? nxt : i);
			}
		}
		outbuf[outp++] = '-';
		W(nxt);
		cur = nxt;
	}
	fwrite(outbuf, 1, outp, stdout);
	return 0;
}