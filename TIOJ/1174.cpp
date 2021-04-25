#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<unistd.h>
#define FOR(i,n) for(int i=0;i<n;++i)
const int S = 1<<16;
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
char eek[20], eekp, outbuf[20], outp;
inline void W(int n){
    if(n == 0) outbuf[outp++] = '0'; 
    eekp = 0;
    while(n) eek[eekp++] = n % 10 + '0', n /= 10;
    for(--eekp; eekp >= 0; --eekp) outbuf[outp++] = eek[eekp];
    write(1, outbuf, outp);
}

#include<algorithm>
const int N = 1e5, INF = 2147483647;
int n, m, ans = INF;
int a[N], b[N], u, v;

int main(){
	n = R(), m = R();
	FOR(i, n) a[i] = R();
	FOR(i, m) b[i] = R();
	std::sort(a, a + n);
	std::sort(b, b + m);
	for(; u < n and v < m; ++(a[u] < b[v] ? u : v))
		ans = std::min(ans, abs(a[u] - b[v]));
	W(ans);
}