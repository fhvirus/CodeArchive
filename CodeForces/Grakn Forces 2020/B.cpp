#pragma Ofast
#pragma loop-opt(on)
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cmath>
using namespace std;
#define ll long long
#define FOR(i, n) for(int i = 0; i < n; ++i)
#define debug(x) cerr << #x << " is " << x << '\n';
const int N = 100 + 1;
int t, n, k, a[N], ans;

int main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> t;
	for(; t; --t){
		cin >> n >> k; ans = 0;
		FOR(i, n) cin >> a[i];
		bool all = true;
		for(int i = 1; i < n; ++i)
			if(a[i] != a[0]) all = false;
		if(all) cout << "1\n";
		else if(k == 1){
			cout << "-1\n";
		} else {
			for(int i = 1; i < n; ++i)
				if(a[i] != a[i-1]) ++ans;
			cout << (int)ceil((double)ans / (k - 1)) << '\n';
		}
	}
	return 0;
}