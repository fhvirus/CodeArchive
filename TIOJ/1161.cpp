#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<unistd.h>
#define FOR(i,n) for(int i=0;i<n;++i)
const int S = 1<<16;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+read(0, buf, S))==buf) ? -1 : *p++;
}
inline int R(){
	int ans = 0, c = readchar();
	while(c<'0') c=readchar();
	while(c>='0') ans=(ans*10)+(c^'0'), c=readchar();
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
    if(outp > S-15) write(1, outbuf, outp), outp = 0;
}

#include<algorithm>
#include<queue>
#define N 1000000
int t, n, k, ans;
struct point{ int x, y;} p[N];
std::priority_queue<int> ys;

int main(){
	t = R();
	for(; t; --t){
		n = R(), k = R(); ys = {};
		FOR(i,n) p[i].x = R(), p[i].y = R();
		std::sort(p, p + n, [](point a, point b){ return a.x < b.x;});
		FOR(i,k) ys.push(p[i].y);
		ans = p[k-1].x + ys.top();
		for(int i = k; i < n; ++i)
			ys.push(p[i].y),
			ys.pop(),
			ans = std::min(ans, p[i].x + ys.top());
		W(ans);
	}
	write(1, outbuf, outp);
	return 0;
}