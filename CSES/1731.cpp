#include <bits/stdc++.h>
using namespace std;

const int kN = 5005;
const int kS = 1000001;
const int MOD = 1e9 + 7;
void mad(int &u, const int& v) {
	u += v - MOD;
	u += MOD & (u >> 31);
}

int nd[kS][27], tot;
void insert(const string& s) {
	int u = 0;
	for (const char& c: s) {
		if (nd[u][c - 'a'] == 0)
			nd[u][c - 'a'] = ++tot;
		u = nd[u][c - 'a'];
	}
	nd[u][26] = 1;
}

int dp[kN];

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	string s;
	cin >> s;
	int n = s.length();
	dp[n] = 1;

	int k; cin >> k;
	for (int i = 0; i < k; ++i) {
		string t;
		cin >> t;
		insert(t);
	}

	for (int i = n - 1; i >= 0; --i) {
		for (int j = i, u = 0; j < n; ++j) {
			u = nd[u][ s[j] - 'a' ];
			if (u == 0) break;
			if (nd[u][26]) mad(dp[i], dp[j + 1]);
		}
	}

	cout << dp[0] << '\n';

	return 0;
}
