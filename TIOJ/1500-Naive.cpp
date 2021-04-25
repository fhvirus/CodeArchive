#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
#define FOR(i,n) for(int i=0;i<n;++i)
inline char readchar(){
	const int S = 1<<20;
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

#include<algorithm>
#include<cmath>
const int N = 50000;
struct point{
	double x, y;
	bool operator<(const point &rhs) const{
		return x == rhs.x ? y < rhs.y : x < rhs.x;
	}
} P[N];

double dist(point a, point b){
	return std::hypot(a.x-b.x, a.y-b.y);
}

int n;
double d;
int main(){
	while(true){
		if((n=R()) == 0) break;
		FOR(i,n) P[i] = (point){(double)R(), (double)R()};
		std::sort(P, P+n);
		d = 1e15;
		FOR(i,n){
			for(int j = i + 1; j < n; ++j){
				if(P[j].x - P[i].x > d) break;
				d = std::min(d, dist(P[i], P[j]));
			}
		}
		printf("%.6lf\n", d);
	}
	return 0;
}