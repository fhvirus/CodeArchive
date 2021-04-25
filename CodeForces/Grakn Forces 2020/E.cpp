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
const int N = 1e5 + 1;
int t, n, a[N], ans;

int main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> t;
	for(; t; --t){
		cin >> n; ans = 0;
		FOR(i, n) cin >> a[i];
	}
	return 0;
}