#include <iostream>
using namespace std;

const int kN = 1001;
const int kM = kN * 2;

int n, T, num[kM][kM];

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	cin >> n >> T;

	int x = n, y = n, tot = 0;
	for (int d = 2; d < 2 * n - 1; d += 2) {
		num[--x][y] = ++tot;
		for (int i = 1; i < d; ++i) num[x][++y] = ++tot;
		for (int i = 0; i < d; ++i) num[++x][y] = ++tot;
		for (int i = 0; i < d; ++i) num[x][--y] = ++tot;
		for (int i = 0; i < d; ++i) num[--x][y] = ++tot;
	}

	while (T --> 0) {
		int k; cin >> k;
		int ans = 0;
		for (int x, y; k; --k) {
			cin >> x >> y;
			ans ^= num[x][y];
		}
		cout << (ans ? "A Win!\n" : "B Win.\n");
	}

	return 0;
}
