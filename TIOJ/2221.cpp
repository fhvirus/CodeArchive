#include<bits/stdc++.h>
using namespace std;
typedef long long ll; typedef pair<int, int> pii;
#define ff first
#define ss second
#define pb emplace_back
#define AI(x) begin(x),end(x)
template<class I> bool chmax(I &a, I b){ return a<b ? (a=b, true) : false; }
template<class I> bool chmin(I &a, I b){ return a>b ? (a=b, true) : false; }
#ifdef OWO
#define debug(args...) LKJ("\033[1;32m[ " + string(#args) + " ]\033[0m", args)
template<class I> void LKJ(I&&x){ cerr << x << endl; }
template<class I, class...T> void LKJ(I&&x, T&&...t){ cerr << x << ", "; LKJ(t...); }
template<class I> void OI(I a, I b){ while(a < b) cerr << *a << " \n"[next(a) == b], ++a; }
#else
#define debug(...) 0
#define OI(...) 0
#endif

#pragma GCC optimize("Ofast")
typedef pair<ll, ll> pll;

const int kN = 1001;
int N, x[kN], y[kN];

inline ll dis(int i, int j){
	return (ll) (x[i] - x[j]) * (x[i] - x[j]) + (ll) (y[i] - y[j]) * (y[i] - y[j]);
}

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> N; for(int i = 1; i <= N; ++i) cin >> x[i] >> y[i];
	map<pii, vector<pii>> mp;
	for(int i = 1; i <= N; ++i)
		for(int j = i+1; j <= N; ++j)
			mp[pii(x[i]+x[j], y[i]+y[j])].pb(i, j);

	ll ans = 0;
	map<ll, int> cnt;
	for(auto &[c, v]: mp){
		cnt.clear();
		for(auto [i, j]: v)
			++cnt[dis(i, j)];
		for(auto [d, u]: cnt)
			ans += u * (u-1) / 2;
	}

	cout << ans << '\n';
	return 0;
}

