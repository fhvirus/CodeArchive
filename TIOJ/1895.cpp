#include "lib1895.h"

#include <algorithm>
#include <vector>
using namespace std;

const int INF = 1e9 + 7;

[[ gnu::pure ]] int id(int l, int r) { return (l + r) | (l != r); }
struct SGT {
	int n; vector<int> mnv, mxv;
	SGT (int nn) : n(nn), mnv(nn * 2, INF), mxv(nn * 2, 0) {}
	void chmax(int u, int v) {
		mnv[u] = max(mnv[u], v);
		mxv[u] = max(mxv[u], v);
	}
	void chmin(int u, int v) {
		mnv[u] = min(mnv[u], v);
		mxv[u] = min(mxv[u], v);
	}
	void push(int i, int l, int r) {
		int m = (l + r) / 2;
		chmax(id(l, m), mxv[i]);
		chmin(id(l, m), mnv[i]);
		chmax(id(m+1, r), mxv[i]);
		chmin(id(m+1, r), mnv[i]);
		mxv[i] = 0;
		mnv[i] = INF;
	}
	void chmax(int l, int r, int ql, int qr, int v) {
		int i = id(l, r);
		if (ql <= l and r <= qr) {
			chmax(i, v);
			return;
		}
		push(i, l, r);
		int m = (l + r) / 2;
		if (ql <= m) chmax(l, m, ql, qr, v);
		if (m < qr) chmax(m+1, r, ql, qr, v);
		return;
	}
	void chmin(int l, int r, int ql, int qr, int v) {
		int i = id(l, r);
		if (ql <= l and r <= qr) {
			chmin(i, v);
			return;
		}
		push(i, l, r);
		int m = (l + r) / 2;
		if (ql <= m) chmin(l, m, ql, qr, v);
		if (m < qr) chmin(m+1, r, ql, qr, v);
		return;
	}
	void leaf(int l, int r, int ans[]) {
		int i = id(l, r);
		if (l == r) {
			ans[l] = min(mnv[i], mxv[i]);
			return;
		}
		push(i, l, r);
		int m = (l + r) / 2;
		leaf(l, m, ans);
		leaf(m+1, r, ans);
		return;
	}
};

void buildWall(int n, int k, int op[], int left[], int right[], int height[], int finalHeight[]) {
	SGT sgt(n);
	for (int i = 0; i < k; ++i) {
		if (op[i] == 1)
			sgt.chmax(0, n-1, left[i], right[i], height[i]);
		else
			sgt.chmin(0, n-1, left[i], right[i], height[i]);
	}
	sgt.leaf(0, n-1, finalHeight);
  return;
}

