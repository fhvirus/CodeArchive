#include <algorithm>
#include <iostream>
using namespace std;

typedef long long ll;
const int kN = 100'001;
const int inf = 1'000'000'007;
const ll INF = 1e18;
int N, L, H[kN], W[kN];
ll dp[kN];

int stk[kN], top;

ll val[kN * 2], tag[kN];
void upd(int i, ll v) {
	val[i] += v;
	if (i < N) tag[i] += v;
}
void push(int i) {
	for (int h = __lg(N); h >= 0; --h) {
		int u = i >> h;
		if (!tag[u >> 1]) continue;
		upd(u, tag[u >> 1]);
		upd(u ^ 1, tag[u >> 1]);
		tag[u >> 1] = 0;
	}
}
void pull(int i) {
	for (; i > 1; i >>= 1)
		val[i >> 1] = min(val[i], val[i ^ 1]) + tag[i >> 1];
}
void modify(int p, ll v) {
	push(p += N);
	val[p] = v;
	for (; p > 1; p >>= 1)
		val[p >> 1] = min(val[p], val[p ^ 1]);
}
void modify(int l, int r, ll v) {
	int tl = l, tr = r;
	push(l += N); push(r += N);
	for (++r; l < r; l >>= 1, r >>= 1) {
		if (l & 1) upd(l++, v);
		if (r & 1) upd(--r, v);
	}
	pull(tl + N); pull(tr + N);
}
ll query(int l, int r) {
	ll res = INF;
	push(l += N); push(r += N);
	for (++r; l < r; l >>= 1, r >>= 1) {
		if (l & 1) res = min(res, val[l++]);
		if (r & 1) res = min(res, val[--r]);
	}
	return res;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	cin >> N >> L;
	for (int i = 1; i <= N; ++i)
		cin >> H[i] >> W[i];

	H[0] = inf;
	stk[0] = 0;

	int lb = 0;
	ll curw = 0;
	for (int i = 1; i <= N; ++i) {
		curw += W[i];
		while (curw > L)
			curw -= W[++lb];

		while (H[stk[top]] <= H[i]) {
			int l = stk[top - 1];
			int r = stk[top] - 1;
			modify(l, r, -H[stk[top]]);
			--top;
		}

		modify(stk[top], i - 1, H[i]);
		stk[++top] = i;

		dp[i] = query(lb, i - 1);
		modify(i, dp[i]);
	}

	cout << dp[N] << '\n';

	return 0;
}
