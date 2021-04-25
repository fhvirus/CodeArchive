#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma loop_opt(on)
#include<unistd.h>
const int S = 1<<14;
#define FOR(i, n) for(int i = 0; i < n; ++i)
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+read(0,buf,S))==buf) ? -1 : *p++;
}
inline int R(){
	int ans = 0; char c = readchar();
	while(c<'0') c=readchar();
	while(c>='0') ans=ans*10+(c^'0'), c=readchar();
	return ans;
}
char outbuf[20], eek[20];
int outp, eekp;
inline void W(int n){
    if(n == 0) outbuf[outp++] = '0';
    eekp = 0;
    while(n) eek[eekp++] = n % 10 + '0', n /= 10;
    for(--eekp; eekp >= 0; --eekp) outbuf[outp++] = eek[eekp];
    write(1, outbuf, outp);
}

#include<cstdio>
const int N = 50, M = 10001;
int m, n, p, dp[M], w[N][N], v[N][N], cnt[N];

int main(){
	m = R(), n = R(), p = R();
	FOR(i, n){
		int k = 0;
		for(int j = 0; j < p; ++j, ++k)
			w[i][k] = R(), v[i][k] = R(), (w[i][k] >= w[i][k-1] and v[i][k] <= v[i][k-1]) and --k;
		cnt[i] = k;
	}
	FOR(k, n)
		for(int i = m; i >= 0; --i)
			FOR(j, cnt[k])
				(i - w[k][j] >= 0 and dp[i] < dp[i - w[k][j]] + v[k][j]) and (dp[i] = dp[i - w[k][j]] + v[k][j]);
	W(dp[m]);
	return 0;
}