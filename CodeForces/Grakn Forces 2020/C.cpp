#pragma Ofast
#pragma loop-opt(on)
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<iomanip>
using namespace std;
#define ll long long
#define FOR(i, n) for(int i = 1; i <= n; ++i)
#define debug(x) cerr << #x << " is " << x << '\n';
const int N = 1e5 + 10;
const double EPS = 1e-7;
int T, n, l, a[N], ans;
double jizz[N], eek[N];

inline bool check(double t){
	double lt = 0, lp = 0, rt = 0, rp = l;
	for(int i = 1; i <= n; ++i){
		double tmp = (a[i] - a[i-1]) / (double)i;
		if(lt + tmp <= t) lt += tmp, lp = a[i];
		else{
			lp += i * (t - lt);
			lt = t;
			break;
		}
	}
	if(lt < t) lp += (n + 1) * (t - lt);
	for(int i = n; i > 0; --i){
		double tmp = (a[i+1] - a[i]) / (double)(n - i + 1);
		if(rt + tmp <= t) rt += tmp, rp = a[i];
		else{
			rp -= (n - i + 1) * (t - rt);
			rt = t;
			break;
		}
	}
	if(rt < t) rp -= (n + 1) * (t - rt);
	// cout << "Jizz " << t << ' ' << lp << ' ' << rp << '\n';
	return lp >= rp;
}

int main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> T;
	for(; T; --T){
		cin >> n >> l; ans = 0;
		FOR(i, n) cin >> a[i];
		a[0] = 0, a[n + 1] = l;
		double L = 0, R = l, M;
		// debug(L) debug(R)
		while(L + EPS < R){
			M = (L + R) / 2;
			if(check(M)) R = M;
			else L = M;
		}
		cout << setprecision(10) << fixed << R << '\n';
	}
	return 0;
}