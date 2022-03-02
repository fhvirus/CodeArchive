#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
#define ff first
#define ss second

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	int n, q; cin >> n >> q;
	vector<int> qs(q);
	for (int &i: qs) cin >> i;

	vector<int> dep(n + 1), cnt(n + 2, 0);
	dep[1] = 1; cnt[1] = 1;
	for (int a, i = 2; i <= n; ++i) {
		cin >> a;
		dep[i] = dep[a] + 1;
		++cnt[dep[i]];
	}

	for (int i = n; i >= 1; --i)
		cnt[i] += cnt[i + 1];

	auto kill = [](pii a, pii b, pii c) -> bool {
		int64_t dm1 = b.ff - a.ff, dk1 = a.ss - b.ss;
		int64_t dm2 = c.ff - a.ff, dk2 = a.ss - c.ss;
		return dk1 * dm2 >= dk2 * dm1;
	};
	auto get = [](pii a, int v) -> int64_t {
		return 1ll * a.ff * v + a.ss;
	};

	vector<pii> hull;
	for (int i = 1; i <= n; ++i) {
		if (cnt[i] == 0) break;
		pii cur(i, cnt[i + 1]);
		while (hull.size() > 1 and kill(end(hull)[-2], end(hull)[-1], cur))
			hull.pop_back();
		hull.push_back(cur);
	}

	vector<int> ans(n + 1, 0);
	for (int i = 1, j = 0; i <= n; ++i) {
		while (j < hull.size() - 1 and get(hull[j], i) <= get(hull[j + 1], i))
			++j;
		ans[i] = (get(hull[j], i) + (i - 1)) / i;
	}

	for (int &i: qs)
		cout << ans[min(i, n)] << ' ';
	cout << '\n';

	return 0;
}
