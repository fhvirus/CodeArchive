// Knapsack DP is harder than FFT.
#include<bits/stdc++.h>
using namespace std;
typedef long long ll; typedef pair<int,int> pii; typedef pair<ll,ll> pll;
#define ff first
#define ss second
#define pb emplace_back
#define AI(x) begin(x),end(x)
template<class I>bool chmax(I&a,I b){return a<b?(a=b,true):false;}
template<class I>bool chmin(I&a,I b){return b<a?(a=b,true):false;} 
#ifdef OWO
#define debug(args...) SDF(#args, args)
#define OIU(args...) ostream& operator<<(ostream&O,args)
#define LKJ(S,B,E,F) template<class...T>OIU(S<T...>s){O<<B;int c=0;for(auto i:s)O<<(c++?", ":"")<<F;return O<<E;}
LKJ(vector,'[',']',i)LKJ(deque,'[',']',i)LKJ(set,'{','}',i)LKJ(multiset,'{','}',i)LKJ(unordered_set,'{','}',i)LKJ(map,'{','}',i.ff<<':'<<i.ss)LKJ(unordered_map,'{','}',i.ff<<':'<<i.ss)
template<class...T>void SDF(const char* s,T...a){int c=sizeof...(T);if(!c){cerr<<"\033[1;32mvoid\033[0m\n";return;}(cerr<<"\033[1;32m("<<s<<") = (",...,(cerr<<a<<(--c?", ":")\033[0m\n")));}
template<class T,size_t N>OIU(array<T,N>a){return O<<vector<T>(AI(a));}template<class...T>OIU(pair<T...>p){return O<<'('<<p.ff<<','<<p.ss<<')';}template<class...T>OIU(tuple<T...>t){return O<<'(',apply([&O](T...s){int c=0;(...,(O<<(c++?", ":"")<<s));},t),O<<')';}
#else
#pragma GCC optimize("Ofast")
#define debug(...) ((void)0)
#endif

typedef tuple<int, int, int> tii;

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int N, M, T, D; ll K;
	cin >> N >> M >> K >> T >> D;

	auto mad = [&D](int &u, int v){
		u += v - D;
		u += D & (u >> 31);
	};
	auto mul = [&D](int u, int v){
		ll r = (ll) u * v;
		if(r >= D) r %= D;
		return r;
	};
	auto sig = [&D, &mul](ll u, ll v){
		ll a = u + v, b = v - u + 1;
		((a & 1) ? b : a) >>= 1;
		if(a >= D) a %= D;
		if(b >= D) b %= D;
		return mul(a, b);
	};

	vector<int> w(N);
	for(int &i: w) cin >> i;
	sort(AI(w));

	vector<tii> eve;
	for(int t, a, b, i = 0; i < M; ++i){
		cin >> t >> a >> b;
		a = lower_bound(AI(w), a) - begin(w);
		b = upper_bound(AI(w), b) - begin(w) - 1;
		if(a <= b) eve.pb(t, a, b);
	}
	eve.pb(T, 0, N-1);
	sort(AI(eve));

	set<tii> s;
	vector<pii> seg;
	int ans = 0;

	s.emplace(N-1, 0, -1);
	for(auto [t, l, r]: eve){
		int tl = l;
		while(l <= r){
			auto it = s.lower_bound(tii(l, -1, -1));
			auto [ur, ul, ut] = *it;
			s.erase(it);

			int width = min(r, ur) - l + 1;
			if(ut == -1) mad(ans, mul(width, t));
			else seg.pb(t - ut, width);

			if(ul < l) s.emplace(l-1, ul, ut);
			if(r < ur) s.emplace(ur, r+1, ut);
			l = ur + 1;
		}
		s.emplace(r, tl, t);
	}
	ans = mul(ans, K % D);

	sort(AI(seg)); reverse(AI(seg));
	for(auto [len, cnt]: seg){
		ll r = max(1ll, K - cnt + 1);
		mad(ans, mul(len, sig(r, K)));
		K = r - 1;
		if(K <= 0) break;
	}
	cout << ans << '\n';
	return 0;
}
