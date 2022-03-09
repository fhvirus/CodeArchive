#include <bits/stdc++.h>

int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);

	int N, K;
	std::cin >> N >> K;

	std::vector<int> a(N + 1, 0);
	for (int i = 1; i <= N; ++i) {
		std::cin >> a[i];
	}
	std::sort(begin(a) + 1, end(a));

	std::vector<int64_t> pre(N + 1, 0);
	for (int i = 1; i <= N; ++i) {
		pre[i] = pre[i - 1] + a[i];
	}

	// the cost of building a post office at a[pos] for (j, i]
	auto cost = [&](const int& j, const int& i) -> int64_t {
		int pos = (j + 1 + i) / 2;
		int64_t res = (int64_t) a[pos] * ((pos - j) - (i - pos));
		res -= pre[pos] - pre[j];
		res += pre[i] - pre[pos];
		return res;
	};

	// dp[i]: (cost, # of post office)
	// dq[i]: (source, best until)
	std::vector<std::pair<int64_t, int>> dp(N + 1);
	std::deque<std::pair<int, int>> dq;

	// the cost of transition from j to i
	auto f = [&](const int& j, const int& i, const int64_t& penalty) -> std::pair<int64_t, int> {
		return std::pair<int64_t, int> (
			dp[j].first + cost(j, i) + penalty,
			dp[j].second + 1
		);
	};

	auto solve = [&](const int64_t penalty) -> void {
		// no need to clear dq here
		dq.clear();

		dp[0] = std::pair<int64_t, int>(0, 0);
		dq.emplace_back(0, N);

		for (int i = 1; i <= N; ++i) {
			while (dq.front().second < i) dq.pop_front();
			dp[i] = f(dq.front().first, i, penalty);

			while (!dq.empty()) {
				int lb = (dq.size() == 1 ? 1 : end(dq)[-2].second + 1);
				if (f(dq.back().first, lb, penalty) < f(i, lb, penalty))
					break;
				dq.pop_back();
			}

			if (dq.empty()) {
				dq.emplace_back(i, N);
				continue;
			}

			if (f(dq.back().first, dq.back().second, penalty) < f(i, dq.back().second, penalty)) {
				if (dq.back().second < N) dq.emplace_back(i, N);
				continue;
			}

			int j = dq.back().first;
			int lb = (dq.size() == 1 ? 1 : end(dq)[-2].second + 1);
			int rb = dq.back().second;

			while (lb < rb) {
				int mb = (lb + rb) / 2;
				if (f(j, mb, penalty) < f(i, mb, penalty)) lb = mb + 1;
				else rb = mb;
			}

			dq.back().second = lb - 1;
			dq.emplace_back(i, N);
		}
	};

	int64_t lb = 0, rb = 1e11;
	while (lb < rb) {
		int64_t mb = (lb + rb) / 2;
		solve(mb);
		if (dp[N].second > K) lb = mb + 1;
		else rb = mb;
	}

	solve(lb);
	std::cout << dp[N].first - lb * K << '\n';

	return 0;
}
