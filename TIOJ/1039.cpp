#include<bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int n, g;

	while (cin >> n >> g and not (n == 0 and g == 0)) {
		vector<string> name(n);
		vector<int> win(n), tie(n), lose(n);
		vector<vector<int>> match(n, vector<int>(n));

		for (int i = 0; i < n; ++i)
			cin >> name[i] >> win[i] >> tie[i] >> lose[i];
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				cin >> match[i][j];

		vector<int> id(n);
		iota(begin(id), end(id), 0);
		sort(begin(id), end(id), [&](int i, int j) {
			return win[i] * (win[j] + lose[j])
				> win[j] * (win[i] + lose[i]);
		});

		int rnk = 0;
		double rate = 2.0;
		for (int i = 0; i < n; ++i) {
			double cur_rate = round(1000.0 * win[id[i]] / (win[id[i]] + lose[id[i]])) / 1000;
			if (i == 0 or cur_rate != rate) {
				rnk = i + 1;
				rate = cur_rate;
			}
			cout << rnk << ':' << setw(10) << left << name[id[i]];
			cout << setprecision(3) << fixed << cur_rate;

			// calculate magin number
			if (i > 0) {
				int magic = 0;
				while ((win[id[0]] + magic) * (g - tie[id[i]]) <= (g - tie[id[i]] - lose[id[i]]) * (g - tie[id[0]])) ++magic;
				if (magic > g - win[id[0]] - tie[id[0]] - lose[id[0]] - match[id[0]][id[i]]) cout << " --";
				else cout << " M" << magic;
			}

			cout << '\n';
		}
		cout << '\n';
	}

	return 0;
}
