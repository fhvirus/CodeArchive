#include<cstdio>
#include<algorithm>
typedef int64_t ll;
inline char readchar(){
	const int S = 1<<14;
	static char buf[S], *p = buf, *q = buf;
	if(p==q and (q=(p=buf)+fread(buf,1,S,stdin))==buf) return EOF;
	return *p++;
}
inline int readint(){
	int ans = 0, c = readchar(), minus = false;
	while((c<'0' or c>'9')and c!='-' and c!=EOF) c = readchar();
	if(c == '-') minus = true, c = readchar();
	while(c >= '0' and c <= '9') ans = (ans<<3)+(ans<<1)+(c-'0'), c=readchar();
	return minus ? -ans : ans;
}
const int MAXN = 1e5;
struct point{
	int x, y;
} P[MAXN], L[MAXN], U[MAXN];
inline bool cross(ll ox, ll oy, ll ax, ll ay, ll bx, ll by){
	return (ax-ox)*(by-oy) >= (ay-oy)*(bx-ox);
}

int main(){
	int n = readint(), l = 0, u = 0;
	for(int i = 0; i < n; ++i){
		P[i].x = readint(), P[i].y = readint();
	}
	std::sort(P, P+n, [](point a, point b){
		return a.x != b.x ? a.x < b.x : a.y < b.y;
	});
	for(int i = 0; i < n; ++i){
		while(l >= 2 and cross(L[l-2].x, L[l-2].y, L[l-1].x, L[l-1].y, P[i].x, P[i].y)) --l;
		while(u >= 2 and cross(U[u-2].x, U[u-2].y, P[i].x, P[i].y, U[u-1].x, U[u-1].y)) --u;
		L[l++] = P[i];
		U[u++] = P[i];
	}
	printf("%d", l+u-2);
	return 0;
}