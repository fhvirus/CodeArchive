#include <algorithm>
#include <iostream>
#include <string>

int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);

	std::string s;
	std::cin >> s;
	int n = s.length();
	std::string t = s + s;

	int ans = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (ans + j == i or t[ans + j] < t[i + j]) {
				i += std::max(0, j - 1);
				break;
			}
			if (t[ans + j] > t[i + j]) {
				ans = i;
				break;
			}
		}
	}

	std::rotate(begin(s), begin(s) + ans, end(s));

	std::cout << s << '\n';

	return 0;
}
