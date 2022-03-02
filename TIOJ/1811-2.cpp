#include <bits/stdc++.h>
using namespace std;

const int kN = 100'001;
int N, L, H[kN], W[kN];
int64_t dp[kN];
deque<int> dq;
multiset<int64_t> ms;

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	cin >> N >> L;
	for (int i = 1; i <= N; ++i)
		cin >> H[i] >> W[i];

	int64_t curw = 0;
	dq.push_back(0);

	for (int i = 1; i <= N; ++i) {
		while (dq.size() > 1 and H[dq.back()] <= H[i]) {
			int t = dq.back(); dq.pop_back();
			ms.erase(dp[dq.back()] + H[t]);
		}
		ms.insert(dp[dq.back()] + H[i]);
		dq.push_back(i);

		curw += W[i];
		while (curw > L) {
			ms.erase(dp[dq[0]] + H[dq[1]]);
			curw -= W[++dq[0]];
			if (dq[0] == dq[1]) dq.pop_front();
			else if (curw <= L) ms.insert(dp[dq[0]] + H[dq[1]]);
		}

		dp[i] = *begin(ms);
	}

	cout << dp[N] << '\n';
	
	return 0;
}
