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

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int N, M, K; cin >> N >> M >> K;
	vector<pii> a(N); for(auto &[w, v]: a) cin >> w >> v;

	vector<ll> dp(M+1, 0);
	for(auto &[w, v]: a)
		for(int i = M-w; i >= 0; --i)
			dp[i+w] = max(dp[i+w], dp[i] + v);

	for(int i = 1; i <= K; ++i){
		cout << dp[M/i] * i << '\n';
	}
	return 0;
}

