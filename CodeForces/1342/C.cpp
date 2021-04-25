#include<iostream>
#include<algorithm>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define int long long

int a, b, c;

int gcd(int a, int b){
	while(b>0){
		a %= b;
		swap(a, b);
	}
	return a;
}

int lcm(int a, int b){
	return a * b / gcd(a, b);
}

int f(int n){
	if(n < 1) return 0;
	long long ans = (n/c)*(c-b);
	if(n%c >= b) ans += n%c - b+1;
	return ans;
}

signed main(){OW0
	int T, q;
	int l, r;
	cin >> T;
	while(T--){
		cin >> a >> b >> q;
		if(a > b)swap(a, b);
		c = lcm(a, b);
		while(q--){
			cin >> l >> r;
			cout << f(r) - f(l-1) << ' ';
		}
		cout << '\n';
	}
	return 0;
}