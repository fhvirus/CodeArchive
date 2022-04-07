#include<bits/stdc++.h>
using namespace std;

const int kN = 404;
const int kC = 27;

struct Source {
	int u, v, c;
	Source (int u = -1, int v = -1, int c = -1):
		u(u), v(v), c(c) {}
};

int n, m;
vector<int> adj[kN][kC], radj[kN][kC];
Source source[kN][kN][kC];
int dis[kN][kN][kC];
char go[kN][kN];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin >> n >> m;

	queue<Source> q;
	
	for (int i = 1; i <= n; ++i) {
		source[i][i][kC - 1].c = -2;
		dis[i][i][kC - 1] = 0;
		q.emplace(i, i, kC - 1);
	}

	for (int i = 0; i < m; ++i) {
		int u, v;
		char c;
		cin >> u >> v >> c;
		adj[u][c - 'a'].push_back(v);
		radj[v][c - 'a'].push_back(u);
		go[u][v] = c;
		source[u][v][kC - 1].c = -2;
		dis[u][v][kC - 1] = 1;
		q.emplace(u, v, kC - 1);
	}

	while (!q.empty()) {
		Source sc = q.front();
		int d = dis[sc.u][sc.v][sc.c];
		q.pop();
		if (sc.c == kC - 1) {
			for (int c = 0; c < kC - 1; ++c) {
				for (const int& v: adj[sc.v][c]) {
					if (source[sc.u][v][c].c == -1) {
						source[sc.u][v][c] = sc;
						dis[sc.u][v][c] = d + 1;
						q.emplace(sc.u, v, c);
					}
				}
			}
		} else {
			for (const int& u: radj[sc.u][sc.c]) {
				if (source[u][sc.v][kC - 1].c == -1) {
					source[u][sc.v][kC - 1] = sc;
					dis[u][sc.v][kC - 1] = d + 1;
					q.emplace(u, sc.v, kC - 1);
				}
			}
		}
	}

	int d;
	cin >> d;
	vector<int> s(d);
	for (int &i: s)
		cin >> i;

	for (int i = 1; i < d; ++i) {
		int u = s[i - 1], v = s[i];
		if (source[u][v][kC - 1].c == -1) {
			cout << -1 << '\n';
			continue;
		}
		int c = kC - 1;
		int d = dis[u][v][c];

		cout << d << ' ';
		string ans;
		while (d --> 0) {
			const Source& sc = source[u][v][c];
			if (c != kC - 1)
				ans.push_back(char('a' + c));
			if (sc.c == -2) break;
			u = sc.u;
			v = sc.v;
			c = sc.c;
		}
		cout << ans;
		if (u != v) cout << go[u][v];
		reverse(begin(ans), end(ans));
		cout << ans << '\n';
	}

	return 0;
}
