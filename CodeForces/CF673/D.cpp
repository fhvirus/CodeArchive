#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

const int N = 1e5 + 10;
int t, n, a[N];
struct eek{
	int a, b, x;
};

int main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> t;
	for(; t; --t){
		cin >> n;
		int sum = 0;
		for(int i = 1; i <= n; ++i)
			cin >> a[i], sum += a[i];
		if(sum % n != 0){ cout << "-1\n"; continue;}

		vector<eek> v;
		int avg = sum / n, jizz = 0;
		for(int i = 2; i <= n; ++i){
			if(a[i] % i > avg) ++ jizz;
		}
		for(int i = 2; i <= n; ++i){
			v.push_back({i, 1, a[i] / i});
			// cout << i << " 1 " << a[i] / i << '\n';
			a[i] %= i;
		}
		for(int i = 2; i <= n; ++i){
			if(a[i] > avg){
				v.push_back({1, i, avg * (a[i] / avg + 1) - a[i]});
				v.push_back({i, 1, (a[i] - avg) / i});
			} else{
				v.push_back({1, i, avg - a[i]});
			}
		}

		cout << v.size() << '\n';
		for(eek i: v){
			cout << i.a << ' ' << i.b << ' ' << i.x << '\n';
		}
	}
}