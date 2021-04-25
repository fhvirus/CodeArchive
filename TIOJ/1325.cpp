#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma loop_opt(on)
#include<cstdio>
inline int R(){
	int ans = 0, c = getchar_unlocked();
	while((c<'0'||c>'9')&&c!=EOF) c=getchar_unlocked();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=getchar_unlocked();
	return ans;
}

#include<cstring>
int t, n, dp[100001], ans;

int main(){
	for(int n = 0; n <= 10; ++n){
		ans = 0;
		memset(dp, 0, n+1<<2);
		for(int i = 1; i <= n; ++i){
			if(n / i - 1 > dp[i])
				for(int j = i * 2; j <= n; j += i)
					++dp[j];
			else ans += dp[i];
		}
		printf("%d,", ans);
	}
}