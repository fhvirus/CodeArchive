#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

#define int long long
#define justinlaiorz ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
const int N = 3e5 + 10, M = 998244353;
int s[N];
void init(){
	s[0] = 1;
	for(int i = 1; i < N; ++i)
		s[i] = s[i-1]  * i % M;
}
int pow(int x, int e){
	int ans = 1;
	while(e) (e&1) and (ans = ans * x % M), x = x * x % M, e >>= 1;
	return ans;
}
int nee(int x){
	return pow(x, M-2);
}
int C(int n, int k){
	return s[n] * nee(s[k]) % M * nee(s[n - k]) % M;
}

int n, k, l[N], r[N]; 
int des[N<<1], e;
signed main(){
	init();
	justinlaiorz
	cin >> n >> k;
	for(int i = 0; i < n; ++i) cin >> l[i] >> r[i], des[e++] = (l[i]), des[e++] = (r[i]);
	sort(des, des + e); e = unique(des, des + e) - des;
	// for(int i: des) cout << i << ' ';
	// 	cout << endl;
	for(int i = 0; i < n; ++i) l[i] = lower_bound(des, des + e, l[i]) - des, r[i] = lower_bound(des, des + e, r[i]) - des;
	sort(l, l + n); sort(r, r + n);
	int lptr = 0, rptr = 0, cur = 0;
	long long ans = 0;

	// for(int i = 0; i < n; ++i) cout << l[i] << ' ';
	// 	cout << '\n';
	// for(int i = 0; i < n; ++i) cout << r[i] << ' ';
	// 	cout << '\n';
	for(int i = 0; i < e; ++i){
		// cout << i << ' ' << cur << '\n';
		while(rptr < n and r[rptr] + 1 == i) --cur, ++rptr;
		while(lptr < n and l[lptr] == i){
			if(cur >= k - 1) ans = (ans + C(cur, k-1)) % M;
			++cur, ++lptr;
		}
	}
	cout << ans;
	return 0;
}