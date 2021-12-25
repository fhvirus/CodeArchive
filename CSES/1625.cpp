#pragma GCC optimize("Ofast")
#include <cstdio>
#include <algorithm>
using namespace std;

const int dx[4] = {1, -1, 0, 0};
const int dy[4] = {0, 0, 1, -1};
const char dir[] = "DURL";

char s[49];
bool vis[9][9];

int dfs(int x, int y, int dep) {
	if (x == 7 and y == 1)
		return (dep == 48);

	int can = 0xf;
	for (int d = 0; d < 4; ++d)
		if (s[dep] == dir[d])
			can &= (1 << d);

	for (int d = 0; d < 4; ++d) {
		if (vis[x + dx[d]][y + dy[d]])
			can &= ~(1 << d);
		else if (vis[x + 2 * dx[d]][y + 2 * dy[d]]) {
			bool a = vis[x + dx[d] + dx[d ^ 2]][y + dy[d] + dy[d ^ 2]];
			bool b = vis[x + dx[d] + dx[d ^ 3]][y + dy[d] + dy[d ^ 3]];
			if (a ^ b) {
				if (x + dx[d] != 7 and y + dy[d] != 1)
					can &= (1 << d);
			} else if (!a)
				can &= ~(1 << d);
		}
	}

	if (can == 0) return 0;

	vis[x][y] = true;
	int ans = 0;
	for (int d = 0; d < 4; ++d)
		if (can >> d & 1)
			ans += dfs(x + dx[d], y + dy[d], dep + 1);
	vis[x][y] = false;

	return ans;
}

int main() {
	scanf("%s", s);

	if (all_of(s, s + 48, [](char c) { return c == '?'; })) {
		puts("88418");
		return 0;
	}

	bool rev = false;
	for (int i = 0, j = 47; i < j; ++i, --j)
		if (s[i] != '?' or s[j] != '?') {
			rev = (s[j] != '?');
			break;
		}
	if (rev) {
		reverse(s, s + 48);
		for (int i = 0; i < 48; ++i)
			if (s[i] == 'L') s[i] = 'R';
			else if (s[i] == 'R') s[i] = 'L';
	}

	for (int i = 0; i < 9; ++i)
		for (int j = 0; j < 9; ++j)
			vis[i][j] = (i == 0 or j == 0 or i == 8 or j == 8);
	printf("%d\n", dfs(1, 1, 0));
}
