#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
inline int mad(int u, int v) {
	u += v - MOD;
	u += MOD & (u >> 31);
	return u;
}
inline int mul(int u, int v) {
	return (uint64_t) u * v % MOD;
}
inline int mow(int x, int e) {
	int r = 1;
	for (; e; x = mul(x, x), e >>= 1)
		if (e & 1) r = mul(r, x);
	return r;
}

typedef array<int, 2> Vec;
typedef array< Vec, 2 > Mat;
const Mat O = {Vec{0, 0}, Vec{0, 0}};
const Mat I = {Vec{1, 0}, Vec{0, 1}};
Mat operator * (const Mat& a, const Mat& b) {
	Mat r = O;
	for (int i: {0, 1}) for (int j: {0, 1}) for (int k: {0, 1})
		r[i][j] = mad(r[i][j], mul(a[i][k], b[k][j]));
	return r;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int64_t N;
	cin >> N;

	Mat r = I;
	Mat x = {Vec{1, 1}, Vec{1, 0}};

	for (; N; x = x * x, N >>= 1)
		if (N & 1) r = r * x;

	int ans = mad(mad(r[0][0], r[0][1]), MOD - 1);
	cout << ans << '\n';

	return 0;
}
