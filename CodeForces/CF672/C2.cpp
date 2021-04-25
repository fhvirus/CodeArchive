#pragma Ofast
#pragma loop-opt(on)
#include<iostream>
#include<algorithm>
using namespace std;

#define int long long
const int N = 3e5 + 10;
int t, n, q, a[N], ans;
inline void erase(int i){
	if(i == 0 or i == n + 1) return;
	if(a[i-1] < a[i] and a[i+1] < a[i]) ans -= a[i];
	if(a[i-1] > a[i] and a[i+1] > a[i]) ans += a[i];
}
inline void insert(int i){
	if(i == 0 or i == n + 1) return;
	if(a[i-1] < a[i] and a[i+1] < a[i]) ans += a[i];
	if(a[i-1] > a[i] and a[i+1] > a[i]) ans -= a[i];
}
signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> t;
	for(; t; --t){
		cin >> n >> q;
		for(int i = 1; i <= n; ++i) cin >> a[i];
		a[0] = -1, a[n+1] = -1;
		ans = 0;
		for(int i = 1; i <= n; ++i){
			if(a[i-1] < a[i] and a[i+1] < a[i]) ans += a[i];
			if(a[i-1] > a[i] and a[i+1] > a[i]) ans -= a[i];
		}
		cout << ans << '\n';
		for(int l, r; q; --q){
			cin >> l >> r;
			erase(l-1), erase(l), erase(l+1);
			if(l != r){
				if(r - 1 != l and r - 1 != l + 1) erase(r-1);
				if(r != l + 1) erase(r);
				erase(r + 1);
			}
			swap(a[l], a[r]);
			insert(l-1), insert(l), insert(l+1);
			if(l != r){
				if(r - 1 != l and r - 1 != l + 1) insert(r - 1);
				if(r != l + 1) insert(r);
				insert(r + 1);
			}
			cout << ans << '\n';
		}
	}
	return 0;
}
