#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
typedef long long ll;
inline char readchar(){
	const int S = 1<<20;
	static char buf[S], *p=buf, *q=buf;
	if(p==q and (q=(p=buf)+fread(buf,1,S,stdin))==buf) return EOF;
	return *p++;
}
inline int readint(){
	int ans=0, c = readchar();
	while((c<'0'||c>'9')&&c!=EOF) c=readchar();
	while(c<='9'&&c>='0') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return ans;
}

const int MAXN = 1e6;
struct point{
	ll x, y;
	point(){}
	point(ll x, ll y):x(x),y(y){}
} p[MAXN];
inline long long dist(point a, point b){
	return (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y);
}

__int128_t a1, b1, c1, a2, b2, c2, d;
inline point O(point a, point b, point c){
	a1 = b.x-a.x, b1 = b.y-a.y, c1 = (a1*a1+b1*b1)/2;
	a2 = c.x-a.x, b2 = c.y-a.y, c2 = (a2*a2+b2*b2)/2;
	d = a1*b2 - a2*b1;
	return point(a.x + (c1*b2-c2*b1)/d, a.y + (a1*c2-a2*c1)/d);
} 

int n, m;
ll ans;
point o;
int main(){
	while(true){
		n = readint(), m = readint();
		if(n == 0) break;
		for(int i = 0; i < m; ++i){
			p[i].x = readint()*10, p[i].y = readint()*10;
		}
		// std::random_shuffle(p, p+m);
		o = p[0], ans = 0;
		for(int i = 1; i < m; ++i){
			if(dist(o, p[i]) > ans){
				o = p[i], ans = 0;
				for(int j = 0; j < i; ++j){
					if(dist(o, p[j]) > ans){
						o = {(p[i].x + p[j].x)/2, (p[i].y + p[j].y)/2};
						ans = dist(o, p[i]);
						for(int k = 0; k < j; ++k){
							if(dist(o, p[k]) > ans){
								o = O(p[i], p[j], p[k]);
								ans = dist(o, p[i]);
							}
						}
					}
				}
			}
		}
		printf("%lld\n", (long long)ceil(sqrt(ans) / 10));
	}
	return 0;
}