#pragma GCC optimize("Ofast")
#pragma loop-opt(on)
#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while(((c=RC())<'0'||c>'9')&&c!='-'&&c!=-1);if(c=='-'){a=0;while((c=RC())>='0'&&c<='9')a*=10,a-=c^'0';}else{a=c^'0';while((c=RC())>='0'&&c<='9')a*=10,a+=c^'0';}return a;}
inline void W(int n){static char buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]=' ';if(OP>65516)write(1,OB,OP),OP=0;}

#include<algorithm>
#include<numeric>
#include<utility>
#include<vector>
#include<tuple>
using namespace std;

#define ll long long
#define pii pair<ll, int>
#define ff first
#define ss second
#define N 300225
#define f(i,n) for(int i = 0; i < n; ++i)
#define ALL(x) x.begin(), x.end()
#define pb push_back

int n;
int x[N], y[N], r[N];
int id[N], ans[N];
bool del[N];

int loglen;
vector<vector<pii>> v;

inline bool inter(int i, int j){
	ll dx = x[i] - x[j], dy = y[i] - y[j], rr = r[i] + r[j];
	return dx*dx + dy*dy <= rr*rr;
}

inline void rescale(){
	--loglen;
	vector<vector<pii>> nv;
	for(const auto &d: v){
		vector<pii> tmp[2];
		for(const auto &p: d)
			if(!del[p.ss]) tmp[(x[p.ss] >> loglen) & 1].pb(p);
		if(tmp[0].size()) nv.pb({}), nv.back().swap(tmp[0]);
		if(tmp[1].size()) nv.pb({}), nv.back().swap(tmp[1]);
	}
	v.swap(nv);
}

inline void calc(int e){
	int xl, xr;
	xl = xr = lower_bound(ALL(v), (x[e] >> loglen) - 2,
		[&](const vector<pii> &a, const ll &b){
			return (x[a[0].ss] >> loglen) < b;
		}) - v.begin();
	while(xr < v.size() and (x[v[xr][0].ss] >> loglen) <= (x[e] >> loglen) + 2) ++xr;

	for(int m = xl; m < xr; ++m){
		for(auto it = lower_bound(ALL(v[m]), pii{y[e] - 2 * r[e], 0});
			it != v[m].end() and it->ff <= y[e] + 2 * r[e]; ++it)
			if(!del[it->ss] and inter(e, it->ss))
				del[it->ss] = true, ans[it->ss] = e;
	}
}

int main(){
	n = R();
	f(i,n) x[i] = R(), y[i] = R(), r[i] = R();

	if(n <= 5000){
		f(i,n) ans[i] = id[i] = i;
	    sort(id, id + n, [](int i, int j){
	        return r[i] == r[j] ? i < j : r[i] > r[j];
	    });
	    f(i,n){
	        if(ans[id[i]] != id[i]) continue;
	        for(int j = i + 1; j <= n; ++j){
	            if(ans[id[j]] == id[j] and inter(id[i], id[j]))
	                ans[id[j]] = id[i];
	        }
	    }
	    f(i,n) W(ans[i]+1);
	    write(1,OB,OP);
	    return 0;
	}

	// initialize
	int minx = *min_element(x, x + n), miny = *min_element(y, y + n);
	f(i,n) x[i] -= minx - 1, y[i] -= miny - 1;

	iota(id, id + n, 0);
	sort(id, id + n, [&](int i, int j){ return tie(r[i], j) > tie(r[j], i);});

	vector<int> xx(n), yy(n), rr(n);
	f(i,n) xx[i] = x[id[i]], yy[i] = y[id[i]], rr[i] = r[id[i]];
	f(i,n) x[i] = xx[i], y[i] = yy[i], r[i] = rr[i];

	loglen = 0;
	f(i,n) loglen = max(loglen, (int)__lg(x[i]) + 1);
	v.resize(1);
	f(i,n) v[0].pb({y[i], i});
	sort(ALL(v[0]));

	// solve
	f(i,n) if(!del[i]){
		del[i] = true; ans[i] = i;
		while(r[i] <= (1LL<<loglen) / 2) rescale();
		calc(i);
	}

	vector<int> tmp(n);
	f(i,n) tmp[id[i]] = id[ans[i]];
	f(i,n) W(tmp[i]+1);
	write(1,OB,OP);
}