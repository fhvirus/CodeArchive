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

const int kN = 500005;
int N, Q, p[kN], ans[kN];

struct tii {
	int r, l, i;
	tii(int r, int l, int i):
		r(r), l(l), i(i) {}
	bool operator < (const tii &oth) const {
		return r < oth.r;
	}
};

void sim(int lb, int rb, int &round, vector<int> &sur){
	vector<int> dp, sc;
	for(int i = lb; i <= rb; ++i)
		sc.pb(i);
	while(sc.size() > 1){
		int n = sc.size();
		dp.clear(); ++round;
		for(int i = 0; i < n; ++i)
			if( (i == 0 or p[sc[i]] > p[sc[i-1]]) and (i == n-1 or p[sc[i]] > p[sc[i+1]]) )
				dp.pb(sc[i]);
		swap(dp, sc);
	}
	sur = dp;
}

void solve(int lb, int rb, vector<tii> &qs){
	if(qs.empty()) return;
	if(lb == rb) return;
	int round = 0; vector<int> sur;
	sim(lb, rb, round, sur);
	int n = sur.size(), lst = lb-1;
	sur.pb(rb+1);
	vector<tii> bkt;
	int q = qs.size(), p = 0;
	for(int i = 0; i < n; ++i){
		bkt.clear();
		while(p < q and qs[p].r < sur[i+1]){
			if(qs[p].l <= lst)
				ans[qs[p].i] = round;
			else
				bkt.push_back(qs[p]);
			++p;
		}
		solve(lst+1, sur[i+1]-1, bkt);
		lst = sur[i];
	}
}

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> N >> Q;
	for(int i = 1; i <= N; ++i) cin >> p[i];
	vector<tii> qs;
	for(int l, r, i = 0; i < Q; ++i){
		cin >> l >> r;
		if(l != r) qs.pb(r, l, i);
	}
	sort(AI(qs));
	solve(1, N, qs);
	for(int i = 0; i < Q; ++i)
		cout << ans[i] << '\n';
	return 0;
}
