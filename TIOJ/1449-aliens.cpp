// Knapsack DP is harder than FFT.
#pragma GCC optimize("Ofast")
#include<unistd.h>
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(long long n){char OB[20],OP=0,buf[20],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];write(1,OB,OP);}

#include<algorithm>
#include<utility>
using namespace std;
typedef pair<int, int> pii;
#define ff first
#define ss second
#define FOO(i,a,b) for(int i=(a);i<=int(b);++i)

const int N = 1004;
int n, k, a[N];
int pre[N];

inline int w(int l, int r){
	int m = (l + r) / 2;
	return (a[m] * ((m - l + 1) - (r - m)) - (pre[m] - pre[l-1])) + 
		((pre[r] - pre[m]));
}

struct Seg{
	int i, l, r;
	Seg(int i = 0, int l = 0, int r = 0):
		i(i), l(l), r(r){}
};

pii operator+(pii a, pii b){
	return pii(a.ff + b.ff, a.ss + b.ss);
}
pii dp[N];
pii f(int j, int i, int pen){
	return dp[j] + pii(w(j + 1, i) + pen, 1);
}

Seg dq[N];
int he, ta;
bool check(int pen){
	he = ta = 0;
	dq[ta++] = Seg(0, 1, n);

	FOO(i,1,n){
		while(dq[he].r < i) ++he;
		dp[i] = f(dq[he].i, i, pen);

		while(he < ta and f(i, dq[ta-1].l, pen) <= f(dq[ta-1].i, dq[ta-1].l, pen))
			--ta;

		if(he == ta){
			dq[ta++] = Seg(i, 1, n);
			continue;
		}

		if(f(i, dq[ta-1].r, pen) > f(dq[ta-1].i, dq[ta-1].r, pen)){
			if(dq[ta-1].r < n) dq[ta++] = Seg(i, dq[ta-1].r + 1, n);
			continue;
		}

		auto [j, l, r] = dq[ta-1];
		int m;
		while(l < r){
			m = (l + r) / 2;
			if(f(j, m, pen) < f(i, m, pen)) l = m + 1;
			else r = m;
		}
		dq[ta-1].r = l - 1;
		dq[ta++] = Seg(i, l, n);
	}
	return dp[n].ss <= k;
}

// the more cut, the better
// so we are adding penalty to each cut
// the bigger penalty is, the less cut there wiint be
// so if cut > k, increase penalty
// else cut <= k, don't modify/ decrease
// so:
// if(cnt > k) l = cnt + 1;
// else r = cnt;
// then check(m) returns:
// m as penalty, is cnt <= k ? 

int32_t main(){
	n = R(), k = R();
	FOO(i,2,n) a[i] = R();
	sort(a + 1, a + n + 1);
	FOO(i,1,n) pre[i] = pre[i-1] + a[i];

	int l = 0, r = 1e5, m;
	while(l < r){
		m = (l + r) / 2;
		if(check(m)) r = m;
		else l = m + 1;
	}
	check(l);
	W(dp[n].ff - k * l);
	return 0;
}
