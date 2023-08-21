#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int s, t, n, tot = 0, ans = 0;

	cin >> s >> t >> n;

	for (int a, i = 0; i < n; ++i) {
		cin >> a;
		tot += a;
	}

	for (int i = 1; i <= tot; ++i) {
		if (i <= (int) round(t * 0.2))
			ans += (int) round(s * 0.7);
		else if (i <= (int) round(t * 0.4))
			ans += (int) round(s * 0.8);
		else if (i <= (int) round(t * 0.6))
			ans += (int) round(s * 0.9);
		else
			ans += (int) round(s);
	}

	cout << (int) round(ans - s * t * 0.3) << '\n';

	return 0;
}
