#include <bits/stdc++.h>
using namespace std;

int g[9][9];
int row[9], col[9], box[9];
int nr[9][9], nc[9][9];
int tot;

void dfs(int r, int c) {
	if (r == -1 and c == -1) {
		tot += 1;
		for (int i = 0; i < 9; ++i) {
			for (int j = 0; j < 9; ++j)
				cout << g[i][j] << " \n"[j == 8];
		}
		cout << '\n';
		return;
	}

	int can = ((1 << 10) - 2) & (~(row[r] | col[c] | box[r - r%3 + c/3]));
	for (int k = 1; k <= 9; ++k) {
		if ((can >> k & 1) == 0) continue;
		g[r][c] = k;
		row[r] |= (1 << k);
		col[c] |= (1 << k);
		box[r - r%3 + c/3] |= (1 << k);
		dfs(nr[r][c], nc[r][c]);
		g[r][c] = 0;
		row[r] ^= (1 << k);
		col[c] ^= (1 << k);
		box[r - r%3 + c/3] ^= (1 << k);
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int r = 0, c = 0;

	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			cin >> g[i][j];
			if (g[i][j] != 0) {
				row[i] |= (1 << g[i][j]);
				col[j] |= (1 << g[i][j]);
				box[i - i%3 + j/3] |= (1 << g[i][j]);
			} else {
				nr[r][c] = i;
				nc[r][c] = j;
				r = i;
				c = j;
			}
		}
	}

	nr[r][c] = -1;
	nc[r][c] = -1;

	r = -1;
	c = -1;
	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			if (g[i][j] == 0) {
				r = i;
				c = j;
				break;
			}
		}
		if (r != -1) break;
	}

	dfs(r, c);

	cout << "there are a total of " << tot << " solution(s).\n";

	return 0;
}
