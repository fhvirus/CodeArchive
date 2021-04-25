// 這是唬爛解
#include<cstdio>
#include<algorithm>
#include<utility>
#include<cmath>
using namespace std;

#define pii pair<double, double>
#define x first
#define y second
#define N 50000
inline double dist(pii a, pii b){
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

int n;
pii p[N];

int main(){
	while(scanf("%d", &n) != -1){
		for(int i = 0; i < n; ++i)
			scanf("%lf%lf", &p[i].x, &p[i].y);
		sort(p, p + n);

		double ans = 2e18;
		for(int i = n-1; i >= 0 and ans > 1; --i){
			for(int j = i-1; j >= 0 and j >= i-4; --j)
				ans = min(ans, dist(p[i], p[j]));
		}
		printf("%.6lf\n", ans);
	}
}