#include <iostream>
#include <string>
#include <vector>

int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);

	std::string s;
	std::cin >> s;
	int n = s.length();

	std::string t;
	std::cin >> t;
	int m = t.length();

	std::vector<int> fft(m + 1);
	fft[0] = -1;
	fft[1] = 0;
	for (int i = 1, j = 1; i < m; j = (++i)) {
		while (j != 0 and t[i] != t[fft[j]]) j = fft[j];
		fft[i + 1] = fft[j] + 1;
	}

	int ans = 0;
	for (int ptr = 0, len = 0; ptr + len < n; ++len) {
		if (s[ptr + len] == t[len]) {
			if (len + 1 == m) {
				++ans;
				ptr += m - fft[m];
				len -= m - fft[m];
			}
		} else {
			ptr += len - fft[len];
			len -= len - fft[len] + 1;
			if (len < -1) len = -1;
		}
	}

	std::cout << ans << '\n';

	return 0;
}
