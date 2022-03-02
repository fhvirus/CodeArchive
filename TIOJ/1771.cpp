#include <bits/stdc++.h>
using namespace std;

struct BIT {
	int n; vector<int> val;
	BIT(int _n): n(_n), val(n + 1, 0) {}
	void modify(int p, int v) {
		for (; p <= n; p += p & -p)
			val[p] += v;
	}
	int query(int p) {
		int r = 0;
		for (; p > 0; p -= p & -p)
			r += val[p];
		return r;
	}
	void clear() { fill(begin(val), end(val), 0); }
};

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	int N, M; cin >> N >> M;
	vector<int> A(N + 1, 0), B(N + 1, M + 1);
	vector<int> pos(N + 1), id(N + 1);
	for (int i = 1; i <= N; ++i) {
		cin >> A[i];
		pos[A[i]] = i;
	}
	for (int v, i = 1; i <= M; ++i) {
		cin >> v;
		B[pos[v]] = i;
	}
	
	for (int i = 1, p = M + 1; i <= N; ++i)
		id[ B[i] == M + 1 ? p++ : B[i] ] = i;

	BIT bit(N);
	vector<int64_t> ans(M + 2, 0ll);
	for (int i = 1; i <= N; ++i) {
		ans[0] += (i - 1) - bit.query(A[i]);
		bit.modify(A[i], 1);
	}
	bit.clear();

	auto solve = [&](auto &solve, int lb, int rb) {
		if (lb + 1 == rb) return;
		int mb = (lb + rb) / 2, lp, rp;
		solve(solve, lb, mb);
		solve(solve, mb, rb);
		// i < j, A[i] > A[j]
		for (lp = lb, rp = mb; lp < mb; ++lp) {
			while (rp < rb and id[rp] < id[lp])
				bit.modify(A[id[rp++]], 1);
			ans[B[id[lp]]] -= (rp - mb) - bit.query(A[id[lp]]);
		}
		for (--rp; rp >= mb; --rp)
			bit.modify(A[id[rp]], -1);
		// i > j, A[i] < A[j]
		for (lp = mb - 1, rp = rb - 1; lp >= lb; --lp) {
			while (rp >= mb and id[rp] > id[lp])
				bit.modify(A[id[rp--]], 1);
			ans[B[id[lp]]] -= bit.query(A[id[lp]] - 1);
		}
		for (++rp; rp < rb; ++rp)
			bit.modify(A[id[rp]], -1);
		inplace_merge(begin(id) + lb, begin(id) + mb, begin(id) + rb);
	};
	solve(solve, 1, N + 1);

	for (int i = 0; i < M; ++i) {
		cout << ans[i] << '\n';
		ans[i + 1] += ans[i];
	}

	return 0;
}
