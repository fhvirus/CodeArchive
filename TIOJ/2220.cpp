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

const int kN = 100001;
int N, A, B, C;
int a[kN], b[kN], c[kN];

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> N >> A >> B >> C;
	for(int i = 0; i < N; ++i)
		cin >> a[i] >> b[i] >> c[i];

	// assume that we take C
	ll sum = 0;
	for(int i = 0; i < N; ++i){
		sum += c[i];
		a[i] -= c[i];
		b[i] -= c[i];
	}

	// again assume we take A
	vector<pii> v; v.reserve(N);
	for(int i = 0; i < N; ++i)
		v.pb(a[i], b[i]);
	sort(AI(v), greater<pii>());

	set<pii> inA, inB;
	vector<bool> isB(N, false);
	priority_queue<pii> inC;
	auto ins = [&](int i){
		// insert one
		auto [x, y] = v[i];
		sum += x;
		inA.emplace(y-x, i);
		if(inA.size() > A){
			auto it = prev(inA.end());
			auto [val, pos] = *it;
			inA.erase(it);
			inB.emplace(val, pos);
			isB[pos] = true;
			sum += val;
		}
		if(inB.empty()) return;
		auto itA = prev(inA.end());
		auto itB = inB.begin();
		if(*itA > *itB){
			auto [va, pa] = *itA;
			auto [vb, pb] = *itB;
			inA.erase(itA);
			inB.erase(itB);
			isB[pb] = false;
			sum -= vb;
			inA.emplace(vb, pb);
			inB.emplace(va, pa);
			isB[pa] = true;
			sum += va;
		}
	};
	auto rem = [&](int i){
		// remove one
		if(isB[i]){
			auto it = inB.find( pii(v[i].ss-v[i].ff, i) );
			inB.erase(it);
			isB[i] = false;
			sum -= v[i].ss;
		} else {
			auto it = inA.find( pii(v[i].ss-v[i].ff, i) );
			inA.erase(it);
			sum -= v[i].ff;
		}
		inC.emplace(v[i].ss, i);
	};

	for(int i = 0; i < A+B; ++i) ins(i);
	for(int i = A+B; i < N; ++i) inC.emplace(v[i].ss, i);

	ll ans = sum;
	for(int i = A+B-1; i >= 0; --i){
		rem(i);
		auto [val, pos] = inC.top();
		inC.pop();
		ins(pos);
		ans = max(ans, sum);
	}

	cout << ans << '\n';

	return 0;
}

