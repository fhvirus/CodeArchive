#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0'&&c!=-1);if(c==-1)return 0;a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}

#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;


const int MAXN = 1e6;
struct point{
	double x, y;
	point(){}
	point(double x, double y):x(x),y(y){}
} p[MAXN];
inline double dist(point a, point b){
	return (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y);
}
inline point O(point a, point b, point c){
	double a1 = b.x-a.x, b1 = b.y-a.y, c1 = (a1*a1+b1*b1)/2;
	double a2 = c.x-a.x, b2 = c.y-a.y, c2 = (a2*a2+b2*b2)/2;
	double d = a1*b2 - a2*b1;
	return point(a.x + (c1*b2-c2*b1)/d, a.y + (a1*c2-a2*c1)/d);
} 

int n, m;
double ans;
point o;
int main(){
	while(true){
		n = R(), m = R();
		if(n == 0) break;
		for(int i = 0; i < m; ++i){
			p[i].x = R(), p[i].y = R();
		}
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
		printf("%.3lf\n", sqrt(ans));
	}
	return 0;
}