#include <algorithm>
#include <deque>
#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;
const ll INF = 1e18;
const int kC = 1000000;

struct Line {
	ll m, k;
	Line(ll _m, ll _k): m(_m), k(_k) {}
	ll operator() (ll x) { return (m == INF ? INF : m * x + k); }
};

struct LiChao {
	struct Node {
		Line val;
		Node *lc, *rc;
		Node (ll m = INF, ll k = INF):
			val(m, k), lc(nullptr), rc(nullptr) {}
	};
	Node *root;
	LiChao(): root(nullptr) {}
	void insert(Node* &u, int lb, int rb, Line line) {
		if (u == nullptr) {
			u = new Node(line.m, line.k);
			return;
		}
		int mid = (lb + rb) / 2;
		if (u->val(mid) > line(mid)) swap(u->val, line);
		if (lb == rb) return;
		if (u->val.m < line.m) insert(u->lc, lb, mid, line);
		else insert(u->rc, mid+1, rb, line);
		return;
	}
	ll query(Node* u, int lb, int rb, int pos) {
		if (u == nullptr) return INF;
		int mid = (lb + rb) / 2;
		ll ans = u->val(pos);
		if (lb == rb) return ans;
		return min(ans, (pos <= mid ?
					query(u->lc, lb, mid, pos) :
					query(u->rc, mid+1, rb, pos)));
	}
	void insert(Line line) { insert(root, 1, kC, line); }
	ll query(int pos) { return query(root, 1, kC, pos); }
};

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	int n, x; cin >> n >> x;
	vector<int> s(n+1, 0);
	vector<int> f(n+1, 0);
	for (int i = 1; i <= n; ++i) cin >> s[i];
	for (int i = 1; i <= n; ++i) cin >> f[i];
	f[0] = x;

	vector<ll> dp(n+1, INF);
	dp[0] = 0;

	LiChao lichao;
	lichao.insert(Line(f[0], dp[0]));
	for (int i = 1; i <= n; ++i) {
		dp[i] = lichao.query(s[i]);
		lichao.insert(Line(f[i], dp[i]));
	}

	cout << dp[n] << '\n';

	return 0;
}
