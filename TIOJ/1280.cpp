#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroint-loops")
#pragma loop_opt(on)
#include<unistd.h>
#define FOR(i,n) for(int i=0;i<n;++i)
const int S = 1<<14;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+read(0,buf,S))==buf) ? -1 : *p++;
}
inline int R(){
	int ans = 0, c = readchar(), minus = false;
	while(c<'-') c=readchar();
	if(c=='-') minus = true, c = readchar();
	while(c>='0') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return minus ? -ans : ans;
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

#include<algorithm>
#define N 10000
int n, ans;
struct point{
	int x, y;
	inline bool operator<(const point &rhs) const{
		return x != rhs.x ? x < rhs.x : y < rhs.y;
	}
	inline int operator*(const point &rhs) const{
		return x * rhs.y - y * rhs.x;
	}
} P[N], L[N], U[N], v1, v2;
inline bool jizz(point o, point a, point b){
	v1 = {a.x - o.x, a.y - o.y};
	v2 = {b.x - o.x, b.y - o.y};
	return v1 * v2 <= 0;
}
int l, u;

int main(){
	n = R();
	FOR(i, n) P[i] = {R(), R()};
	std::sort(P, P + n);
	for(int i = 0; i < n; ++i){
		while(l >= 2 and jizz(L[l-2], L[l-1], P[i])) --l;
		while(u >= 2 and jizz(U[u-2], P[i], U[u-1])) --u;
		L[l++] = P[i];
		U[u++] = P[i];
	}

	for(int i = 1; i < l; ++i)
		ans += L[i] * L[i-1];

	for(int i = u-2; i >= 0; --i)
		ans += U[i] * U[i+1];

	W((-ans + 1) / 2);
}