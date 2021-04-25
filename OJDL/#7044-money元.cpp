#include<iostream>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
using ll = long long;

void extgcd(ll a, ll b, ll &x, ll &y, ll &d){
	if(!b){
		d = a;
		x = 1;
		y = 0;
		return;
	}
	extgcd(b, a%b, x, y, d);
	ll newx = y, newy = x - a / b * y;
	x = newx, y = newy;
	return;
}

inline ll mod(ll x, ll m){
	if(x > 0) return x;
	return m+x;
}

int main(){OW0
	ll m, q, n, x, y, d;
	cin >> m >> q;
	for(;q;q--){
		cin >> n;
		extgcd(n, m, x, y, d);
		if(d != 1) cout << "jizz\n";
		else{
			cout << mod(x, m) << '\n';
		}
	}
	return 0;
}