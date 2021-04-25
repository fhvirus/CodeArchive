#pragma Ofast
#pragma loop-opt(on)
#define FOR(i, n) for(int i = 0; i < n; ++i)
#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define ll long long
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

const int N = 1e5;
int t, a, b;

int main(){OW0
	cin >> t;
	for(; t; --t){
		cin >> a >> b;
		int c = a & b;
		cout << (a ^ c) + (b ^ c) << endl;
	}
	return 0;
}