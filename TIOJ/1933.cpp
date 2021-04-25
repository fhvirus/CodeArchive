#include<iostream>
#include<vector>
#include<queue>
#include<functional>
#include<utility>
#include<algorithm>
using namespace std;
typedef long long ll;
typedef pair<int, ll> pil;
const int N = 1e5 + 225;
struct seg{
	int l, r, v;
} s[N];
inline void solve(){
	int n, l, c;
	cin >> n >> l >> c;
	for(int i = 0, t; i < n; ++i){
		cin >> s[i].l >> t;
		s[i].r = s[i].l + t;
		s[i].v = c - (s[i].r);
	}
	sort(s, s + n, [](seg a, seg b){
		return a.l < b.l;
	});

	vector<ll> dp(n, 0);
	priority_queue<pil, vector<pil>, greater<pil>> pq;
	ll curmax = 0;

	for(int i = 0; i < n; ++i){
		while(!pq.empty() and pq.top().first <= s[i].l){
			curmax = max(curmax, pq.top().second), pq.pop();
		}
		dp[i] = curmax + s[i].v;
		pq.push({s[i].r, dp[i]});
	}
	while(!pq.empty()) curmax = max(curmax, pq.top().second), pq.pop();
	cout << curmax << endl;
}
int main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int T;
	cin >> T;
	for(; T; --T) solve();
	return 0;
}