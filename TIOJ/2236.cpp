#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
const int OWT = (MOD + 1) / 2;
int mad(int u, int v) {
	u += v - MOD;
	u += MOD & (u >> 31);
	return u;
}
int mul(int u, int v) {
	return (int64_t) u * v % MOD;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int N, M;
	cin >> N >> M;

	vector<vector<int>> A(N, vector<int>(M));
	for (auto& v: A) for (int& i: v) cin >> i;

	vector<vector<int>> LR(N, vector<int>(M));
	vector<vector<int>> U(N, vector<int>(M));
	vector<vector<int>> D(N, vector<int>(M));

	vector<pair<int, int>> stk;
	stk.reserve(max(N, M));

	for (int i = 0; i < N; ++i) {
		stk.clear();
		for (int j = 0; j < M; ++j) {
			while (!stk.empty() and A[i][j] >= stk.back().second)
				stk.pop_back();
			LR[i][j] = (stk.empty() ? j : j - stk.back().first - 1);
			stk.emplace_back(j, A[i][j]);
		}
		stk.clear();
		for (int j = M - 1; j >= 0; --j) {
			while (!stk.empty() and A[i][j] >= stk.back().second)
				stk.pop_back();
			LR[i][j] = min(LR[i][j], stk.empty() ? M - 1 - j : stk.back().first - 1 - j);
			stk.emplace_back(j, A[i][j]);
		}
	}

	for (int j = 0; j < M; ++j) {
		stk.clear();
		for (int i = 0; i < N; ++i) {
			while (!stk.empty() and A[i][j] >= stk.back().second)
				stk.pop_back();
			U[i][j] = (stk.empty() ? i : i - stk.back().first - 1);
			stk.emplace_back(i, A[i][j]);
		}
		stk.clear();
		for (int i = N - 1; i >= 0; --i) {
			while (!stk.empty() and A[i][j] >= stk.back().second)
				stk.pop_back();
			D[i][j] = (stk.empty() ? N - 1 - i : stk.back().first - 1 - i);
			stk.emplace_back(i, A[i][j]);
		}
	}

	int ans = 0;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			int lr = LR[i][j];
			int u = U[i][j], d = D[i][j];
			u = min(u, d);
			int ud = mad(mul(u, d + 1), MOD - mul(mul(u, u + 1), OWT));
			ans = mad(ans, mul(lr, ud));
		}
	}

	cout << ans << '\n';

	return 0;
}
