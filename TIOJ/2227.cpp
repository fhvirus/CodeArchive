#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,popcnt")
#include <bits/stdc++.h>
using namespace std;

const int kN = 2500;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int n;
	cin >> n;

	vector<bitset<kN>> bs(n);
	for (int i = 0; i < n; ++i) {
		int d;
		cin >> d;
		for (int j = 0; j < d; ++j) {
			int f;
			cin >> f;
			bs[i][f] = 1;
		}
	}

	int ans = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = i + 1; j < n; ++j) {
			ans += (bs[i] & bs[j]).any();
		}
	}

	cout << ans << '\n';

	return 0;
}
