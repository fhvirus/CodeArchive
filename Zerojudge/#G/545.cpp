#include <iostream>
using namespace std;


const int MOD = 1e9 + 7;
int mad(int u, int v) {
	u += v - MOD;
	u += MOD & (u >> 31);
	return u;
}

const int kN = 2002;
int N;
string S;
int dp[kN][kN];

signed main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	cin >> N >> S;

	S = ' ' + S;
	dp[0][0] = 1;
	for (int i = 1; i <= N; ++i) {
		if (S[i] == '[' or S[i] == '?')
			for (int j = 1; j <= i; ++j)
				dp[i][j] = mad(dp[i][j], dp[i-1][j-1]);
		if (S[i] == ']' or S[i] == '?')
			for (int j = 0; j <= i; ++j)
				dp[i][j] = mad(dp[i][j], dp[i-1][j+1]);
	}
	
	cout << dp[N][0] << '\n';

	return 0;
}
