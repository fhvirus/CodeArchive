#pragma GCC optmize("Ofast")
#pragma GCC target("avx,avx2")
#include<bits/stdc++.h>
using namespace std;

const int kN = 2800;
const int kW = 5;
int n, P;
int A[kN][kN], B[kN][kN];
vector<pair<int, int>> anss;

int64_t wei[kW][kN];
int64_t WB[kW][kN];
void build(int l, int r) {
	for (int w = 0; w < kW; ++w)
		for (int i = 0; i < n; ++i)
			WB[w][i] = 0;
	for (int w = 0; w < kW; ++w) {
		for (int j = l; j < r; ++j) {
			for (int i = 0; i < n; ++i)
				WB[w][i] += B[j][i] * wei[w][j];
		}
	}
	for (int w = 0; w < kW; ++w)
		for (int i = 0; i < n; ++i)
			WB[w][i] %= P;
}

bool test(int i) {
	for (int w = 0; w < kW; ++w) {
		int64_t v = 0;
		for (int j = 0; j < n; ++j)
			v += A[i][j] * WB[w][j];
		if (v % P != 0) return true;
	}
	return false;
}

void solve(const vector<int>& ids, int l, int r) {
	build(l, r);
	vector<int> can;
	for (const int& i: ids)
		if (test(i)) can.push_back(i);

	if (can.empty()) return;
	if (l + 1 == r) {
		for (const int& i: can)
			anss.emplace_back(i, l);
	} else {
		int m = (l + r) / 2;
		if (l < m) solve(can, l, m);
		if (m < r) solve(can, m, r);
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int subtask;
	cin >> subtask;

	cin >> n >> P;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			cin >> A[i][j];
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			cin >> B[j][i];

	random_device rd;
	mt19937 mt(rd());
	uniform_int_distribution<int> rnd(1, P - 1);
	for (int w = 0; w < kW; ++w)
		for (int i = 0; i < n; ++i)
			wei[w][i] = rnd(mt);


	vector<int> ids(n);
	iota(begin(ids), end(ids), 0);

	anss.reserve(n * 2);
	solve(ids, 0, n);

	sort(begin(anss), end(anss));
	for (const auto& [i, j]: anss) {
		int64_t v = 0;
		for (int k = 0; k < n; ++k)
			v += (int64_t) A[i][k] * B[j][k];
		cout << i + 1 << ' ' << j + 1 << ' ' << v % P << '\n';
	}
	return 0;
}
