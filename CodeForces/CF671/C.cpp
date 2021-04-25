#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

#define justinlaiorz ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define int long long
const int N = 1e3;
int t, n, x, a[N];

signed main(){ justinlaiorz
	cin >> t;
	for(; t; --t){
		cin >> n >> x;
		bool all = true, has = false;
		int sum = 0;
		for(int i = 0; i < n; ++i){
			cin >> a[i];
			all &= (a[i] == x);
			has |= (a[i] == x);
			sum += a[i];
		}
		// cout << "Sum: " << sum << '\n';
		if(all){ cout << 0 << '\n'; continue;}
		if(sum % n == 0 and sum / n == x){ cout << "1\n"; continue;}
		if(has){ cout << "1\n"; continue;}
		if(sum % n == 0){ cout << "2\n"; continue;}
		cout << "2\n";
	}
	return 0;
}