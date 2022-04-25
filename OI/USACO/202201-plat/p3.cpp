// Knapsack DP is harder than FFT.
#include<bits/stdc++.h>
using namespace std;
typedef long long ll; typedef pair<int,int> pii;
#define ff first
#define ss second
#define pb emplace_back
#define AI(x) begin(x),end(x)
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

struct Vec {
	int64_t x, y;
	Vec (int64_t x = 0, int64_t y = 0): x(x), y(y) {}
	void read() { cin >> x >> y; }
};
const Vec hori(1, 0);

ostream& operator << (ostream& O, const Vec& v)
{ return O << '(' << v.x << ", " << v.y << ')'; }

bool operator < (const Vec& a, const Vec& b)
{ return a.x != b.x ? a.x < b.x : a.y < b.y; }
Vec operator + (const Vec& a, const Vec& b)
{ return Vec(a.x + b.x, a.y + b.y); }
Vec operator - (const Vec& a, const Vec& b)
{ return Vec(a.x - b.x, a.y - b.y); }
Vec operator - (const Vec& a)
{ return Vec(-a.x, -a.y); }
int64_t operator * (const Vec& a, const Vec& b)
{ return a.x * b.x + a.y * b.y; }
int64_t operator ^ (const Vec& a, const Vec& b)
{ return a.x * b.y - a.y * b.x; }
int sign(int64_t a) { return (a > 0) - (a < 0); }
int ori(const Vec& a, const Vec& b, const Vec& c)
{ return sign((b - a) ^ (c - a)); }
bool upper(const Vec& a)
{ return a.y > 0 or (a.y == 0 and a.x > 0); }
bool cmp(const Vec& a, const Vec& b) {
	bool u = upper(a), v = upper(b);
	if (u != v) return u > v;
	return (a ^ b) > 0;
}
bool same(const Vec& a, const Vec& b) {
	return (a ^ b) == 0 and (a * b) > 0;
}

void getHull(vector<Vec>& ps) {
	if (ps.size() <= 1) return;
	sort(begin(ps), end(ps));
	vector<Vec> stk;
	int n = ps.size();
	for (int i = 0; i < n; ++i) {
		while (stk.size() > 1 and ori(end(stk)[-2], end(stk)[-1], ps[i]) <= 0)
			stk.pop_back();
		stk.push_back(ps[i]);
	}
	int t = stk.size();
	for (int i = n - 2; i >= 0; --i) {
		while (stk.size() > t and ori(end(stk)[-2], end(stk)[-1], ps[i]) <= 0)
			stk.pop_back();
		stk.push_back(ps[i]);
	}
	stk.pop_back();
	swap(ps, stk);
}
void getBorder(const vector<Vec>& ps, vector<Vec>& border) {
	int n = ps.size();
	for (int i = 0; i + 1 < n; ++i) {
		Vec v = ps[i + 1] - ps[i];
		border[i] = Vec(v.y, -v.x);
	}
	Vec v = ps[0] - ps[n - 1];
	border[n - 1] = Vec(v.y, -v.x);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int N;
	cin >> N;

	vector<pair<Vec, Vec>> events;

	for (int i = 0; i < N; ++i) {
		int G;
		cin >> G;

		vector<Vec> ps(G);
		for (Vec& v: ps)
			v.read();

		getHull(ps);

		vector<Vec> border(ps.size());
		getBorder(ps, border);

		debug(ps);
		debug(border);

		int n = ps.size();
		for (int i = 0; i < n; ++i) {
			Vec lb = border[i == 0 ? n - 1 : i - 1];
			Vec rb = border[i];
			if (sign(hori ^ lb) < 0 and sign(hori ^ rb) > 0)
				events.emplace_back(hori, ps[i]);
			events.emplace_back(lb, ps[i]);
			if (!same(rb, hori))
				events.emplace_back(rb, -ps[i]);
		}
	}

	for (const auto& i: events)
		debug(i);

	sort(begin(events), end(events), [](const pair<Vec, Vec>& u, const pair<Vec, Vec>& v) {
		return cmp(u.first, v.first);
	});

	int64_t ans = 0;
	Vec cur(0, 0);
	for (int i = 0, j = 0, n = events.size(); i < n; i = j) {
		for (; j < n and same(events[i].first, events[j].first); ++j) {
			cur = cur + events[j].second;
			debug(events[j]);
		}
		debug(cur, cur * cur);
		ans = max(ans, cur * cur);
	}

	cout << ans << '\n';

	return 0;
}
