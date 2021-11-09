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

const int MOD = 1e9+7;
const int P = 37;
const int INV = 621621626;
inline int mad(int u, int v){
	u += v - MOD;
	u += MOD & (u >> 31);
	return u;
}
inline int mul(int u, int v){
	return (ll) u * v % MOD;
}
inline int mow(int x, int e){
	int r = 1;
	while(e){
		if(e&1) r = mul(r, x);
		x = mul(x, x);
		e >>= 1;
	}
	return r;
}

struct BIT {
	int n; vector<int> val;
	BIT (int nn) : n(nn), val(nn+1, 0) {}
	void modify(int p, int v){
		for(; p <= n; p += p&-p)
			val[p] = mad(val[p], v);
	}
	int query(int p){
		int r = 0;
		for(; p > 0; p -= p&-p)
			r = mad(r, val[p]);
		return r;
	}
	int query(int l, int r){
		return mad(query(r), MOD-query(l-1));
	}
};

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int N, Q; cin >> N >> Q;
	string S; cin >> S; S = ' ' + S;

	vector<int> p(N+1); p[0] = 1;
	for(int i = 1; i <= N; ++i) p[i] = mul(p[i-1], P);
	vector<int> q(N+1); q[0] = 1;
	for(int i = 1; i <= N; ++i) q[i] = mul(q[i-1], INV);
	BIT hs(N+2), sh(N+2);
	for(int i = 1; i <= N; ++i) hs.modify(i, mul(S[i] - 'a', p[i-1]));
	for(int i = 1; i <= N; ++i) sh.modify(i, mul(S[i] - 'a', p[N-i]));

	auto geths = [&](int l, int r){
		int d = hs.query(l, r);
		d = mul(d, q[l-1]);
		return d;
	};
	auto getsh = [&](int l, int r){
		int d = sh.query(l, r);
		d = mul(d, q[N-r]);
		return d;
	};

	for(int t, l, r, i = 0; i < Q; ++i){
		cin >> t >> l >> r;
		if(t == 1){
			int x = (r-l+1) / 3;
			if(x * 3 != (r-l+1)){
				cout << 0 << '\n';
				continue;
			}
			int a = geths(l, l+x-1);
			int b = getsh(l+x, l+2*x-1);
			int c = geths(l+2*x, r);
			cout << (a == b and b == c) << '\n';
		} else {
			if(S[l] == S[r]) continue;
			hs.modify(l, MOD-mul(S[l] - 'a', p[l-1]));
			hs.modify(r, MOD-mul(S[r] - 'a', p[r-1]));
			sh.modify(l, MOD-mul(S[l] - 'a', p[N-l]));
			sh.modify(r, MOD-mul(S[r] - 'a', p[N-r]));
			swap(S[l], S[r]);
			hs.modify(l, mul(S[l] - 'a', p[l-1]));
			hs.modify(r, mul(S[r] - 'a', p[r-1]));
			sh.modify(l, mul(S[l] - 'a', p[N-l]));
			sh.modify(r, mul(S[r] - 'a', p[N-r]));
		}
	}
	return 0;
}

