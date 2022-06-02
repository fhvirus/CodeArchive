#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	string s;

	while (cin >> s and s != "END") {
		for (int i = s.size() - 1; i >= 0; --i) {
			if (s[i] == '!') {
				s.erase(i, 1);
				s[i] ^= 1;
			}
		}
		for (int i = 0; i < (int) s.size(); ++i) {
			if (s[i] == '*') {
				s[i - 1] &= s[i + 1];
				s.erase(i, 2);
				--i;
			}
		}
		for (int i = 0; i < (int) s.size(); ++i) {
			if (s[i] == '+') {
				s[i - 1] |= s[i + 1];
				s.erase(i, 2);
				--i;
			}
		}
		cout << s << '\n';
	}

	return 0;
}
