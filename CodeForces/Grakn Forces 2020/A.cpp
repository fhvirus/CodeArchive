#pragma Ofast
#pragma loop-opt(on)
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;
#define ll long long
#define FOR(i, n) for(int i = 0; i < n; ++i)
#define debug(x) cerr << #x << " is " << x << '\n';
const int N = 100 + 1;
int t, n, a[N], b[N], c[N], ans;

int main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> t;
	for(; t; --t){
		cin >> n; ans = 0;
		FOR(i, n) cin >> a[i];
		FOR(i, n) cin >> b[i];
		FOR(i, n) cin >> c[i];
		int last = a[0];
		cout << a[0] << ' ';
		for(int i = 1; i < n-1; ++i){
			if(a[i] != last){
				cout << a[i] << ' ';
				last = a[i];
			} else if(b[i] != last){
				cout << b[i] << ' ';
				last = b[i];
			} else{
				cout << c[i] << ' ';
				last = c[i];
			}
		}
		if(a[n-1] != a[0] and a[n-1] != last){
			cout << a[n-1] << '\n';
		} else if(b[n-1] != a[0] and b[n-1] != last){
			cout << b[n-1] << '\n';
		} else {
			cout << c[n-1] << '\n';
		}
	}
	return 0;
}