#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int kN = 100'001;
const int kL = 20;

int N, Q, A[kN];

struct SGT {
	static const int kNode = kN * 4;
	array<int, kL> val[kNode];
	int tag[kNode];
#define lc (i << 1)
#define rc (i << 1 | 1)
#define m  (l + r >> 1)
	void upd(int i, int v, int len) {
		for (int lg = 0; lg < kL; ++lg)
			if (v >> lg & 1) val[i][lg] = len - val[i][lg];
		tag[i] ^= v;
	}
	void push(int i, int l, int r) {
		if (tag[i] == 0) return;
		upd(lc, tag[i], m - l + 1);
		upd(rc, tag[i], r - m);
		tag[i] = 0;
	}
	array<int, kL> merge(array<int, kL> a, array<int, kL> b) {
		array<int, kL> r;
		for (int lg = 0; lg < kL; ++lg)
			r[lg] = a[lg] + b[lg];
		return r;
	}
	void pull(int i) { val[i] = merge(val[lc], val[rc]); }
	void build(int i, int l, int r) {
		if (l == r) {
			for (int lg = 0; lg < kL; ++lg)
				val[i][lg] = (A[l] >> lg & 1);
			return;
		}
		build(lc, l, m);
		build(rc, m + 1, r);
		pull(i);
	}
	void modify(int i, int l, int r, int ql, int qr, int v) {
		if (ql <= l and r <= qr) {
			upd(i, v, r - l + 1);
			return;
		}
		push(i, l, r);
		if (ql <= m) modify(lc, l, m, ql, qr, v);
		if (m < qr) modify(rc, m + 1, r, ql, qr, v);
		pull(i);
	}
	array<int, kL> query(int i, int l, int r, int ql, int qr) {
		if (ql <= l and r <= qr) return val[i];
		push(i, l, r);
		if (qr <= m) return query(lc, l, m, ql, qr);
		if (m < ql) return query(rc, m + 1, r, ql, qr);
		return merge(query(lc, l, m, ql, qr), query(rc, m + 1, r, ql, qr));
	}
	void build() { build(1, 1, N); }
	void modify(int l, int r, int v) { modify(1, 1, N, l, r, v); }
	ll query(int l, int r) {
		array<int, kL> a = query(1, 1, N, l, r);
		ll ans = 0;
		for (int lg = 0; lg < kL; ++lg)
			ans += (((ll) a[lg]) << lg);
		return ans;
	}
#undef lc
#undef rc
#undef m
} sgt;

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	cin >> N;
	for (int i = 1; i <= N; ++i)
		cin >> A[i];

	sgt.build();

	cin >> Q;
	for (int t, l, r, x, i = 0; i < Q; ++i) {
		cin >> t;
		if (t == 1) {
			cin >> l >> r;
			cout << sgt.query(l, r) << '\n';
		} else {
			cin >> l >> r >> x;
			sgt.modify(l, r, x);
		}
	}
	return 0;
}
