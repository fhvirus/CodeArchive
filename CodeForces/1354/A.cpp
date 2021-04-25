#include<iostream>
using namespace std;

#define eek ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

int main(){eek
	long long t, a, b, c, d;
	cin >> t;
	while(t--){
		cin >> a >> b >> c >> d;
		if(b >= a) cout << b << '\n';
		else{
			if(d >= c) cout << "-1\n";
			else{
				int left = a-b;
				int e = left / (c-d) + (left%(c-d)? 1: 0);
				cout << b + e * c << '\n';
			}
		}
	}
	return 0;
}