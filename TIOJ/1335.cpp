// Knapsack DP is harder than FFT.
#include<bits/stdc++.h>
using namespace std;
typedef int64_t ll;
#define pb emplace_back
#define AI(x) begin(x),end(x)
const int M = 1e9 + 7;

int32_t main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int d, t; cin >> d >> t;
	vector<int> qs;
	for(int i = 0, q; i < t; ++i){
		cin >> q;
		qs.pb(q);
	}
	int n = *max_element(AI(qs));
	vector<int> dp(n + 1, 0);
	dp[0] = 1;
	if(d == 1){
		for(int j = 1; j <= n; ++j)
			for(int i = j; i <= n; ++i){
				dp[i] += dp[i - j];
				if(dp[i] >= M) dp[i] -= M;
			}
	} else {
		vector<int> sig(n + 1, 0); sig[0] = 1;
		vector<int> inv(n + 1, 0); inv[1] = 1;
		for(int i = 1, sq = 1; i <= n; ++i, sq = i * i)
			for(int j = i; j <= n; j += i)
				sig[j] += sq;
		for(int i = 2; i <= n; ++i)
			inv[i] = M - 1ll * (M / i) * inv[M % i] % M;
		for(int i = 1; i <= n; ++i){
			for(int j = 1; j <= i; ++j)
				dp[i] = (dp[i] + 1ll * dp[i - j] * sig[j] % M) % M;
			dp[i] = 1ll * dp[i] * inv[i] % M;
		}
	}
	for(int q: qs) cout << dp[q] << '\n';
	return 0;
}
