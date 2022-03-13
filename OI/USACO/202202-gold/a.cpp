#include <bits/stdc++.h>

const int kN = 18;
int N, Q, tmp[kN];
bool adj[kN][kN];
uint64_t ans[1 << kN];
uint64_t dp[1 << kN][kN];

int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);

	std::cin >> N;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			std::cin >> tmp[j];
		}
		for (int j = 0; j < N; ++j) {
			adj[i][tmp[j] - 1] = true;
			if (tmp[j] - 1 == i) break;
		}
	}

	ans[0] = 1;
	for (int i = 0; i < N; ++i) {
		dp[1 << i][i] = 1;
	}

	for (int i = 0; i < N; ++i) {
		for (int mask = (1 << i); mask < (1 << (i + 1)); ++mask) {
			for (int last = 0; last <= i; ++last) {
				if (mask >> last & 1) {
					const uint64_t val = dp[mask][last];
					for (int j = 0; j < i; ++j) {
						if ((mask >> j & 1) == 0 and adj[last][j])
							dp[mask | (1 << j)][j] += val;
					}
					if (adj[last][i])
						ans[mask] += val;
				}
			}
			if (ans[mask]) {
				for (int j = i + 1; j < N; ++j)
					dp[mask | (1 << j)][j] += ans[mask];
			}
		}
	}

	std::cin >> Q;
	for (int q = 0; q < Q; ++q) {
		std::string s;
		std::cin >> s;
		std::array<int, 2> msk({0, 0});
		for (int i = 0; i < N; ++i)
			msk[ s[i] == 'G' ] |= (1 << i);
		std::cout << ans[msk[0]] * ans[msk[1]] << '\n';
	}
	return 0;
}
