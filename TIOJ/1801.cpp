#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
inline char readchar(){
	const int S = 1<<12;
	static char buf[S], *p = buf, *q = buf;
	if(p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) return EOF;
	return *p++;
}
inline int R(){
	int ans = 0, c = readchar();
	while((c<'0'||c>'9')&&c!='-'&&c!=EOF) c=readchar();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return ans;
}

inline int josephus(int n, int k){
	if(k == 1) return n-1;
	int ans = 0, step;
	for(int i = 2; i <= n;){
		if(ans + k >= i){
			ans = (ans+k) % i;
			++i;
			continue;
		}
		step = (i - 1 - ans - 1)/(k - 1);
		if(i + step > n){
			ans += (n-(i-1))*k;
			break;
		}
		i += step;
		ans += step * k;
		printf("%d ", ans);
	}
	return ans;
}

int m, n, k;
int main(){
	m = R();
	for(int i = 1; i <= m; ++i){
		n = R(); k = R();
		printf("Case %d: %d\n", i, josephus(n, k)%n+1);
	}
	return 0;
}