#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
const int S = 1<<16;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) ? EOF : *p++;
}
inline int R(){
	int ans = 0; char c = readchar(); char minus = false;
	while(c<'-') c=readchar();
	if(c=='-') minus = true, c = readchar();
	while(c>='0') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return minus ? -ans : ans;
}

#define ll long long
const int N = 5e5;
int n, i;
ll sumx, sumy;
double ans;
int main(){
	n = R();
	for(ll x, y; i < n; ++i)
		x = R(), y = R(),
		ans += x * x + y * y,
		sumx += x, sumy += y;
	ans = ans * n * 2 - 2 * ((double)sumx * sumx + (double)sumy * sumy);
	printf("%.9lf\n", ans * 3.1415926535 / 4);
}