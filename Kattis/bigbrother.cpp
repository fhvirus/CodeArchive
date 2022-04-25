// Knapsack DP is harder than FFT.
#include<bits/stdc++.h>
using namespace std;
typedef long long ll; typedef pair<int,int> pii;
#define ff first
#define ss second
#define pb emplace_back
#define AI(x) begin(x),end(x)
#ifdef OWO
#define debug(args...) SDF(#args,args)
#define OIU(args...) ostream& operator<<(ostream&O,args)
#define LKJ(S,B,E,F) template<class...T>OIU(S<T...>s){O<<B;int c=0;for(auto i:s)O<<(c++?", ":"")<<F;return O<<E;}
LKJ(vector,'[',']',i)LKJ(deque,'[',']',i)LKJ(set,'{','}',i)LKJ(multiset,'{','}',i)LKJ(unordered_set,'{','}',i)LKJ(map,'{','}',i.ff<<':'<<i.ss)LKJ(unordered_map,'{','}',i.ff<<':'<<i.ss)
template<class...T>void SDF(const char* s,T...a){int c=sizeof...(T);if(!c){cerr<<"\033[1;32mvoid\033[0m\n";return;}(cerr<<"\033[1;32m("<<s<<") = (",...,(cerr<<a<<(--c?", ":")\033[0m\n")));}
template<class T,size_t N>OIU(array<T,N>a){return O<<vector<T>(AI(a));}template<class...T>OIU(pair<T...>p){return O<<'('<<p.ff<<','<<p.ss<<')';}template<class...T>OIU(tuple<T...>t){return O<<'(',apply([&O](T...s){int c=0;(...,(O<<(c++?", ":"")<<s));},t),O<<')';}
#else
#define debug(...) ((void)0)
#endif

const double eps = 1e-10;
int sign(double a) { return fabs(a) < eps ? 0 : (a > 0) - (a < 0); }

typedef pair<double, double> pdd;
#define x first
#define y second
#define opab(x) operator x (pdd a, pdd b)
pdd opab(+) { return pdd(a.x + b.x, a.y + b.y); }
pdd opab(-) { return pdd(a.x - b.x, a.y - b.y); }
double opab(*) { return a.x * b.x + a.y * b.y; }
double opab(^) { return a.x * b.y - a.y * b.x; }
pdd operator * (pdd a, double x) { return pdd(a.x * x, a.y * x); }
pdd operator / (pdd a, double x) { return pdd(a.x / x, a.y / x); }

#define abc(x) x (pdd a, pdd b, pdd c)
int abc(ori) { return sign((b - a) ^ (c - a)); }

typedef pair<pdd, pdd> seg;
int ori(seg a, pdd p) { return ori(a.x, a.y, p); }
bool operator == (seg a, seg b) {
	pdd v1 = a.y - a.x, v2 = b.y - b.x;
	return sign(v1 ^ v2) == 0 and sign(v1 * v2) > 0;
}
pdd interp(seg a, seg b) {
	double a123 = (a.y - a.x) ^ (b.x - a.x);
	double a124 = (a.y - a.x) ^ (b.y - a.x);
	return (b.y * a123 - b.x * a124) / (a123 - a124);
}

bool cmp(seg a, seg b) {
	pdd v1 = a.y - a.x, v2 = b.y - b.x;
	if (a == b) return ori(b, a.x) > 0;
	bool up1 = (v1 > pdd(0, 0));
	bool up2 = (v2 > pdd(0, 0));
	if (up1 != up2) return up1 > up2;
	return sign(v1 ^ v2) > 0;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << setprecision(10) << fixed;

	int n;
	cin >> n;

	vector<pdd> ps(n);
	for (int i = 0; i < n; ++i)
		cin >> ps[i].x >> ps[i].y;

	vector<seg> segs;
	for (int i = 0; i + 1 < n; ++i)
		segs.emplace_back(ps[i + 1], ps[i]);
	segs.emplace_back(ps[0], ps[n - 1]);

	sort(begin(segs), end(segs), cmp);

	deque<seg> dq;
	int len = 0;
	for (int i = 0; i < n; ++i) {
		if (i > 0 and segs[i] == segs[i - 1]) continue;
		while (len > 1 and ori(segs[i], interp(dq[len - 1], dq[len - 2])) < 0) {
			dq.pop_back();
			len -= 1;
		}
		while (len > 1 and ori(segs[i], interp(dq[0], dq[1])) < 0) {
			dq.pop_front();
			len -= 1;
		}
		dq.push_back(segs[i]);
		len += 1;
	}

	while (len > 2 and ori(dq[0], interp(dq[len - 1], dq[len - 2])) < 0) {
		dq.pop_back();
		len -= 1;
	}

	if (len < 3) {
		cout << 0 << '\n';
		return 0;
	}

	vector<pdd> hull(len);
	for (int i = 0; i + 1 < len; ++i)
		hull[i] = interp(dq[i], dq[i + 1]);
	hull.back() = interp(dq[len - 1], dq[0]);

	double ans = 0;
	for (int i = 0; i + 1 < len; ++i)
		ans += (hull[i] ^ hull[i + 1]);
	ans += (hull[len - 1] ^ hull[0]);

	cout << fabs(ans) / 2 << '\n';

	return 0;
}
// Knapsack DP is NP-Hard, but FFT is O(N log N).
