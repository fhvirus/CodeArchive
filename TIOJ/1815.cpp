#include <bits/stdc++.h>
using namespace std;

const int kT = 1000000;
const int kA = 50000;

int A, B, T, X[kA], Y[kA];
pair<int, int> toy[kT];

bool solve(int lim) {
	priority_queue<int> pq;
	int ptr = 0;
	for (int i = 0; i < A; ++i) {
		while (ptr < T and toy[ptr].first < X[i])
			pq.emplace(toy[ptr++].second);
		for (int k = 0; !pq.empty() and k < lim; ++k)
			pq.pop();
	}
	while (ptr < T) pq.emplace(toy[ptr++].second);
	for (int i = B - 1; i >= 0 and !pq.empty(); --i) {
		if (pq.top() >= Y[i]) return false;
		for (int k = 0; !pq.empty() and k < lim; ++k)
			pq.pop();
	}
	return pq.empty();
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	cin >> A >> B >> T;
	for (int i = 0; i < A; ++i) cin >> X[i];
	for (int i = 0; i < B; ++i) cin >> Y[i];
	for (int i = 0; i < T; ++i)
		cin >> toy[i].first >> toy[i].second;

	sort(X, X + A);
	sort(Y, Y + B);
	sort(toy, toy + T);

	for (int i = 0; i < T; ++i)
		if (toy[i].first >= X[A - 1] and toy[i].second >= Y[B - 1]) {
			cout << -1 << '\n';
			return 0;
		}

	int ans = 0;
	for (int l = (1 << 20); l > 0; l >>= 1)
		if (!solve(ans + l)) ans += l;

	cout << ans + 1 << '\n';

	return 0;
}
