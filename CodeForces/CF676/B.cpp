#pragma Ofast
#pragma loop-opt(on)
#define FOR(i, n) for(int i = 1; i <= n; ++i)
#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define ll long long
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

const int N = 201;
int t, n, cnt;
char a[N][N];

int main(){OW0
	cin >> t;
	for(; t; --t){
		cin >> n;
		FOR(i, n) FOR(j, n) cin >> a[i][j];
		cnt = 0;
		if(a[2][1] != a[1][2] and a[n][n-1] != a[n-1][n]){
			cout << 2 << endl;
			if(a[2][1] == '1') cout << "2 1\n";
			else cout << "1 2\n";
			if(a[n][n-1] == '0') cout << n << ' ' << n-1 << endl;
			else cout << n-1 << ' ' << n << endl;
		} else if(a[2][1] == a[1][2] and a[n][n-1] == a[n-1][n]){
			if(a[2][1] == a[n][n-1]){
				cout << "2\n2 1\n1 2\n";
			} else {
				cout << "0\n";
			}
		} else if(a[2][1] == a[1][2]){
			cout << "1\n";
			if(a[n][n-1] == a[2][1]) cout << n << ' ' << n-1 << endl;
			else cout << n-1 << ' ' << n << endl;
		} else {
			cout << "1\n";
			if(a[2][1] == a[n-1][n]) cout << "2 1\n";
			else cout << "1 2\n";
		}
	}
	return 0;
}