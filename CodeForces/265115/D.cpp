#include<iostream>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

long long int dp[5001][5001];
int a[5000];
const int M = 1e9 + 7;

int main(){OW0
	int n, k;
	cin >> n >> k;
	for(int i = 0; i < n; i++){
		cin >> a[i];
	}
	for(int i = 0; i <= k; i++){
		dp[0][i] = 0;
	}
	for(int i = 0; i <= n; i++){
		dp[i][0] = 1;
	}
	for(int j = 1; j <= k; j++){
		for(int i = 1; i <= n; i++){
			dp[i][j] = (dp[i-1][j] + (dp[i-1][j-1] * a[i-1])%M)%M;
		}
	}

	cout << dp[n][k];

	return 0;
}