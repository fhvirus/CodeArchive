#include <iostream>
#include <string>
#include <vector>

int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);

	std::string s;
	std::cin >> s;
	int n = s.length();

	std::vector<int> fft(n + 1);
	fft[0] = -1;
	fft[1] = 0;
	for (int i = 1, j = 1; i < n; j = (++i)) {
		while (j != 0 and s[i] != s[fft[j]]) j = fft[j];
		fft[i + 1] = fft[j] + 1;
	}

	std::vector<int> ans;
	for (int i = n; fft[i] != 0; i = fft[i])
		ans.push_back(fft[i]);

	for (int i = ans.size() - 1; i >= 0; --i)
		std::cout << ans[i] << " \n"[i == 0];

	return 0;
}
