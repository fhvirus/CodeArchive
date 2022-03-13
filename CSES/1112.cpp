#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

const int MOD = 1e9 + 7;
void mad(int& u, const int& v) {
	u += v - MOD;
	u += MOD & (u >> 31);
}
int mul(const int& u, const int& v) {
	return static_cast<int64_t>(u) * v % MOD;
}

int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);

	int n;
	std::cin >> n;

	std::string s;
	std::cin >> s;
	int m = s.length();

	std::vector<int> fft(m + 1);
	fft[0] = -1;
	fft[1] = 0;
	for (int i = 1, j = 1; i < m; j = (++i)) {
		while (j != 0 and s[i] != s[fft[j]]) j = fft[j];
		fft[i + 1] = fft[j] + 1;
	}

	std::vector go(m, std::vector<int>(26, 0));
	for (int i = 0; i < m; ++i) {
		for (char c = 'A'; c <= 'Z'; ++c) {
			int j = i;
			while (j != -1 and c != s[j]) j = fft[j];
			go[i][c - 'A'] = j + 1;
		}
	}

	std::vector<int> sc(m + 1, 0), dp(m + 1, 0);
	sc[0] = 1;

	for (int i = 0; i < n; ++i) {
		std::fill(begin(dp), end(dp), 0);
		for (int j = 0; j < m; ++j) {
			for (int c = 0; c < 26; ++c) {
				mad(dp[go[j][c]], sc[j]);
			}
		}
		mad(dp[m], mul(sc[m], 26));
		swap(dp, sc);
	}

	std::cout << sc[m] << '\n';

	return 0;
}
