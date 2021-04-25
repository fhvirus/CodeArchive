#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma loop_opt(on)
#include<unistd.h>
#define FOR(i,n) for(int i=0;i<n;++i)
const int S = 1<<12;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+read(0,buf,S))==buf) ? -1 : *p++;
}
inline int R(){
	int ans = 0, c = readchar();
	while(c<'0') c=readchar();
	while(c>='0') ans=(ans*10)+(c^'0'), c=readchar();
	return ans;
}
char outbuf[20], eek[20];
int outp, eekp;
inline void W(long long n){
    if(n == 0) outbuf[outp++] = '0';
    eekp = 0;
    while(n) eek[eekp++] = n % 10 + '0', n /= 10;
    for(--eekp; eekp >= 0; --eekp) outbuf[outp++] = eek[eekp];
    write(1, outbuf, outp);
}

const int N = 251;
int v, e, m, s, t, w[N][N], in[N];
long long ans[N];
int Q[N], head, tail;

int main(){
	v = R(), e = R(), m = R();
	for(int i = 0, a, b; i < e; ++i)
		a = R(), b = R(), w[a][b]++, in[b]++;
	s = R(), t = R();

	ans[s] = 1;
	for(int i = 0; i < v; ++i)
		if(in[i] == 0) Q[tail++] = i;
	while(tail > head){
		int u = Q[head++];
		for(int i = 0; i < v; ++i){
			if(w[u][i] > 0){
				ans[i] = (ans[i] + ans[u] * w[u][i]) % m;
				in[i] -= w[u][i];
				if(in[i] == 0) Q[tail++] = i;
			}
		}
	}
	W(ans[t]);
}