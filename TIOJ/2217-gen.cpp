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
#define debug(...) ((void)0)
#endif

#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2")

const int kN = 200;
const int kK = 200;

typedef bitset<kN> owo;
mt19937 mt(std::chrono::system_clock::now().time_since_epoch().count());

int n, k;
bitset<kN> a[kK];

int solve(bitset<kN> cur){
	int mn = kN;
	for(int i = 0; i < k; ++i){
		int sum = (a[i]^cur).count();
		mn = min(mn, sum);
	}
	return mn;
}
owo mate(owo a, owo b){
	owo c(0);
	for(int i = 0; i < kN; ++i)
		c[i] = (mt()&1) ? a[i] : b[i];
	return c;
}

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> n >> k;
	for(int i = 0; i < k; ++i){
		string s; cin >> s;
		a[i] = bitset<kN>(s);
	}

	uniform_int_distribution<int> rnd1(0, k);
	uniform_int_distribution<int> rnd2(0, n-1);
	
	vector<array<int, 2>> cnt(n, {0, 0});
	for(int i = 0; i < k; ++i)
		for(int j = 0; j < n; ++j)
			++cnt[n][a[i][j]];

	vector<owo> gen;
	const int kC = 200;
	for(int uwu = 0; uwu < kC; ++uwu){
		owo o(0);
		for(int i = 0; i < n; ++i)
			o[i] = (rnd1(mt) <= cnt[i][0]);
		gen.pb(o);
	}

	const int kG = 10000;
	for(int uwu = 0; uwu < kG; ++uwu){
		vector<owo> nx;
		for(int g = 0; g < 3; ++g){
			random_shuffle(AI(gen));
			for(int i = 0; i < kC; i += 2){
				for(int h = 5; h > 1; --h){
					owo o = mate(gen[i], gen[i+1]);
					for(int i = 0; i < 5; ++i){
						auto tmp = o;
						for(int x = (mt() % h + 1); x; --x)
							tmp.flip(rnd2(mt));
						nx.push_back(tmp);
					}
				}
			}
		}
		for(auto i: gen) nx.push_back(i);

		sort(AI(nx), [](owo a, owo b){ return solve(a) > solve(b); });
		if((uwu&7) == 0) nx.erase(unique(AI(nx)), end(nx));

		vector<owo> jiz;
		while(nx.size() > kC) nx.pop_back();
		debug(solve(nx[0]), nx[0]);
		swap(nx, gen);
	}

	return 0;
}
