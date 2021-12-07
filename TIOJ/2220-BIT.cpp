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

struct DS {
	// given a list of possible value
	// insert/remove one item
	// query the first K (const) items
	vector<int> pv, cnt;
	vector<ll> val;
	int n;
	inline void pb(int v){ pv.pb(v); }
	void done(){
		sort(AI(pv), greater<int>());
		pv.erase(unique(AI(pv)), end(pv));
		n = pv.size();
		cnt.assign(n+1, 0);
		val.assign(n+1, 0);
	}
	void modify(int v, int t){
		int p = lower_bound(AI(pv), v, greater<int>()) - begin(pv) + 1;
		for(; p <= n; p += p&-p){
			cnt[p] += t;
			val[p] += t * v;
		}
	}
	ll query(int k){
		int c = 0, p = 0; ll s = 0;
		for(int l = __lg(n); l >= 0; --l){
			int np = p + (1<<l);
			if(np <= n and c + cnt[np] < k)
				p = np, c += cnt[np], s += val[np];
		}
		s += (ll) (k-c) * pv[p];
		return s;
	}
};

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int N, A, B, C;
	cin >> N >> A >> B >> C;

	ll sum = 0;
	vector<pii> v;
	for(int a, b, c, i = 0; i < N; ++i){
		cin >> a >> b >> c;
		b -= a; c -= a;
		v.pb(b, c); sum += a;
	}
	sort(AI(v), greater<pii>());

	DS ds;
	for(auto &[b, c]: v) ds.pb(c - b);
	ds.done();

	priority_queue<pii> pq;
	for(int i = 0; i < B+C; ++i) ds.modify(v[i].ss-v[i].ff, 1), sum += v[i].ff;
	for(int i = B+C; i < N; ++i) pq.emplace(v[i].ss, -v[i].ff);

	ll ans = sum + ds.query(C);
	for(int i = B+C-1; i >= 0; --i){
		auto [b, c] = v[i];
		sum -= b; ds.modify(c-b, -1);
		pq.emplace(c, -b);

		auto [nc, nb] = pq.top(); nb = -nb;
		pq.pop();
		sum += nb; ds.modify(nc - nb, 1);

		ans = max(ans, sum + ds.query(C));
	}
	cout << ans << '\n';

	return 0;
}
