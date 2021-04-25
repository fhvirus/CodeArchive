// Knapsack DP is harder than FFT.
#include<unistd.h>
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(long long n){char OB[20],OP=0,buf[20],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];write(1,OB,OP);}

#include<deque>
#include<utility>
#include<cstdint>
using namespace std;
typedef int64_t ll;
typedef pair<ll,ll> pll;
#define ff first
#define ss second
#define pb emplace_back
#define FOR(i,n) for(int i=0;i<(n);++i)
#define FOO(i,a,b) for(int i=(a);i<=int(b);++i)
template<class I>bool chmax(I&a,I b){return a<b?(a=b,true):false;}

const int N = 1e5 + 225;
int n, m;
pll red[N], blu[N];
inline ll area(int r, int b){
	return (red[r].ff - blu[b].ff) * (blu[b].ss - red[r].ss);
}
struct eek{
	// red id -> blu[l, r)
	int id, l, r;
	eek(int id = 0, int l = 0, int r = 0): id(id), l(l), r(r){}
};
deque<eek> dq;

int32_t main(){
	{
		n = R() / 2;
		int x = 0, y = 0, r, d;
		FOR(i,n){
			r = R(), d = R();
			red[i] = {x + r, y};
			x += r, y += d;
		}
	}
	{
		m = R() / 2;
		int x = 0, y = 0, d, r;
		FOR(i,m){
			d = R(), r = R();
			blu[i] = {x, y + d};
			x += r, y += d;
		}
	}

	FOR(i,n){
		while(!dq.empty()){
			auto & back = dq.back();
			if(area(back.id, back.l) > area(i, back.l)) break;
			dq.pop_back();
		}

		if(dq.empty()){
			dq.pb(i, 0, m);
			continue;
		}
		auto & back = dq.back();
		if(area(back.id, m-1) >= area(i, m-1)) continue;

		auto [id, l, r] = back; int mid;
		while(l + 1 < r){
			mid = (l + r) / 2;
			(area(id, mid) <= area(i, mid) ? r : l) = mid;
		}
		back.r = l;
		// m is m not mid!
		dq.pb(i, l, m);
	}
	
	ll ans = 0;
	for(auto x: dq){
		auto [i, l, r] = x;
		FOO(j, l, r - 1) chmax(ans, area(i, j));
	}
	W(ans);
	return 0;
}
