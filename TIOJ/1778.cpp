#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MOD = 1e9 + 9;
inline void mad(int& u, int v) {
	u += v - MOD;
	u += MOD & (u >> 31);
}
inline int mul(int u, int v)
{ return (uint64_t) u * v % MOD; }

const int kN = 100;
int N, M, S, T;
ll K;
int adj[kN][kN], ans[2][kN][kN];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin >> N >> M >> S >> T >> K;
	for (int u, v, i = 0; i < M; ++i) {
		cin >> u >> v;
		u -= 1; v -= 1;
		adj[u][v] += 1;
		adj[v][u] += 1;
	}

	for (int i = 0; i < N; ++i)
		ans[0][i][i] = 1;

	int lg = 63 - __builtin_clzll(K), ro = 0;
	for (int l = lg; l >= 0; --l) {
		for (int i = 0; i < N; ++i)
			for (int j = 0; j < N; ++j) {
				ans[ro ^ 1][i][j] = 0;
				for (int k = 0; k < N; ++k)
					mad(ans[ro ^ 1][i][j], mul(ans[ro][i][k], ans[ro][j][k]));
			}
		ro ^= 1;

		if (K >> l & 1) {
			for (int i = 0; i < N; ++i)
				for (int j = 0; j < N; ++j) {
					ans[ro ^ 1][i][j] = 0;
					for (int k = 0; k < N; ++k)
						mad(ans[ro ^ 1][i][j], mul(ans[ro][i][k], adj[j][k]));
				}
			ro ^= 1;
		}
	}

	cout << ans[ro][S - 1][T - 1] << '\n';
	return 0;
}
