#include<bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	vector<int64_t> f(87, 0);
	f[0] = f[1] = 1;
	for (int i = 2; i <= 86; ++i)
		f[i] = f[i - 2] + f[i - 1];

	vector<tuple<int, int, int, int>> border;
	for (int i = 1; i <= 44; ++i) {
		for (int j = i + 2; j <= 44; ++j) {
			border.emplace_back(j, i, j, i + 1);
		}
	}
	for (int i = 1; i <= 44; ++i) {
		for (int j = i + 3; j <= 44; ++j) {
			border.emplace_back(i, j, i + 1, j);
		}
	}
	border.emplace_back(44, 44, 44, 45);

	int64_t T;
	cin >> T;

	vector<bool> need(87, false);
	for (int i = 86; i >= 0; --i) {
		if (T >= f[i]) {
			need[i] = true;
			T -= f[i];
		}
	}

	bool has = false;
	for (int i = 86; i >= 0; --i) {
		has |= need[i];
		if (need[i]) continue;
		if (!has) {
			int r = i / 2 + 1;
			int c = i / 2 + 1 + (i & 1);
			if (r > 1) border.emplace_back(r - 1, c, r, c);
			if (c > 1) border.emplace_back(r, c - 1, r, c);

			if (i >= 2 and !need[i - 2]) {
				if (i & 1) border.emplace_back(r - 1, c - 1, r - 1, c);
				else border.emplace_back(r - 1, c - 1, r, c - 1);
			}
		} else {
			if (i & 1) {
				int r = i / 2 + 1;
				int c = min(r + 2, 44);
				border.emplace_back(r, c, r, c + 1);
			} else {
				int c = i / 2 + 1;
				int r = min(c + 1, 43);
				if (i == 84 and need[86]) border.emplace_back(r + 1, c, r + 2, c);
				else border.emplace_back(r, c, r + 1, c);
			}
		}
	}

	sort(begin(border), end(border));
	border.erase(unique(begin(border), end(border)), end(border));

	int N = 45, M = 45, K = border.size();
	cout << N << ' ' << M << '\n';
	cout << K << '\n';
	for (const auto& [a, b, c, d]: border)
		cout << a << ' ' << b << ' ' << c << ' ' << d << '\n';

	return 0;
}
