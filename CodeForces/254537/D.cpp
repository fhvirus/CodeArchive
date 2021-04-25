#include<iostream>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
const int M = 998244353;

int N, G, K, w;
long long dp[1005][15];
void solve(){
	cin >> N >> G >> K;
	for(int i = 0; i <= G; i++){
		for(int j = 0; j <= K; j++)
			dp[i][j] = 0;
	}
	dp[0][0] = 1;
	for(int i = 0; i < N; i++){
		cin >> w;
		for(int j = G; j >= w; j--){
			for(int k = 1; k <= K; k++)
				dp[j][k] = (dp[j][k] + dp[j-w][k-1]) % M;
		}
	}
	cout << dp[G][K] << '\n';
}

signed main(){OW0
	int T;
	cin >> T;
	while(T--) solve();
	return 0;
}