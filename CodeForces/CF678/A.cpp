#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

const int N = 1e5 + 1;
int t, n, m, a[N];

int main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> t;
	for(; t; --t){
		cin >> n >> m;
		int sum = 0;
		for(int i = 0; i < n; ++i){
			cin >> a[i];
			sum += a[i];
		}
		cout << (sum == m ? "YES\n" : "NO\n");
	}
	return 0;
}