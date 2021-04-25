#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

const int N = 1e5 + 1;
int t, n, a[N];
int main(){
	cin >> t;
	for(; t; --t){
		cin >> n;
		for(int i = 0; i < n; ++i) cin >> a[i];
		bool all = true;
		for(int i = 1; i < n; ++i)
			if(a[i] >= a[i-1]){ all = false; break;}
		cout << (all ? "NO" : "YES") << '\n';
	}
	return 0;
}