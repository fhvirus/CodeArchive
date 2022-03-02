#include <bits/stdc++.h>
using namespace std;

const int kN = 10001;
int t, Q, fft[kN];
string T, P;

int solve() {
	if (P.size() > T.size()) return 0;
	fft[0] = -1;
	fill(fft + 1, fft + P.size() + 1, 0);
	for (int i = 1, j = 1; i < P.size(); ++i, j = i) {
		while (P[i] != P[fft[j]] and j != 0) j = fft[j];
		fft[i + 1] = fft[j] + 1;
	}

	int ans = 0;
	for (int i = 0, j = 0; i + j < T.size(); ++j) {
		if (T[i + j] == P[j]) {
			if (j == P.size() - 1) {
				++ans;
				i += P.size() - fft[j + 1];
				j -= P.size() - fft[j + 1];
			}
		} else {
			i += j - fft[j];
			j -= j - fft[j] + 1;
			if (j < -1) j = -1;
		}
	}
	return ans;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	cin >> t;
	while (t --> 0) {
		cin >> T >> Q;
		for (int i = 0; i < Q; ++i) {
			cin >> P;
			cout << solve() << '\n';
		}
	}

	return 0;
}
