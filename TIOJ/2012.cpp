#include <bits/stdc++.h>
using namespace std;

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cout << setprecision(15) << fixed;

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

		vector<int> id(N + 1);
		iota(begin(id), end(id), 0);

		for (int i = 0; i < N; ++i) {
			int maxi = i, maxj = id[i];
			for (int j = i; j < N; ++j)
				for (int k = j; k < N; ++k)
					if (fabs(A[j][id[k]]) > fabs(A[maxi][id[maxj]]))
						maxi = j, maxj = k;
			swap(A[i], A[maxi]);
			swap(id[i], id[maxj]);

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
