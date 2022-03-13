#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);

	std::string s;
	std::cin >> s;
	int n = s.length();

	std::string t(n * 2 + 1, '.');
	for (int i = 0; i < n; ++i)
		t[i * 2 + 1] = s[i];
	s.swap(t);
	n = s.size();

	std::vector<int> p(n);
	for (int i = 0, l = 0, r = 0; i < n; ++i) {
		int len = r - i;
		p[i] = std::min(len, p[l + len]);
		int cur_l = i - p[i], cur_r = i + p[i];
		while (cur_l >= 1 and cur_r < n and s[cur_l - 1] == s[cur_r + 1]) {
			++p[i];
			--cur_l;
			++cur_r;
		}
		if (r < cur_r) {
			l = cur_l;
			r = cur_r;
		}
	}

	int pos = std::max_element(begin(p), end(p)) - begin(p);

	for (int i = pos - p[pos]; i <= pos + p[pos]; ++i)
		if (s[i] != '.') std::cout << s[i];
	std::cout << '\n';

	return 0;
}
