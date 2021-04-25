#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma loop_opt(on)
#include<cstdio>
const int S = 1<<16;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) ? EOF : *p++;
}
inline int R(){
	int ans = 0, c = readchar();
	while(c<'0') c=readchar();
	while(c>='0') ans=(ans*10)+(c^'0'), c=readchar();
	return ans;
}

#include<algorithm>
int n, a[100000], ans;
int main(){
	n = R();
	for(int i = 1; i <= n; ++i) a[i] = R();
	std::sort(a + 1, a + n + 1, [](int a, int b){ return a > b;});
	int jizz = -1;
	for(int i = 1; i <= n; ++i){
		if((i & (i - 1)) == 0) ++jizz;
		ans += a[i] * (jizz + 1);
		// printf("%d %d\n", a[i], jizz);
	}
	if((n & (n-1)) == 0) ans += a[n-1];
	printf("%d\n", ans);
}