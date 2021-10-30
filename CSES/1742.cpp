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

struct LISAN : vector<ll> {
	void done() { sort(AI()); erase(unique(AI()), end()); }
	int operator () (ll v) { return lower_bound(AI(), v) - begin(); }
};
struct BIT {
	int n; vector<int> val;
	BIT(int n = 0) : n(n), val(n+1, 0) {}
	void init(){ fill(AI(val), 0); };
	void modify(int p, int v){
		for(++p; p <= n; p += p & -p)
			val[p] += v;
	}
	int query(int p){
		int r = 0;
		for(++p; p > 0; p -= p&-p)
			r += val[p];
		return r;
	}
	int query(int l, int r){
		return query(r) - query(l-1);
	}
};
struct SOLVER {
	int dx, dy, tot;
	vector<vector<pii>> mods, ques, vers;
	BIT bit;
	SOLVER (int dx = 0, int dy = 0):
		dx(dx), dy(dy), mods(dy+1), ques(dy+1), vers(dx+1), bit(dx+1), tot(0) {}
	void init(){
		for(int i = 0; i <= dy; ++i) mods[i].clear();
		for(int i = 0; i <= dy; ++i) ques[i].clear();
		for(int i = 0; i <= dx; ++i) vers[i].clear();
		bit.init();
		tot = 0;
	}
	void add(int x1, int y1, int x2, int y2){
		++tot;
		if(x1 == x2){
			if(y1 > y2) swap(y1, y2);
			mods[y1].pb(x1, 1);
			mods[y2+1].pb(x1, -1);
			vers[x1].pb(y1, y2);
		} else {
			if(x1 > x2) swap(x1, x2);
			ques[y1].pb(x1, x2);
		}
	}
	bool go(vector<pii> &v){
		if(v.size() <= 1) return false;
		sort(AI(v));
		int mx = -1;
		for(auto [l, r]: v){
			if(mx >= l) return true;
			mx = max(mx, r);
		}
		return false;
	}
	bool solve(){
		for(auto &i: ques) if(go(i)) return true;
		for(auto &i: vers) if(go(i)) return true;
		ll cnt = 0;
		for(int i = 0; i <= dy; ++i){
			for(auto [p, v]: mods[i])
				bit.modify(p, v);
			for(auto [l, r]: ques[i])
				cnt += bit.query(l, r);
			if(cnt >= tot) return true;
		}
		return false;
	}
};

typedef array<ll, 4> seg;
ll banana(seg a, seg b, LISAN &lx, LISAN &ly){
	if((a[0] == a[2]) and (b[0] == b[2])){
		if(a[0] != b[0]) return -1;
		return min(abs(ly[a[1]] - ly[b[1]]), abs(ly[a[1]] - ly[b[3]]));
	}
	if((a[1] == a[3]) and (b[1] == b[3])){
		if(a[1] != b[1]) return -1;
		return min(abs(lx[a[0]] - lx[b[0]]), abs(lx[a[0]] - lx[b[2]]));
	}
	if(a[0] == a[2]){
		if(a[0] < min(b[0], b[2]) or a[0] > max(b[0], b[2])) return -1;
		return abs(ly[a[1]] - ly[b[1]]);
	}
	if(a[1] < min(b[1], b[3]) or a[1] > max(b[1], b[3])) return -1;
	return abs(lx[a[0]] - lx[b[0]]);
}

bool opposite(char a, char b){
	if(a > b) swap(a, b);
	return (a == 'D' and b == 'U')
		or (a == 'L' and b == 'R');
}

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int n; cin >> n;
	vector<ll> len;
	vector<pair<char, ll>> mv;
	int ret = n+1;
	for(int i = 0; i < n; ++i){
		char d; int x; cin >> d >> x;
		if(i > 0 and d == mv.back().ff){
			mv.back().ss += x;
			len.back() += x;
		} else {
			mv.pb(d, x);
			len.pb(x);
			if(len.size() > 1 and opposite(end(mv)[-2].ff, d)){
				ret = len.size()-1;
				break;
			}
		}
	}
	n = len.size();

	vector<seg> segs;
	LISAN lx, ly; lx.pb(0), ly.pb(0);
	for(ll cx = 0, cy = 0, nx, ny, i = 0; i < n; ++i){
		auto [dir, x] = mv[i];
		if(dir == 'U') nx = cx, ny = cy + x;
		if(dir == 'D') nx = cx, ny = cy - x;
		if(dir == 'R') nx = cx + x, ny = cy;
		if(dir == 'L') nx = cx - x, ny = cy;
		segs.push_back({ cx, cy, nx, ny });
		if(cx != nx) lx.pb(nx);
		if(cy != ny) ly.pb(ny);
		cx = nx, cy = ny;
	}
	lx.done(); ly.done();
	for(auto &a: segs){
		a[0] = lx(a[0]); a[2] = lx(a[2]);
		a[1] = ly(a[1]); a[3] = ly(a[3]);
	}

	int l = 1, r = n, m;
	SOLVER solver(lx.size(), ly.size());
	while(l < r){
		m = (l+r) / 2;
		solver.init();
		for(int i = 0; i <= m; ++i)
			solver.add(segs[i][0], segs[i][1], segs[i][2], segs[i][3]);
		if(solver.solve()) r = m;
		else l = m+1;
		if(l >= ret) break;
	}
	
	ll sum = accumulate(begin(len), begin(len) + min(ret, l), 0ll);
	if(l == n or ret <= l){
		cout << sum << '\n';
		return 0;
	}
	ll ans = 1e18;
	for(int i = 0; i < l-1; ++i){
		ll d = banana(segs[l], segs[i], lx, ly);
		if(d != -1) ans = min(ans, d);
	}
	cout << sum + ans << '\n';
	return 0;
}
