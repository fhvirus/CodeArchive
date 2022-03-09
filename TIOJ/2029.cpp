#include <bits/stdc++.h>
using namespace std;
typedef pair<int64_t, int64_t> pll;

const int64_t INF = 1e18;
const int kN = 100001;
int N, K, d[kN];
int64_t R, C;

int64_t pre[kN], prek[kN];

int64_t dp_pool[2][kN];
deque<pair<int, pll>> dq;

int64_t get_val(const pll& func, const int64_t& val)
{ return func.first * val + func.second; }
bool can_kill(const pll& a, const pll& b, const pll& c, const int& rb) {
	int64_t dm1 = a.first - b.first, dk1 = -(a.second - b.second);
	int64_t dm2 = a.first - c.first, dk2 = -(a.second - c.second);
	// dk1 / dm1 >= dk2 / dm2
	return dk1 * dm2 >= dk2 * dm1 and
		(rb >= N or (c.first - b.first) * pre[rb + 1] + (c.second - b.second) >= 0);
}

int64_t solve(const int& lim) {
	auto sc = dp_pool[0], dp = dp_pool[1];
	sc[0] = 0;
	for (int i = 1; i <= N; ++i)
		sc[i] = -INF;

	for (int k = 1; k <= K; ++k) {
		dp[0] = -INF;
		dq.clear();
		dq.emplace_back(0, pll(C, sc[0]));
		for (int i = 1; i <= N; ++i) {
			if (dq.front().first < i - lim)
				dq.pop_front();
			while (dq.size() > 1 and get_val(dq[0].second, pre[i]) < get_val(dq[1].second, pre[i]))
				dq.pop_front();
			dp[i] = get_val(dq.front().second, pre[i]) - prek[i];
			pll cur(C + i, -(C + i) * pre[i] + prek[i] + sc[i]);
			while (dq.size() > 1 and can_kill(end(dq)[-2].second, end(dq)[-1].second, cur, end(dq)[-2].first + lim))
				dq.pop_back();
			dq.emplace_back(i, cur);
		}
		swap(dp, sc);
	}

	return sc[N];
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	cin >> N >> K >> R >> C;
	for (int i = 1; i <= N; ++i) {
		cin >> d[i];
		pre[i] = pre[i - 1] + d[i];
		prek[i] = prek[i - 1] + (int64_t) i * d[i];
	}

	int ans = 0;
	for (int l = (1 << 16); l > 0; l >>= 1)
		if (ans + l <= N and solve(ans + l) < R)
			ans += l;

	cout << (ans == N ? -1 : ans + 1) << '\n';

	return 0;
}
