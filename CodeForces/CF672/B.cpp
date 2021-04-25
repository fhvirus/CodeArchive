#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

const int N = 1e5 + 1;
int t, n, a[N], cnt[32];
int main(){
	cin >> t;
	for(; t; --t){
		cin >> n;
		for(int i = 0; i < n; ++i) cin >> a[i];
		for(int i = 0; i < 32; ++i) cnt[i] = 0;
		long long ans = 0;
		for(int i = 0; i < n; ++i){
			int l = 31 - __builtin_clz(a[i]);
			ans += cnt[l];
			cnt[l]++;
		}
		cout << ans << '\n';
	}
	return 0;
}