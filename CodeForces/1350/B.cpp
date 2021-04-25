#include<iostream>
#include<algorithm>
using namespace std;

#define eek ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

int a[100001], dp[100001];
void solve(){
	int n;
	cin >> n;
	for(int i = 1; i <= n; i++){
		cin >> a[i];
		dp[i] = 1;
	}
	int ans = 1;
	for(int i = 1; i <= n; i++){
		for(int j = 1; j*j <= i; j++){
			if(!(i%j) and a[j] < a[i])
				dp[i] = max(dp[i], dp[j]+1);
			if(!(i%j) and a[i/j] < a[i])
				dp[i] = max(dp[i], dp[i/j]+1);
		}
		ans = max(ans, dp[i]);
	}
	cout << ans << '\n';
}

int main(){eek
	int T;
	cin >> T;
	while(T--) solve();
	return 0;
}