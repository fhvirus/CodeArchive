#pragma Ofast
#pragma loop-opt(on)
#define FOR(i, n) for(int i = 0; i < n; ++i)
#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define ll long long
#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
using namespace std;

const int N = 1e5;

int main(){OW0
	string s;
	cin >> s;
	cout << 4 << '\n';
	cout << "R " << s.size()-1 << '\n';
	cout << "R " << s.size() << '\n';
	cout << "L " << s.size()+1 << '\n';
	cout << "L 2" << '\n';
	return 0;
}