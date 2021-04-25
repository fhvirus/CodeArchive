#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
inline int R(){
	int ans = 0, c = getchar_unlocked();
	while((c<'0'||c>'9')&&c!=EOF) c=getchar_unlocked();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=getchar_unlocked();
	return ans;
}

long long int dp[20];
int n;

int main(){
	dp[0] = 0;
	dp[1] = 0;
	dp[2] = 1;
	for(int i = 3; i < 20; ++i){
		dp[i] = (i-1) * (dp[i-1] + dp[i-2]);
	}
	while(true){
		if((n= R()) == 0) break;
		printf("%lld\n", dp[n]);
	}
	return 0;
}