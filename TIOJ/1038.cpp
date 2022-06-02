#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
#define pb emplace_back

const int kN = 255;
const int kC = 128;
int r, c, n;
vector<string> pieces;
vector<bool> used;
vector<pii> bkt[kC][kC];
char ans[kN][kN], edge[kN][kN][2];

bool solve(int i, int j) {
	if (i == r) return true;
	const char lb = edge[i][j][0];
	const char ub = edge[i][j][1];

	for (const auto& [id, ori]: bkt[lb][ub]) {
		if (used[id]) continue;
		if (j + 1 == c xor pieces[id][(ori + 2) & 3] == '-') continue;
		if (i + 1 == r xor pieces[id][(ori + 3) & 3] == '-') continue;
		edge[i][j + 1][0] = pieces[id][(ori + 2) & 3] ^ 32;
		edge[i + 1][j][1] = pieces[id][(ori + 3) & 3] ^ 32;
		used[id] = true;
		bool b = (j + 1 == c ? solve(i + 1, 0) : solve(i, j + 1));
		if (b) {
			ans[i][j] = pieces[id][4 + ori];
			return true;
		}
		used[id] = false;
	}
	return false;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	while (cin >> r >> c and not (r == 0 and c == 0)) {
		n = r * c;
		pieces.resize(n);

		// input
		cin.ignore();
		for (int i = 0; i < n; ++i)
			getline(cin, pieces[i]);

		// init
		used.assign(n, false);
		for (int i = 0; i < kC; ++i)
			for (int j = 0; j < kC; ++j)
				bkt[i][j].clear();

		for (int i = 1; i < n; ++i) {
			for (int j = 0; j < 4; ++j) {
				int lb = pieces[i][j];
				int ub = pieces[i][(j + 1) & 3];
				bkt[lb][ub].pb(i, j);
			}
		}

		for (int i = 0; i < r; ++i) {
			for (int j = 0; j < c; ++j) {
				edge[i][j][0] = (j == 0 ? '-' : 0);
				edge[i][j][1] = (i == 0 ? '-' : 0);
			}
		}

		ans[0][0] = pieces[0][4];
		edge[0][1][0] = pieces[0][2] ^ 32;
		edge[1][0][1] = pieces[0][3] ^ 32;

		// solve
		assert(solve(0, 1));

		// output
		for (int i = 0; i < r; ++i) {
			for (int j = 0; j < c; ++j)
				cout << ans[i][j];
			cout << '\n';
		}
		cout << '\n';
	}

	return 0;
}
