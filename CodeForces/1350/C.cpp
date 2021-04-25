#include<iostream>
#include<algorithm>
using namespace std;

#define eek ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define MAXN 100000
typedef long long ll;

ll a[MAXN], pre[MAXN], suf[MAXN];

ll gcd(ll x, ll y){
	while(y){
		x %= y;
		swap(x, y);
	}
	return x;
}

int main(){eek
	int n;
	cin >> n;
	for(int i = 0; i < n; ++i)
		cin >> a[i];
	pre[0] = a[0], suf[n-1] = a[n-1];
	for(int i = 1; i < n; ++i)
		pre[i] = gcd(a[i], pre[i-1]);
	for(int i = n-2; i >= 0; --i)
		suf[i] = gcd(a[i], suf[i+1]);
	ll ans = suf[1];
	for(int i = 1; i < n; ++i){
		if(i == n-1)
			ans = ans * pre[i-1] / gcd(ans, pre[i-1]);
		else
			ans = ans * gcd(pre[i-1], suf[i+1]) / gcd(ans, gcd(pre[i-1], suf[i+1]));
	}
	cout << ans;
	return 0;
}