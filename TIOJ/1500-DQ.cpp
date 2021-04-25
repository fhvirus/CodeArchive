#pragma GCC optimize("Ofast")
#include<unistd.h>
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while(((c=RC())<'0'||c>'9')&&c!='-'&&c!=-1);if(c==-1)return 0;if(c=='-'){a=0;while((c=RC())>='0'&&c<='9')a*=10,a-=c^'0';}else{a=c^'0';while((c=RC())>='0'&&c<='9')a*=10,a+=c^'0';}return a;}

#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
#define FOR(i,n) for(int i=0;i<n;++i)
const int N = 50000;
const double INF = 8e7*8e7;
struct point{
	double x, y;
	bool operator<(const point &rhs) const{
		return x < rhs.x;
	}
} P[N], s1[N], s2[N];

inline double dist(point a, point b){
	return sqrt((a.x-b.x) * (a.x-b.x) + (a.y-b.y) * (a.y-b.y));
}


int n;
double dq(int l, int r){ // []
	if(l == r) return INF;
	if(r - l <= 300){
		double ans = 8e18;
		for(int i = l; i < r; ++i)
			for(int j = i + 1; j < i + 5 and j < n; ++j)
				ans = min(ans, dist(P[i], P[j]));
		return ans;
	}
	int m = (l+r)>>1, p1 = 0, p2 = 0, i, j, k;
	double d = min(dq(l, m), dq(m+1, r)), mn = d;

	for(i = l; i <= m; ++i) if(P[m].x - P[i].x <= d) s1[p1++] = P[i];
	for(i = m+1; i <= r; ++i) if(P[i].x - P[m].x <= d) s2[p2++] = P[i];
	for(i = 0, j = 0; i < p1; ++i){
		for(; j < p2 and s2[j].y - s1[i].y > d; ++j);
		for(k = 0; k + j < p2 and k < 3; ++k)
			mn = min(mn, dist(s2[j+k], s1[i]));
	}
	// 意義不明
	if(n < 10000) return mn;
	for(i = l, j = m+1, p1 = 0; i <= m; ++i){
		while(j <= r and P[j].y > P[i].y) s1[p1++] = P[j++];
		s1[p1++] = P[i];
	}
	while(j <= r) s1[p1++] = P[j++];
	for(i = l; i <= r; ++i) P[i] = s1[i-l];
	return mn;
}

int main(){
	while(true){
		if((n = R()) == 0) break;
		FOR(i,n) P[i] = {(double)R(), (double)R()};
		sort(P, P+n);
		printf("%.6lf\n", dq(0, n-1));
	}
	return 0;
}