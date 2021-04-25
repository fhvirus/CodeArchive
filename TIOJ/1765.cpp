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
	int ans = 0, c = readchar(), minus = false;
	while((c<'0'||c>'9')&&c!='-'&&c!=EOF) c=readchar();
	if(c=='-') minus = true, c = readchar();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return minus ? -ans : ans;
}

#include<cmath>
typedef long long ll;
const int N = 1e5;
int n, ansi, ansj, ansk;
double radius;
struct point{
	ll x, y;
	point(){}
	point(ll x, ll y): x(x), y(y){}
} P[N], o;
inline double dist(point a, point b){
	return hypot(a.x - b.x, a.y - b.y);
}
inline point mid(point a, point b){
	return {(a.x + b.x) / 2, (a.y + b.y) / 2};
}
__int128_t a1, b1, c1, a2, b2, c2, d;
inline point O(point a, point b, point c){
	a1 = b.x-a.x, b1 = b.y-a.y, c1 = (a1*a1+b1*b1)/2;
	a2 = c.x-a.x, b2 = c.y-a.y, c2 = (a2*a2+b2*b2)/2;
	d = a1*b2 - a2*b1;
	return point(a.x + (c1*b2-c2*b1)/d, a.y + (a1*c2-a2*c1)/d);
} 

int main(){
	n = R();
	FOR(i, n) P[i] = {R(), R()};
	o = P[0], radius = 0;
	for(int i = 1; i < n; ++i){
		if(dist(o, P[i]) > radius){
			puts("j");
			o = P[i], radius = 0;
			for(int j = 0; j < i; ++j){
				if(dist(o, P[j]) > radius){
					puts("k");
					o = mid(P[i], P[j]);
					radius = dist(o, P[i]);
					for(int k = 0; k < j; ++k){
						if(dist(o, P[k]) > radius){
							o = O(P[i], P[j], P[k]);
							ansi = i, ansj = j, ansk = k;
							radius = dist(o, P[i]);
						}
					}
				}
			}
		}
	}
	printf("%d %d %d\n", ansi, ansj, ansk);
}