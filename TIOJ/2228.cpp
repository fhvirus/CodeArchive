#include <bits/stdc++.h>
using namespace std;


struct Lisan: vector<int> {
	void done() { sort(begin(), end()); erase(unique(begin(), end()), end()); }
	int operator () (int v) { return lower_bound(begin(), end(), v) - begin(); }
};

struct Event {
	int x, l, r, v;
	Event (int _x, int _l, int _r, int _v):
		x(_x), l(_l), r(_r), v(_v) {}
	const bool operator < (const Event& oth) const {
		return x < oth.x;
	}
};

struct SegmentTree {
	int n; vector<int> val, tag;
	SegmentTree(int _n): n(_n), val(4 << __lg(n), 0), tag(4 << __lg(n), 0) {}
	void update(int i, int v) {
		val[i] += v;
		tag[i] += v;
	}
	void push(int i) {
		if (tag[i] != 0) {
			update(i * 2, tag[i]);
			update(i*2+1, tag[i]);
			tag[i] = 0;
		}
	}
	void pull(int i) {
		val[i] = max(val[i * 2], val[i*2+1]);
	}
	void modify(int i, int l, int r, int ql, int qr, int qv) {
		if (ql <= l and r <= qr) {
			update(i, qv);
			return;
		}
		push(i);
		int m = (l + r) / 2;
		if (ql < m) modify(i * 2, l, m, ql, qr, qv);
		if (m < qr) modify(i*2+1, m, r, ql, qr, qv);
		pull(i);
	}
	void modify(int ql, int qr, int qv) { modify(1, 0, n, ql, qr, qv); }
	int query() { return val[1]; }
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int n;
	cin >> n;

	Lisan lisan;
	vector<Event> events;

	for (int x, y, R, W, i = 0; i < n; ++i) {
		cin >> x >> y >> R >> W;
		tie(x, y) = make_tuple(x + y, x - y);
		int l = x - R, r = x + R + 1;
		int d = y - R, u = y + R + 1;
		events.emplace_back(l, d, u,  W);
		events.emplace_back(r, d, u, -W);
		lisan.push_back(d);
		lisan.push_back(u - 1);
	}

	lisan.done();
	sort(begin(events), end(events));
	SegmentTree sgt(lisan.size());

	int ans = 0;
	for (int i = 0, j = 0; i < n * 2; i = j) {
		while (events[j].x == events[i].x) {
			auto& [x, l, r, v] = events[j];
			l = lisan(l);
			r = lisan(r);
			sgt.modify(l, r, v);
			j += 1;
		}
		ans = max(ans, sgt.query());
	}

	cout << ans << '\n';

	return 0;
}
