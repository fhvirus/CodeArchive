#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
	string s; cin >> s;
	int n = s.length(), nq = 0;
	vector<int> qs;
	for (int i = 0; i < n; ++i)
		if (s[i] == '?') {
			s[i] = ')';
			++nq;
			qs.emplace_back(i);
		}

	vector<int> L(nq), R(nq);
	for (int i = 0; i < nq; ++i) cin >> L[i] >> R[i];

	ll ans = 0;
	vector<ll> cost(n, LLONG_MAX);
	for (int i = 0; i < nq; ++i) {
		cost[qs[i]] = (ll) L[i] - R[i];
		ans += R[i];
	}

	auto cmp = [&](int u, int v) -> bool
	{ return cost[u] > cost[v]; };
	priority_queue<int, vector<int>, decltype(cmp)> pq(cmp);
	
	int cnt = 0;
	for (int i = 0; i < n; ++i) {
		if (s[i] == '(') ++cnt;
		else if (s[i] == ')') {
			--cnt;
			if (cost[i] != LLONG_MAX) pq.emplace(i);
			if (cnt < 0) {
				if (pq.empty()) {
					cout << "QAQ\n";
					return;
				}
				ans += cost[pq.top()];
				s[pq.top()] = '(';
				cnt += 2;
				pq.pop();
			}
		}
	}

	if (cnt > 0) {
		cout << "QAQ\n";
		return;
	}

	cout << ans << '\n';
	return;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	int T; cin >> T;
	while (T --> 0) solve();

	return 0;
}
