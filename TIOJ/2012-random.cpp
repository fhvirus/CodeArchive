#include <bits/stdc++.h>
using namespace std;

int main() {
	ios_base::sync_with_stdio(0); cout.tie(0);
	cout << setprecision(15) << fixed;
	random_device rd;
	mt19937 mt(rd());

	int T; cin >> T;
	while (T --> 0) {
		int N; cin >> N;
		vector<vector<double>> A(N, vector<double>(N + 1));
		for (vector<double> &v: A) {
			vector<int> tmp(N + 1);
			int g = 0;
			for (int &i: tmp) {
				cin >> i;
				g = __gcd(g, i);
			}
			for (int i = 0; i <= N; ++i)
				v[i] = tmp[i] / g;
		}

		vector<int> id(N);
		iota(begin(id), end(id), 0);
		shuffle(begin(id), end(id), mt);
		id.push_back(N);

		for (int i = 0; i < N; ++i) {
			for (int j = i + 1; j < N; ++j)
				if (fabs(A[j][id[i]]) > fabs(A[i][id[i]]))
					swap(A[j], A[i]);

			for (int j = i + 1; j < N; ++j) {
				double mul = A[j][id[i]] / A[i][id[i]];
				for (int k = i; k <= N; ++k)
					A[j][id[k]] -= A[i][id[k]] * mul;
			}
		}

		vector<double> ans(N);
		for (int i = N - 1; i >= 0; --i) {
			for (int j = i + 1; j < N; ++j)
				A[i][N] -= A[i][id[j]] * A[j][N];
			ans[id[i]] = (A[i][N] /= A[i][id[i]]);
		} 

		for (int i = 0; i < N; ++i)
			cout << ans[i] << '\n';
	}

	return 0;
}
