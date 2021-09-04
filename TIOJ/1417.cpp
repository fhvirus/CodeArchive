#include<unistd.h>

inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while(((c=RC())<'0'||c>'9')&&c!='-'&&c!=-1);if(c=='-'){a=0;while((c=RC())>='0'&&c<='9')a*=10,a-=c^'0';}else{a=c^'0';while((c=RC())>='0'&&c<='9')a*=10,a+=c^'0';}return a;}

#include<cstdio>
#include<algorithm>
#include "lib1417.h"

#undef long long

const int kN = 100000;
int n, s, t, a[kN];
char OB[20], OP;
char tmp[20], tp;

void solve(){
	n = R(), s = R(), t = R();
	for(int i = 0; i < n; ++i) a[i] = R();
	std::nth_element(a, a + t, a + n);
	std::nth_element(a, a + (s-1), a + n);

	long long ans = 0;
	for(int i = s-1; i < t; ++i) ans += a[i];
	OP = tp = 0;
	if(ans < 0) OB[OP++] = '-', ans = -ans;
	if(ans == 0) OB[OP++] = '0';
	while(ans > 0) tmp[tp++] = '0' + ans % 10, ans /= 10;
	while(tp > 0) OB[OP++] = tmp[--tp];
	OB[OP] = '\0';
	output(OB);
}

signed main(){
	for(int T = R(); T; --T) solve();
	return 0;
}
