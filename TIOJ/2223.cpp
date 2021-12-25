#include <iostream>
#include <algorithm>
using namespace std;

const int kN = 1001;
int n, M;
struct Stone {
	int w, p;
	bool operator < (const Stone &oth) const {
		return p > oth.p;
	}
} stone[kN];

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	for (int i = 0; i < n; ++i)
		cin >> stone[i].w >> stone[i].p;
	sort(stone, stone + n);
	int ans = 0;
	for (int i = 0; i < n and M > 0; ++i) {
		int t = M;
		if (stone[i].w < t)
			t = stone[i].w;
		M -= t;
		ans += t * stone[i].p;
	}
	cout << ans << '\n';
	return 0;
}
