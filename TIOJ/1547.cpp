#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma loop_opt(on)
#include<cstdio>
inline char readchar(){
	static char buf[10], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+fread(buf,1,10,stdin))==buf) ? EOF : *p++;
}
inline int R(){
	int ans = 0, c = readchar();
	while(c<'0') c=readchar();
	while(c>='0') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return ans;
}

int n, a[31], jizz = 1, outp;
int tail[31] = {0,2,5,9,15,24,38,60,95,151,241,386,620,998,1609,2597,4195,6780,10962,17728,28675,46387,75045,121414,196440,317834,514253,832065,1346295,2178336,3524606};

int main(){
	n = R();
	fwrite(outbuf, 1, tail[n], stdout);
}