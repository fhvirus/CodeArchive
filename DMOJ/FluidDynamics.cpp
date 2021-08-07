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

const int kN = 200002;
const int kK = 350;

int N, Q; ll W;

struct BLK {
	int siz;
	vector<pii> milk;
	vector<pii> hull, kelp;
	BLK(): siz(0), milk(), hull(), kelp() {}
	BLK(vector<pii> a): siz(a.size()), milk(a), hull(), kelp(a) {
		for(auto &[a, b]: kelp) swap(a, b), b = -b;
		sort(AI(kelp), greater<pii>());
		buildHull();
	}
	void buildHull(){
		// problem 1
		auto canKill = [](pii a, pii b, pii c){
			if(b.ff == c.ff) return b.ss >= c.ss;
			return 1ll * (c.ss - a.ss) * (a.ff - b.ff)
				<= 1ll * (b.ss - a.ss) * (a.ff - c.ff);
		};
		hull.clear();
		for(pii i: kelp){
			while(hull.size() >= 2 and canKill(end(hull)[-2], end(hull)[-1], i))
				hull.pop_back();
			hull.push_back(i);
		}
	}
	void insert(int v, int c){
		int pos = 0;
		for(; pos < siz; ++pos)
			if(1ll * v * milk[pos].ss - 1ll * milk[pos].ff * c < W)
				break;
		milk.insert(begin(milk) + pos, pii(v, c));

		int a = c, b = -v;
		pos = 0;
		for(; pos < siz; ++pos)
			if(kelp[pos].ff <= a)
				break;
		kelp.insert(begin(kelp) + pos, pii(a, b));

		++siz;
		if(siz == kK * 2) return;

		buildHull();
	}
	pii query(int k){ return milk[k]; }
	bool canSkip(int v, int c){
		if(siz == 0) return false;
		auto f = [&](pii a){ return 1ll * v * a.ff - 1ll * -a.ss * c; };
		if(hull.size() == 1) return f(hull[0]) >= W;

		// problem 2
		if(f(hull[0]) < f(hull[1])) return f(hull[0]) >= W;
		int p = 0;
		for(int l = 1 << __lg((int) hull.size()); l > 0; l >>= 1)
			if(p + l < hull.size()-1 and f(hull[p+l]) > f(hull[p+l+1]))
				p += l;
		return f(hull[p+1]) >= W;
	}
	vector<pii> split(){
		auto it = begin(milk) + kK;
		vector<pii> ret(it, end(milk));
		milk.erase(it, end(milk));

		hull.clear();
		kelp = milk;
		for(auto &[a, b]: kelp) swap(a, b), b = -b;
		sort(AI(kelp), greater<pii>());
		buildHull();
		siz = kK;
		return ret;
	}
}; 

vector<BLK> blk;
vector<int> nxt;

int tot = 0;
void insert(int v, int c){
	++tot;
	int cur = 0;
	while(blk[cur].canSkip(v, c) and nxt[cur] != -1) cur = nxt[cur];
	blk[cur].insert(v, c);

	if(blk[cur].siz < kK * 2) return;
	vector<pii> tmp = blk[cur].split();
	blk.pb(tmp); nxt.pb(-1);
	int niw = blk.size() - 1;
	nxt[niw] = nxt[cur]; nxt[cur] = niw;
}
void query(int k){
	k = tot - k;
	int cur = 0;
	while(k >= blk[cur].siz){
		k -= blk[cur].siz;
		cur = nxt[cur];
	}
	pii ans = blk[cur].query(k);
	cout << ans.ff << ' ' << ans.ss << '\n';
}

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> N >> Q >> W;

	blk.pb();
	nxt.pb(-1);
	tot = 0;
	for(int v, c, i = 1; i <= N; ++i){
		cin >> v >> c;
		insert(v, c);
	}
	for(int i = 1; i <= Q; ++i){
		string s; cin >> s;
		if(s[0] == 'K'){
			int k; cin >> k;
			query(k);
		} else {
			int v, c; cin >> v >> c;
			insert(v, c);
		}
	}
	return 0;
}
