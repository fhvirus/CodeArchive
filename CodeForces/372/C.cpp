#include<iostream>
#include<algorithm>
#include<deque>
#include<utility>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define int long long
const int MAXN = 150001;
const int MAXM = 300;

int a[MAXM], b[MAXM], t[MAXM];
int dp[MAXN];
deque<pair<int, int>> dq;

signed main(){OW0
	int n, m, d;
	cin >> n >> m >> d;
	for(int i = 0; i < m; i++)
		cin >> a[i] >> b[i] >> t[i];

	for(int i = 0; i <= n; ++i)
		dp[i] = 0;

	int pt = 1;
	for(int i = 0; i < m; i++){
		dq.clear();
		int maxd = min((t[i] - pt) * d, n);
		for(int j = 1; j <= maxd; j++){
			while(!dq.empty() and dq.back().first <= dp[j])
				dq.pop_back();
			dq.push_back({dp[j], j});
		}

		for(int j = 1, l, r; j <= n; ++j){
			r = j + maxd, l = j - maxd;
			if(r <= n){
				while(!dq.empty() and dq.back().first <= dp[r])
					dq.pop_back();
				dq.push_back({dp[r], r});
			}
			while(!dq.empty() and dq.front().second < l)
				dq.pop_front();
			dp[j] = dq.front().first + (b[i] - abs(a[i] - j));
		}
		pt = t[i];
	}
	int ans = LLONG_MIN;
	for(int j = 1; j <= n; j++){
		ans = max(ans, dp[j]);
	}
	cout << ans;
	return 0;
}