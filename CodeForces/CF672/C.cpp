#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

#define int long long
const int N = 3e5 + 1;
int t, n, q, a[N], dp[2][N], jizz, eek;

signed main(){
	cin >> t;
	for(; t; --t){
		cin >> n >> q;
		for(int i = 0; i < n; ++i) cin >> a[i];
		dp[0][0] = a[0];
		jizz = a[0]; eek = 0;
		for(int i = 1; i < n; ++i){
			dp[0][i] = max(eek + a[i], max(a[i], jizz));
			dp[1][i] = max(jizz - a[i], eek);
			jizz = max(jizz, dp[0][i]);
			eek = max(eek, dp[1][i]);
		}
		cout << max(dp[0][n-1], dp[1][n-1]) << endl;
	}
	return 0;
}