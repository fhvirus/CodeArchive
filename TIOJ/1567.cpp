#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while(((c=RC())<'0'||c>'9')&&c!='-'&&c!=-1);if(c=='-'){a=0;while((c=RC())>='0'&&c<='9')a*=10,a-=c^'0';}else{a=c^'0';while((c=RC())>='0'&&c<='9')a*=10,a+=c^'0';}return a;}
inline void W(int n){char OB[12],OP=0,buf[12],p;if(n<0)OB[OP++]='-',n=-n;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];write(1,OB,OP);}

#include<algorithm>
#include<cmath>
#include<utility>
using namespace std;

const int N = 1e6 + 1;
#define pdd pair<double, double>
#define ff first
#define ss second
pdd seg[N];

int main(){
	int n = R(); double d = R(), x, y, dx;
	for(int i = 0; i < n; ++i){
		x = R(), y = R();
		if(y > d or y < -d){ W(-1); return 0;}
		dx = sqrt(d*d - y*y);
		seg[i] = {x + dx, x - dx};
	}
	sort(seg, seg + n);
	int ans = 0;
	double last = -1e18;
	for(int i = 0; i < n; ++i)
		if(seg[i].ss > last)
			++ans, last = seg[i].ff;
	W(ans);
	return 0;
}