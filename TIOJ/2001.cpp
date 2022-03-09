#include<bits/stdc++.h>
using namespace std;

struct Source {
	double m, k; int r;
	Source (const double& _m, const double& _k, const int& _r):
		m(_m), k(_k), r(_r) {}
	const pair<double, int> operator () (const double& x) const
	{ return pair<double, int>(m * x + k, r + 1); }
	friend ostream& operator << (ostream& O, const Source& s)
	{ return O << '(' << s.m << ',' << s.k << ',' << s.r << ')'; }
};

bool can_kill(const Source& a, const Source& b, const Source& c) {
	double dm1 = a.m - b.m, dk1 = -(a.k - b.k);
	double dm2 = a.m - c.m, dk2 = -(a.k - c.k);
	return dk1 / dm1 >= dk2 / dm2;
}

const int kN = 200002;
int N, k, t[kN];

int64_t pre[kN];
double f[kN];

pair<double, int> dp[kN];
deque<Source> dq;

void solve(double penalty) {
	dq.clear();
	dq.emplace_back(0, penalty, 0);
	for (int i = 1; i <= N; ++i) {
		while (dq.size() > 1 and dq[0](f[i]) > dq[1](f[i]))
			dq.pop_front();
		dp[i] = dq[0](f[i]);
		Source cur(-pre[i], dp[i].first + pre[i] * f[i] + penalty, dp[i].second);
		while (dq.size() > 1 and can_kill(end(dq)[-2], end(dq)[-1], cur))
			dq.pop_back();
		dq.push_back(cur);
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	cin >> N >> k;
	for (int i = 1; i <= N; ++i)
		cin >> t[i];

	double add = 0;

	for (int i = 1; i <= N; ++i) {
		pre[i] = pre[i - 1] + t[i];
		double inv_t = 1.0 / t[i];
		f[i] = f[i - 1] + inv_t;
		add += pre[i] * inv_t;
	}

	double lb = 0, rb = 1e18, mb;
	for (int h = 0; h < 100; ++h) {
		mb = (lb + rb) / 2;
		solve(mb);
		if (dp[N].second > k) lb = mb;
		else rb = mb;
	}

	solve(lb);
	cout << setprecision(10) << fixed << dp[N].first - lb * k + add << '\n';

	return 0;
}
