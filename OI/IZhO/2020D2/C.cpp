#include <bits/stdc++.h>

struct Lisan: std::vector<int> {
	void done() { std::sort(begin(), end()); erase(std::unique(begin(), end()), end()); }
	int operator () (const int& v) const { return std::lower_bound(begin(), end(), v) - begin(); }
	int upper_bound (const int& v) const { return std::upper_bound(begin(), end(), v) - begin(); }
};

namespace Solver {

const int kK = 502;
const int kN = 200002;

int val[kK], val_lisan[kK];
int64_t cost[kK + 1][kK + 1];
int first[kK][kK], last[kK][kK];
int map_l[kN], map_r[kN];
Lisan lisan, all;

void build(const int& bl, const int& br, const std::vector<int> a) {
	const int K = br - bl;
	lisan.clear();

	for (int i = 0; i < K; ++i) {
		val[i] = a[bl + i];
		lisan.emplace_back(val[i]);
	}
	lisan.done();
	for (int i = 0; i < K; ++i)
		val_lisan[i] = lisan(val[i]);

	int C = lisan.size();
	for (int i = 0; i < C; ++i) {
		std::fill(cost[i], cost[i] + C, 0);
		std::fill(first[i], first[i] + C, -1);
		std::fill(last[i], last[i] + C, 0);
	}

	int j = 0;
	for (int i = 0; i < C; ++i) {
		while (j < all.size() and lisan[i] >= all[j]) {
			map_l[j] = i;
			++j;
		}
	}
	while (j < all.size()) map_l[j++] = C;
	j = all.size() - 1;
	for (int i = C - 1; i >= 0; --i) {
		while (j >= 0 and lisan[i] <= all[j]) {
			map_r[j] = i;
			--j;
		}
	}
	while (j >= 0) map_r[j--] = -1;

	for (int i = 0; i < K; ++i) {
		int u = val_lisan[i];
		int ub = K - 1, db = 0;
		for (int j = i + 1; j < K; ++j) {
			int v = val_lisan[j];
			if (v > ub or db > v) continue;
			if (u == v) break;
			if (v > u) {
				int64_t c = val[j] - val[i];
				cost[db][v] += c;
				cost[db][ub + 1] -= c;
				cost[u + 1][v] -= c;
				cost[u + 1][ub + 1] += c;
				ub = v - 1;
			}
			if (v < u) {
				int64_t c = val[i] - val[j];
				cost[db][u] += c;
				cost[db][ub + 1] -= c;
				cost[v + 1][u] -= c;
				cost[v + 1][ub + 1] += c;
				db = v + 1;
			}
			if (db >= ub) break;
		}
	}

	for (int i = 0; i <= C; ++i)
		for (int j = 1; j <= C; ++j)
			cost[i][j] += cost[i][j - 1];
	for (int i = 1; i <= C; ++i)
		for (int j = 0; j <= C; ++j)
			cost[i][j] += cost[i - 1][j];

	for (int i = 0; i < K; ++i) {
		int u = val_lisan[i];
		if (first[u][u] == -1)
			first[u][u] = i;
		last[u][u] = i;
	}
	for (int i = 0; i < C; ++i) {
		for (int j = i + 1; j < C; ++j) {
			first[i][j] = std::min(first[i][j - 1], first[j][j]);
			last[i][j] = std::max(last[i][j - 1], last[j][j]);
		}
	}
	for (int i = 0; i < C; ++i) {
		for (int j = i; j < C; ++j) {
			first[i][j] = val[first[i][j]];
			last[i][j] = val[last[i][j]];
		}
	}
}

void solve(const int& Q, const std::vector<std::pair<int, int>>& queries,
		std::vector<int>& prev_val, std::vector<int64_t>& ans) {
	for (int qi = 0; qi < Q; ++qi) {
		auto [ql, qr] = queries[qi];
		if (ql > qr) continue;
		ql = map_l[ql];
		qr = map_r[qr];
		if (ql > qr) continue;
		ans[qi] += cost[ql][qr];
		if (prev_val[qi] != -1) {
			ans[qi] += abs(prev_val[qi] - first[ql][qr]);
		}
		prev_val[qi] = last[ql][qr];
	}
}

} // namespace Solver

int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);

	int N, Q;
	std::cin >> N >> Q;

	std::vector<int> a(N);
	for (int& i: a) {
		std::cin >> i;
		Solver::all.emplace_back(i);
	}
	Solver::all.done();

	std::vector<std::pair<int, int>> queries;
	queries.reserve(Q);
	for (int l, r, i = 0; i < Q; ++i) {
		std::cin >> l >> r;
		l = Solver::all(l);
		r = Solver::all.upper_bound(r) - 1;
		queries.emplace_back(l, r);
	}

	std::vector<int> prev_val(Q, -1);
	std::vector<int64_t> ans(Q, 0);

	const int K = 502;
	for (int bl = 0, br; bl < N; bl += K) {
		br = std::min(bl + K, N);
		Solver::build(bl, br, a);
		Solver::solve(Q, queries, prev_val, ans);
	}

	for (int i = 0; i < Q; ++i)
		std::cout << ans[i] << '\n';

	return 0;
}
