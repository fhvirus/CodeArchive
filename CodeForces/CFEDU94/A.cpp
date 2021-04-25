#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma loop_opt(on)
#include<iostream>
#include<string>
using namespace std;

int main(){
	int t, n;
	string in;
	cin >> t;
	for(; t; --t){
		cin >> n >> in;
		for(int i = 0; i < n; ++i) cout << in[n-1];
		cout << '\n';
	}
}