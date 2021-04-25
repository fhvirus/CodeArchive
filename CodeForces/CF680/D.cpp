#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
const int N = 150000 + 225, M = 998244353;
#define ll long long
ll n, a[N*2];
inline ll mpow(ll x, ll e){
	ll ans = 1; 
	while(e) (e&1)&&(ans = ans * x % M), x = x * x % M, e >>= 1;
	return ans;
}
int main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> n;
	for(int i = 0; i < n * 2; ++i)
		cin >> a[i];
	sort(a, a + n * 2);
	ll sa = 0, sb = 0, jiz = 1, eek = 1;
	for(int i = 0; i < n; ++i)
		sa += a[i], sb += a[i + n];
	for(int i = 1; i <= n; ++i)
		jiz = jiz * i % M, eek = eek * (i + n) % M;

	cout << ((sb - sa) % M * eek % M * (mpow(jiz, M - 2)) % M + M) % M;
	return 0;
}