#include<bits/stdc++.h>
using namespace std;

#define pb emplace_back
#define AI(x) begin(x),end(x)
struct Lisan: vector<int> {
	void done() { sort(AI()); erase(unique(AI()), end()); }
	int operator () (int v) { return lower_bound(AI(), v) - begin(); }
};

const int kN = 404;
int n, l[kN], r[kN], t[kN], b[kN];
int row, col, add[kN][kN];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	while (cin >> n and n != 0) {
		Lisan lr, tb;
		for (int i = 0; i < n; ++i) {
			cin >> l[i] >> t[i] >> r[i] >> b[i];
			lr.pb(l[i]); lr.pb(r[i]);
			tb.pb(t[i]); tb.pb(b[i]);
		}

		lr.pb(0); lr.pb(10000);
		tb.pb(0); tb.pb(10000);
		lr.done(); row = lr.size() - 1;
		tb.done(); col = tb.size() - 1;

		for (int i = 0; i <= row; ++i)
			for (int j = 0; j <= col; ++j)
				add[i][j] = 0;

		for (int i = 0; i < n; ++i) {
			l[i] = lr(l[i]); r[i] = lr(r[i]);
			t[i] = tb(t[i]); b[i] = tb(b[i]);
			++add[l[i]][t[i]];
			--add[r[i]][t[i]];
			--add[l[i]][b[i]];
			++add[r[i]][b[i]];
		}

		for (int i = 0; i < row; ++i)
			for (int j = 1; j < col; ++j)
				add[i][j] += add[i][j - 1];
		for (int i = 1; i < row; ++i)
			for (int j = 0; j < col; ++j)
				add[i][j] += add[i - 1][j];

		long long ans = 0;
		for (int i = 0; i < row; ++i)
			for (int j = 0; j < col; ++j)
				ans += (1ll << add[i][j]) * (lr[i + 1] - lr[i]) * (tb[j + 1] - tb[j]);

		cout << ans << '\n';
	}

	return 0;
}
