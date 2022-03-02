#include<bits/stdc++.h>
using namespace std;

const int kN = 100001;
int n, a[2][kN];
int64_t ans;

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	cin >> n;
	for (const int& i: {0, 1})
		for (int j = 0; j < n; ++j)
			cin >> a[i][j];

	for (int j = 0; j < n; ++j) {
		for (const int& i: {0, 1})
			while (a[i][j] > 1 and a[i ^ 1][j] < 1) {
				--a[i][j];
				++a[i ^ 1][j];
				++ans;
			}
		for (const int& i: {0, 1})
			if (a[i][j] != 1) {
				int d = a[i][j] - 1;
				a[i][j] -= d;
				a[i][j + 1] += d;
				ans += abs(d);
			}
	}

	cout << ans << '\n';

	return 0;
}
